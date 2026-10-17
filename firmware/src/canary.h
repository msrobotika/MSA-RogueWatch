#pragma once
#include <stdbool.h>
#include <stdint.h>
#define EVENT_CAP 24
typedef struct {uint32_t sequence,seconds,ip,repeats;uint16_t port;uint8_t service;bool multiport;} event_t;
typedef struct {
 bool connected,configured,armed;
 char ip[16],ssid[33];int rssi,disconnect_reason;
 uint32_t hits,logged,suppressed,uptime,heap,alert_sequence;
 uint32_t per_service[4];uint16_t ports_ready;
 event_t events[EVENT_CAP];unsigned event_count;
} snapshot_t;
void canary_snapshot(snapshot_t *out);
void canary_toggle(void);
void canary_save_display(int profile,bool invert);
void canary_serial_blob(const uint8_t *data,unsigned bytes,int width,int height);
const char *canary_service(unsigned index);
void display_start(int profile,bool invert);
void display_page(int page);
void display_profile(int profile,bool invert);
bool display_capture(void);
unsigned display_frames(void);
int display_current_page(void);
int display_current_profile(void);
bool display_current_invert(void);
unsigned display_button_presses(void);
unsigned display_button_holds(void);
int display_button_level(void);
bool display_auto_active(void);
