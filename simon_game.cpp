#include "simon_game.hpp"
//#include "hardware/gpio.h"
//#include "hardware/regs/addressmap.h"
//#include "hardware/regs/rosc.h"
#include "hardware/structs/rosc.h"
//#include "pico/stdio.h"
//#include "debounce.hpp"
#include <cstdint>
#include <cstdio>

CurrentBtnState_t SimonGame::current_btn_stat({-1,0,false});

SimonGame::SimonGameClass::SimonGameClass()
    :waiting_for_pattern(true),level(0),user_input_number(0),
    game_over(false),user_point(0),btns{{BTN0,false,false,0,0},
    {BTN1,false,false,0,0},
    {BTN2,false,false,0,0},
    {BTN3,false,false,0,0},
    {BTN4,false,false,0,0}},
    //rand patten vec
    rand_pattern{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}{
        //empty
    }
//init gpio
    void SimonGame::SimonGameClass::initialize_gpio(){
        stdio_init_all();
        gpio_init(SimonGame::ONBOARD_LED);
        gpio_set_dir(SimonGame::ONBOARD_LED,true);
        gpio_init(SimonGame::LED0);
        gpio_set_dir(SimonGame::LED0,true);
        gpio_init(SimonGame::LED1);
        gpio_set_dir(SimonGame::LED1,true);
        gpio_init(SimonGame::LED2);
        gpio_set_dir(SimonGame::LED2,true);
        gpio_init(SimonGame::LED3);
        gpio_set_dir(SimonGame::LED3,true);

    }

    void SimonGame::SimonGameClass::initialize_irq(){
        gpio_set_irq_enabled_with_callback(SimonGame::BTN0,GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL,true,&SimonGame::gpio_callback);
        gpio_set_irq_enabled(SimonGame::BTN1,GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL,true);
        gpio_set_irq_enabled(SimonGame::BTN2,GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL,true);
        gpio_set_irq_enabled(SimonGame::BTN3,GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL,true);
        gpio_set_irq_enabled(SimonGame::BTN4,GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL,true);
    }

    void SimonGame::SimonGameClass::check_user_input(){
        if (!current_btn_stat.has_changed){
            return;
        }
        current_btn_stat.has_changed=false;

        volatile BtnState *target_btn;
        int32_t gpio=current_btn_stat.btn;
        uint32_t events=current_btn_stat.events;

        if(gpio==SimonGame::BTN0){
            target_btn=&btns[0];
    }else if (gpio==SimonGame::BTN1){
        target_btn=&btns[1];
    }else if (gpio==SimonGame::BTN2){
        target_btn=&btns[2];
    }else if(gpio==SimonGame::BTN3){
        target_btn=&btns[3];
    }else if(gpio==SimonGame::BTN4){
        target_btn=&btns[4];
    }else{
        return;
    }

    if((events & GPIO_IRQ_EDGE_RISE)&&(events & GPIO_IRQ_EDGE_FALL)){
        set_rising_edge_state(target_btn);
        return;
    }else if (events&GPIO_IRQ_EDGE_RISE){
        set_rising_edge_state( target_btn);
        return;
    }else if(events & GPIO_IRQ_EDGE_FALL){
        set_falling_edge_state(target_btn);
    }
    bool is_btn_stable=debounce(*target_btn);

    if(is_btn_stable){
        if(gpio==BTN3){
            reset_game();
            return;
        }

        if(game_over){
            return;
        }
        int user_selected_value=-1;
        switch(gpio){
            case BTN0:
            user_selected_value=0;
            break;
            case BTN1:
            user_selected_value=1;
            break;
            case BTN2:
            user_selected_value=2;
            break;
            case BTN4:
            user_selected_value=3;
            break;
            default:
            break;
        }
        if (user_selected_value==-1){
            return;
        }

        if(user_input_number<level){
            printf("[%d] of [%d] rand = %d user=%d\n",user_input_number,level,rand_pattern.at(user_input_number),user_selected_value);
            
            if(rand_pattern.at(user_input_number)!= user_selected_value){
            game_over=true;
std::cout<<" __        ______        _______. _______ .______   " <<std::endl;
std::cout<<"|  |      /  __  \\      /       ||   ____||   _  \\   "<<std::endl;  
std::cout<<"|  |     |  |  |  |    |   (----`|  |__   |  |_)  |  " <<std::endl;   
std::cout<<"|  |     |  |  |  |     \\   \\    |   __|  |      /     " <<std::endl; 
std::cout<<"|  `----.|  `--'  | .----)   |   |  |____ |  |\\  \\----. " <<std::endl;
std::cout<<"|_______| \\______/  |_______/    |_______|| _| `._____| " <<std::endl;
                                                       
std::cout<<"  _______      ___      .___  ___.  _______             " <<std::endl;
std::cout<<" /  _____|    /   \\    |   \\/   | |   ____|            " <<std::endl;
std::cout<<"|  |  __     /  ^  \\    |  \\  /  | |  |__               " <<std::endl;
std::cout<<"|  | |_ |   /  /_\\  \\  |  |\\/|  | |   __|              " <<std::endl;
std::cout<<"|  |__| |  /  _____  \\  |  |  |  | |  |____             " <<std::endl;
std::cout<<"\\______| /__/     \\__\\|__|  |__| |_______|            " <<std::endl;
                                                       
std::cout<<"  ______   ____    ____  _______ .______                " <<std::endl;
std::cout<<" /  __  \\  \\   \\  /   / |   ____||   _  \\             " <<std::endl;  
std::cout<<"|  |  |  |  \\   \\/   /  |  |__   |  |_)  |              " <<std::endl;
std::cout<<"|  |  |  |   \\      /   |   __|  |      /               " <<std::endl;
std::cout<<"|  `--'  |    \\    /    |  |____ |  |\\  \\----.          " <<std::endl;
std::cout<<"\\______/      \\__/     |_______|| _| `._____|          " <<std::endl;
                            
return;
            }
            if (user_input_number ==level-1){
                user_input_number=0;
                user_point++;

            printf("score:%d\n", user_point);
            waiting_for_pattern=true;

            }else {
            waiting_for_pattern=false;
            user_input_number++;
            }
        }
    }
    }
    void SimonGame::SimonGameClass::reset_game(){
        std::cout<<"----------------"<<std::endl;
        std::cout<<"Reset Game"<<std::endl;
        std::cout<<"----------------"<<std::endl;
        user_point=0;
        level=0;
        game_over=false;
        user_input_number=0;
        rand_pattern.clear();
        waiting_for_pattern=true;


    }

    void SimonGame::SimonGameClass::show_pattern(){
        for (int i=0;i<= level;i++){
            printf("\npattern[%d]=%d\n",i,rand_pattern.at(i));
            if(rand_pattern.at(i)==0){
                gpio_put(SimonGame::LED0,1);
                gpio_put(SimonGame::LED1,0);
                gpio_put(SimonGame::LED2,0);
                gpio_put(SimonGame::LED3,0);

            }else if (rand_pattern.at(i)==1){
                gpio_put(SimonGame::LED0,0);
                gpio_put(SimonGame::LED1,1);
                gpio_put(SimonGame::LED2,0);
                gpio_put(SimonGame::LED3,0);

        }else if (rand_pattern.at(i)==2){
                gpio_put(SimonGame::LED0,0);
                gpio_put(SimonGame::LED1,0);
                gpio_put(SimonGame::LED2,1);
                gpio_put(SimonGame::LED3,0);

    }else if (rand_pattern.at(i)==3){
                gpio_put(SimonGame::LED0,0);
                gpio_put(SimonGame::LED1,0);
                gpio_put(SimonGame::LED2,0);
                gpio_put(SimonGame::LED3,1);

    } else{
                gpio_put(SimonGame::LED0,0);
                gpio_put(SimonGame::LED1,0);
                gpio_put(SimonGame::LED2,0);
                gpio_put(SimonGame::LED3,0);

    }
    sleep_ms(SimonGame::BLINK_LED_DELAY);
    gpio_put(SimonGame::LED0,0);
    gpio_put(SimonGame::LED1,0);
    gpio_put(SimonGame::LED2,0);
    gpio_put(SimonGame::LED3,0);
    sleep_ms(SimonGame::BLINK_LED_DELAY);
        }
    }

    uint32_t SimonGame::SimonGameClass::get_random_num(){
        uint32_t k, random=0;
        volatile uint32_t *rnd_reg=(uint32_t *)(ROSC_BASE+ROSC_RANDOMBIT_OFFSET);
        for(k=0;k<32;k++){
            random=random<<1;
            random=random+(0x00000001 &(*rnd_reg));

        }
        return random;
    }
    void SimonGame::SimonGameClass::generate_pattern(){
        int pattern=get_random_num()%4;
        rand_pattern.push_back(pattern);

    }
     void SimonGame::SimonGameClass::check_pattern_gen(){
        if(waiting_for_pattern){
            generate_pattern();
            show_pattern();
            level++;
            waiting_for_pattern = false;
        }
     }
    bool SimonGame::SimonGameClass::is_game_over(){
        return game_over;
    }
