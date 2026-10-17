/* Original MSA Canary UI. Candidate ideaspark pinout: GJKJ/ESP3219LCD.
 * Two panel geometries are selectable; no touch hardware is assumed. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_heap_caps.h"
#include "esp_timer.h"
#include "lwip/sockets.h"
#include "ui_fonts.h"
#include "canary.h"

#define BG 0x060D16
#define CARD 0x101E2C
#define EDGE 0x243A4E
#define WHITE 0xE4F0F4
#define DIM 0x8299AD
#define TEAL 0x40E3C1
#define AMBER 0xFFBF63
#define RED 0xFF4F65
static esp_lcd_panel_handle_t panel;
static SemaphoreHandle_t flushed,capture_done;
static uint16_t *pixels;
static int width=170,height=320;
static volatile int page,requested_profile,applied_profile=-1;
static volatile bool requested_invert=true,applied_invert=true,capture_requested;
static volatile unsigned frames;
static int64_t frame_ms,alarm_until;
static unsigned seen_sequence;
static volatile unsigned button_presses,button_holds;
// 32-bit millisecond timestamps avoid torn 64-bit cross-task accesses on ESP32.
static volatile uint32_t manual_until;
static uint32_t last_rotation;
static uint32_t millis(void){return (uint32_t)(esp_timer_get_time()/1000);}
static bool manual_active(uint32_t now){return manual_until&&(int32_t)(manual_until-now)>0;}
static const char *titles[4]={"RADAR","ALERTAS","HUELLAS","EVIDENCIAS"};

static uint16_t rgb565(uint32_t c){return __builtin_bswap16(((c>>8)&0xf800)|((c>>5)&0x7e0)|((c>>3)&31));}
static void pixel(int x,int y,uint32_t c){if(x>=0&&x<width&&y>=0&&y<height)pixels[y*width+x]=rgb565(c);}
static void rect(int x,int y,int w,int h,uint32_t c){
 int left=x<0?0:x,right=x+w>width?width:x+w,top=y<0?0:y,bottom=y+h>height?height:y+h;
 uint16_t color=rgb565(c);for(int yy=top;yy<bottom;yy++)for(int xx=left;xx<right;xx++)pixels[yy*width+xx]=color;
}
static void line(int x0,int y0,int x1,int y1,uint32_t c){
 int dx=abs(x1-x0),sx=x0<x1?1:-1,dy=-abs(y1-y0),sy=y0<y1?1:-1,e=dx+dy;
 while(1){pixel(x0,y0,c);if(x0==x1&&y0==y1)break;int twice=2*e;if(twice>=dy){e+=dy;x0+=sx;}if(twice<=dx){e+=dx;y0+=sy;}}
}
static void outline(int x,int y,int w,int h,uint32_t c){line(x,y,x+w-1,y,c);line(x,y+h-1,x+w-1,y+h-1,c);line(x,y,x,y+h-1,c);line(x+w-1,y,x+w-1,y+h-1,c);}
static void alpha(int x,int y,uint32_t c,uint8_t a){
 if(!a||x<0||x>=width||y<0||y>=height)return;
 uint16_t old=__builtin_bswap16(pixels[y*width+x]);int r=((old>>11)&31)*255/31,g=((old>>5)&63)*255/63,b=(old&31)*255/31;
 r=(r*(255-a)+((c>>16)&255)*a)/255;g=(g*(255-a)+((c>>8)&255)*a)/255;b=(b*(255-a)+(c&255)*a)/255;pixel(x,y,(r<<16)|(g<<8)|b);
}
static int text_width(const char *s,const ui_font_t *font){int n=0;for(;*s;s++){unsigned ch=(unsigned char)*s;if(ch<32||ch>126)ch='?';n+=font->glyph[ch-32].width;}return n;}
static void text(int x,int y,const char *s,const ui_font_t *font,uint32_t c){
 for(;*s;s++){
  unsigned ch=(unsigned char)*s;if(ch<32||ch>126)ch='?';const glyph_t *g=&font->glyph[ch-32];
  for(int yy=0;yy<font->height;yy++)for(int xx=0;xx<g->width;xx++)alpha(x+xx,y+yy,c,font->data[g->offset+yy*g->width+xx]);
  x+=g->width;if(x>=width)break;
 }
}
static void centered(int y,const char *s,const ui_font_t *font,uint32_t c){text((width-text_width(s,font))/2,y,s,font,c);}
static void clipped(int x,int y,int available,const char *s,const ui_font_t *font,uint32_t c){
 char small[48];strlcpy(small,s,sizeof(small));if(text_width(small,font)>available){size_t n=strlen(small);while(n&&text_width(small,font)+text_width("..",font)>available)small[--n]=0;strlcat(small,"..",sizeof(small));}text(x,y,small,font,c);
}
static void draw_signal(int x,int y,const snapshot_t *s){int bars=!s->connected?0:s->rssi>=-55?4:s->rssi>=-67?3:s->rssi>=-78?2:1;for(int i=0;i<4;i++)rect(x+i*5,y+12-i*3,3,3+i*3,i<bars?TEAL:EDGE);}
static bool warning_active(void){return frame_ms<alarm_until;}
static void header(const snapshot_t *s){
 text(9,5,"MSA_ROBOTIKA",&font11,DIM);text(8,18,"ROGUEWATCH",&font19,WHITE);draw_signal(width-28,18,s);
 line(8,44,width-9,44,EDGE);rect(8,44,18+(frame_ms/40)%(width-37),1,warning_active()?RED:TEAL);
 text(9,49,titles[page],&font11,warning_active()?RED:DIM);
}
static void footer(void){
 int y=height-25;line(8,y,width-9,y,EDGE);
 for(unsigned i=0;i<4;i++)rect(width/2-22+i*12,y+5,7,3,i==(unsigned)page?TEAL:EDGE);
 centered(height-14,manual_active(millis())?"BOOT: vista | 2s: pausa":"AUTO | BOOT: cambiar",&font11,DIM);
}
static void emblem(int cx,int cy,bool danger){
 uint32_t ink=danger?RED:TEAL;int pulse=frame_ms/90%36;bool blink=frame_ms%5800>5600;
 outline(cx-40,cy-35,80,71,EDGE);line(cx-48,cy-12,cx-48,cy+12,ink);line(cx+48,cy-12,cx+48,cy+12,ink);
 line(cx-31,cy-21,cx,cy-31,ink);line(cx,cy-31,cx+31,cy-21,ink);line(cx-31,cy-21,cx-26,cy+16,ink);line(cx+31,cy-21,cx+26,cy+16,ink);line(cx-26,cy+16,cx,cy+30,ink);line(cx,cy+30,cx+26,cy+16,ink);
 rect(cx-24,cy-9,18,blink?2:7,ink);rect(cx+6,cy-9,18,blink?2:7,ink);
 line(cx-4,cy-2,cx-10,cy+11,ink);line(cx+4,cy-2,cx+10,cy+11,ink);line(cx-10,cy+11,cx,cy+17,ink);line(cx,cy+17,cx+10,cy+11,ink);
 line(cx-34,cy-18+pulse,cx+34,cy-18+pulse,0x175044);
}
static void dashboard(const snapshot_t *s){
 bool tall=height>240;emblem(width/2,tall?116:101,warning_active());
 const char *label=!s->configured?"CONFIGURAR WIFI":!s->connected?"SIN ENLACE":!s->armed?"ESCUCHA PAUSADA":warning_active()?"ACCESO RECIBIDO":"ESCUCHA ACTIVA";
 uint32_t ink=!s->connected||!s->armed?AMBER:warning_active()?RED:TEAL;
 int y=tall?158:141;centered(y,label,&font13,ink);
 if(tall){centered(178,"Solo conexiones a este equipo",&font11,DIM);}
 y=tall?203:169;rect(9,y,width-18,tall?54:42,CARD);
 char value[32];snprintf(value,sizeof(value),"%lu",(unsigned long)s->hits);text(17,y-1,value,tall?&font26:&font19,WHITE);text(18,y+(tall?32:24),"ACCESOS DESDE ARRANQUE",&font11,DIM);
 if(tall){clipped(10,268,width-20,s->connected?s->ip:"Configurar por USB",&font13,WHITE);}
}
static void events_page(const snapshot_t *s){
 if(!s->event_count){centered(104,"SIN EVENTOS",&font19,TEAL);centered(139,"Esperando conexiones",&font11,DIM);return;}
 unsigned rows=height>240?3:2;char small[48];
 for(unsigned i=0;i<s->event_count&&i<rows;i++){
  const event_t *e=&s->events[i];int y=69+i*64;rect(8,y,width-16,58,CARD);rect(8,y,2,58,e->multiport?AMBER:TEAL);
  snprintf(small,sizeof(small),"%s :%u",canary_service(e->service),e->port);text(16,y+2,small,&font13,WHITE);
  struct in_addr addr={.s_addr=e->ip};char ip[16];inet_ntop(AF_INET,&addr,ip,sizeof(ip));text(16,y+20,ip,&font13,TEAL);
  snprintf(small,sizeof(small),"t+%lus  x%lu%s",(unsigned long)e->seconds,(unsigned long)e->repeats,e->multiport?"  MULTI":"");text(16,y+40,small,&font11,e->multiport?AMBER:DIM);
 }
 if(height>240){snprintf(small,sizeof(small),"Historial RAM: %u / 24",s->event_count);text(10,268,small,&font11,DIM);}
}
static void services_page(const snapshot_t *s){
 char value[40];const int ports[4]={80,22,21,23};int step=height>240?43:31;
 for(unsigned i=0;i<4;i++){
  int y=70+i*step;rect(8,y,width-16,step-4,CARD);rect(width-18,y+9,4,4,(s->ports_ready&(1U<<i))?TEAL:AMBER);
  snprintf(value,sizeof(value),"%s  %d",canary_service(i),ports[i]);text(15,y+1,value,&font13,WHITE);
  if(height>240){snprintf(value,sizeof(value),"%lu accesos",(unsigned long)s->per_service[i]);text(15,y+19,value,&font11,DIM);}
 }
 if(height>240){text(10,250,"Banners, sin acceso real",&font11,DIM);text(10,268,"No solicita contrasenas",&font11,TEAL);}
}
static void network_page(const snapshot_t *s){
 int y=72;char value[48];text(10,y,"DIRECCION LOCAL",&font11,DIM);clipped(10,y+17,width-20,s->ip,width>135?&font19:&font13,WHITE);
 y+=51;text(10,y,"RED WIFI",&font11,DIM);clipped(10,y+16,width-20,s->configured?s->ssid:"Sin configurar",&font13,TEAL);
 y+=43;snprintf(value,sizeof(value),"Senal: %d dBm",s->rssi);text(10,y,s->connected?value:"Esperando enlace",&font13,s->connected?WHITE:AMBER);
 if(height>240){snprintf(value,sizeof(value),"Tiempo: %lum %lus",(unsigned long)(s->uptime/60),(unsigned long)(s->uptime%60));text(10,y+30,value,&font11,DIM);snprintf(value,sizeof(value),"RAM libre: %lu kB",(unsigned long)(s->heap/1024));text(10,y+48,value,&font11,DIM);text(10,268,"Datos del canario, no de la LAN",&font11,DIM);}
}
static bool color_done(esp_lcd_panel_io_handle_t io,esp_lcd_panel_io_event_data_t *event,void *ctx){BaseType_t wake=pdFALSE;xSemaphoreGiveFromISR(flushed,&wake);return wake==pdTRUE;}
static void apply_geometry(void){
 if(applied_profile==requested_profile&&applied_invert==requested_invert)return;
 applied_profile=requested_profile;applied_invert=requested_invert;width=applied_profile==0?170:135;height=applied_profile==0?320:240;
 esp_lcd_panel_swap_xy(panel,false);esp_lcd_panel_mirror(panel,false,false);esp_lcd_panel_set_gap(panel,applied_profile==0?35:52,applied_profile==0?0:40);esp_lcd_panel_invert_color(panel,applied_invert);
}
static void button_task(void *unused){
 bool raw=false,stable=false,acted=false;uint32_t changed=0,pressed_at=0;
 while(1){
  uint32_t now=millis();bool sample=gpio_get_level(0)==0;
  if(sample!=raw){raw=sample;changed=now;}
  if(raw!=stable&&now-changed>=30){
   stable=raw;
   if(stable){pressed_at=now;acted=false;}
   else if(!acted){button_presses++;page=(page+1)%4;manual_until=now+60000;}
  }
  if(stable&&!acted&&now-pressed_at>=2000){button_holds++;canary_toggle();acted=true;manual_until=now+60000;}
  vTaskDelay(pdMS_TO_TICKS(10));
 }
}
static void display_task(void *unused){
 while(1){
  frame_ms=esp_timer_get_time()/1000;uint32_t now=millis();
  if(manual_active(now))last_rotation=now;
  else if(now-last_rotation>=12000){page=(page+1)%4;last_rotation=now;}
  snapshot_t s;canary_snapshot(&s);if(s.alert_sequence!=seen_sequence){seen_sequence=s.alert_sequence;alarm_until=frame_ms+6000;}
  apply_geometry();rect(0,0,width,height,BG);header(&s);
  if(page==0)dashboard(&s);else if(page==1)events_page(&s);else if(page==2)services_page(&s);else network_page(&s);
  footer();if(warning_active()&&(frame_ms/350)%2==0){outline(0,0,width,height,RED);outline(1,1,width-2,height-2,RED);}
  while(xSemaphoreTake(flushed,0)==pdTRUE){}
  if(esp_lcd_panel_draw_bitmap(panel,0,0,width,height,pixels)==ESP_OK&&xSemaphoreTake(flushed,pdMS_TO_TICKS(1000))==pdTRUE)frames++;
  if(capture_requested){capture_requested=false;canary_serial_blob((const uint8_t*)pixels,width*height*2,width,height);xSemaphoreGive(capture_done);}
  vTaskDelay(pdMS_TO_TICKS(90));
 }
}
void display_start(int profile,bool invert){
 requested_profile=profile;requested_invert=invert;flushed=xSemaphoreCreateBinary();capture_done=xSemaphoreCreateBinary();pixels=heap_caps_malloc(170*320*2,MALLOC_CAP_DMA);assert(flushed&&capture_done&&pixels);
 spi_bus_config_t bus={.mosi_io_num=23,.miso_io_num=-1,.sclk_io_num=18,.quadwp_io_num=-1,.quadhd_io_num=-1,.max_transfer_sz=170*320*2};ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST,&bus,SPI_DMA_CH_AUTO));
 esp_lcd_panel_io_handle_t io;esp_lcd_panel_io_spi_config_t cfg={.cs_gpio_num=15,.dc_gpio_num=2,.spi_mode=0,.pclk_hz=16000000,.trans_queue_depth=1,.lcd_cmd_bits=8,.lcd_param_bits=8,.on_color_trans_done=color_done};
 ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPI2_HOST,&cfg,&io));esp_lcd_panel_dev_config_t dev={.reset_gpio_num=4,.rgb_ele_order=LCD_RGB_ELEMENT_ORDER_RGB,.bits_per_pixel=16};ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(io,&dev,&panel));ESP_ERROR_CHECK(esp_lcd_panel_reset(panel));ESP_ERROR_CHECK(esp_lcd_panel_init(panel));apply_geometry();ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel,true));
 gpio_config_t led={.pin_bit_mask=1ULL<<32,.mode=GPIO_MODE_OUTPUT};ESP_ERROR_CHECK(gpio_config(&led));gpio_set_level(32,1);gpio_config_t button={.pin_bit_mask=1ULL<<0,.mode=GPIO_MODE_INPUT,.pull_up_en=GPIO_PULLUP_ENABLE};ESP_ERROR_CHECK(gpio_config(&button));
 assert(xTaskCreate(display_task,"canary_ui",6144,NULL,3,NULL)==pdPASS);
 assert(xTaskCreate(button_task,"canary_button",2048,NULL,3,NULL)==pdPASS);
}
void display_page(int value){if(value>=0&&value<4){page=value;manual_until=millis()+60000;}}
void display_profile(int profile,bool invert){requested_profile=profile;requested_invert=invert;}
bool display_capture(void){while(xSemaphoreTake(capture_done,0)==pdTRUE){}capture_requested=true;return xSemaphoreTake(capture_done,pdMS_TO_TICKS(20000))==pdTRUE;}
unsigned display_frames(void){return frames;}
int display_current_page(void){return page;}
int display_current_profile(void){return applied_profile;}
bool display_current_invert(void){return applied_invert;}
unsigned display_button_presses(void){return button_presses;}
unsigned display_button_holds(void){return button_holds;}
int display_button_level(void){return gpio_get_level(0);}
bool display_auto_active(void){return !manual_active(millis());}

