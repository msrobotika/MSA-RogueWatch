#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_timer.h"
#include "esp_mac.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "canary.h"

static snapshot_t state;
static portMUX_TYPE lock = portMUX_INITIALIZER_UNLOCKED;
static uint8_t mac[6];
static volatile bool paused;

void canary_snapshot(snapshot_t *out){portENTER_CRITICAL(&lock);*out=state;portEXIT_CRITICAL(&lock);out->uptime=(uint32_t)(esp_timer_get_time()/1000000);out->heap=esp_get_free_heap_size();out->armed=!paused;}
void canary_toggle(void){paused=!paused;}
void canary_save_display(int profile,bool invert){(void)profile;(void)invert;}
void canary_serial_blob(const uint8_t *data,unsigned bytes,int width,int height){(void)data;(void)bytes;(void)width;(void)height;}
const char *canary_service(unsigned index){(void)index;return "SCAN";}

static void scan_task(void *arg){
  (void)arg;
  while(1){
    if(!paused){
      uint16_t count=0;
      esp_wifi_scan_start(NULL,true);
      esp_wifi_scan_get_ap_num(&count);
      wifi_ap_record_t records[32]; uint16_t n=32;
      esp_wifi_scan_get_ap_records(&n,records);
      portENTER_CRITICAL(&lock);
      state.hits=count; state.logged++; state.alert_sequence=state.logged;
      state.rssi=n?records[0].rssi:0; state.connected=true; state.configured=true;
      strlcpy(state.ip,"PASIVO",sizeof(state.ip)); strlcpy(state.ssid,"RADAR WIFI",sizeof(state.ssid));
      portEXIT_CRITICAL(&lock);
    }
    vTaskDelay(pdMS_TO_TICKS(10000));
  }
}

void app_main(void){
  memset(&state,0,sizeof(state)); esp_read_mac(mac,ESP_MAC_WIFI_STA);
  strlcpy(state.ip,"PASIVO",sizeof(state.ip)); strlcpy(state.ssid,"RADAR WIFI",sizeof(state.ssid));
  display_start(0,true);
  ESP_ERROR_CHECK(esp_netif_init()); ESP_ERROR_CHECK(esp_event_loop_create_default()); esp_netif_create_default_wifi_sta();
  wifi_init_config_t cfg=WIFI_INIT_CONFIG_DEFAULT(); ESP_ERROR_CHECK(esp_wifi_init(&cfg));
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA)); ESP_ERROR_CHECK(esp_wifi_start()); esp_wifi_set_ps(WIFI_PS_NONE);
  xTaskCreate(scan_task,"roguewatch_scan",4096,NULL,4,NULL);
  while(1){vTaskDelay(pdMS_TO_TICKS(1000));}
}
