#ifndef __SIMON_GAME__
#define __SIMON_GAME__

#include "pico/stdlib.h"
#include "debounce.hpp"
#include <iostream>
#include <vector>
#include <cstdint>


namespace SimonGame{
    static const uint32_t BLINK_LED_DELAY=500;
    static const uint32_t ONBOARD_LED =25;
    static const uint32_t LED0=12;//yellow
    static const uint32_t LED1=13;//green
    static const uint32_t LED2=14;//red
    static const uint32_t LED3=15;//yellow
    static const uint32_t BTN0=16;//btm
    static const uint32_t BTN1=17;//2
    static const uint32_t BTN2=18;//3
    static const uint32_t BTN3=19; //top
    static const uint32_t BTN4=20;
    static const uint32_t PATTERN_LEN=10;
    static const uint32_t NUMBER_OF_BTNS=5;
    extern CurrentBtnState_t current_btn_stat;

    void core1_entry();
    void gpio_callback(uint gpio, uint32_t events);

    class SimonGameClass{
        public:
        SimonGameClass();
        void initialize_gpio();
        void initialize_irq();
        void check_user_input();
        void check_pattern_gen();
        void generate_pattern();
        void show_pattern();
        bool is_game_over();
        void reset_game();
        uint32_t get_random_num();

        volatile bool waiting_for_pattern;
        int level;
        int user_input_number;
        int game_over;
        int user_point;

        volatile BtnState btns[NUMBER_OF_BTNS];
        std::vector<int> rand_pattern;

    };
};
#endif
