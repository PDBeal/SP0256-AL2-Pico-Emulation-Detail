/**
 * SPO256 -AL2 
 * samples from https://www.cpcwiki.eu/index.php/SP0256_Allophones
 * 
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "allophones.c"
#include "hardware/pwm.h"
#include "allophoneDefs.h"

//must be pins on the same slice
#define soundIO1 15
#define soundIO2 14

#define rate 90

uint PWMslice;

void PlayAllophone(int al){
    int b,s;
    uint8_t v;
    s=allophonesizeCorrected[al];
    for(b=0;b<s;b++){
        v=allophoneindex[al][b]; //get delta value
        sleep_us(rate);
         pwm_set_both_levels(PWMslice,v,~v);

    }

}

void PlayAllophones(uint8_t *list,int listlength){
   int a;
   for(a=0;a<listlength;a++){
     PlayAllophone(list[a]);
   }
}

void SetPWM(void){
    gpio_init(soundIO1);
    gpio_set_dir(soundIO1,GPIO_OUT);
    gpio_set_function(soundIO1, GPIO_FUNC_PWM);
    
    gpio_init(soundIO2);
    gpio_set_dir(soundIO2,GPIO_OUT);
    gpio_set_function(soundIO2, GPIO_FUNC_PWM);
    
    PWMslice=pwm_gpio_to_slice_num (soundIO1);
    pwm_set_clkdiv(PWMslice,16);
    pwm_set_both_levels(PWMslice,0x80,0x80);
    
    pwm_set_output_polarity(PWMslice,true,false);

    pwm_set_wrap (PWMslice, 256);
    pwm_set_enabled(PWMslice,true);

}


int main() {
    stdio_init_all();
    SetPWM();
        
    uint8_t list[] ={AR,PA5,SS,SS,IY,PA5,TT2,WH,EH,EH,NN1,PA2,PA3,TT2,IY,PA5,FF,OR,PA3,TT2,IY,PA5};

    printf("Starting");

    while(1){    
        PlayAllophones(list,sizeof(list));
        sleep_ms(500);
    }


}//main
