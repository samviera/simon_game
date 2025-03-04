#ifndef __DEBOUNCE_H__
#define __DEBOUNCE_H__

#include "pico/stdlib.h"


static const uint32_t DEBOUNCE_DELAY = 200000;
static const uint32_t HIGH=1;
static const uint32_t LOW=0;

typedef struct{
    uint but_pin;
    bool prev_state;
    bool curr_state;
    absolute_time_t prev_time;
    absolute_time_t curr_time;
}BtnState;

typedef struct{
    int32_t btn;
    uint32_t events;
    bool has_changed;
}CurrentBtnState_t;

bool debounce(const volatile BtnState &btn);
bool is_stable(const absolute_time_t prev_time,const absolute_time_t curr_time);
bool has_changed (bool prev_state,bool curr_state);
void set_rising_edge_state(volatile BtnState *btn);
void set_falling_edge_state(volatile BtnState *btn0);
void reset_btn_state(volatile BtnState *btn);

#endif
