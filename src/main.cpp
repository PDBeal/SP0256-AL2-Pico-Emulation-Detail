#include "main.h"

void PlayAllophone(int al){
    int b,s;
    uint8_t v;
    
    s = allophone[al].allophoneSize;
    for(b=0; b<s; b++){
        v = allophone[al].allophoneIndex[b]; //get delta value
        sleep_us(rate);
        pwm_set_both_levels(PWMslice,v,~v);
    }
}

void PlayAllophones(uint8_t *alist, int listlength){
   int a;
   for(a=0;a<listlength;a++){
     PlayAllophone(alist[a]);
   }
}

void SetPWM() {
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

void init() {
  stdio_init_all();

  gpio_init(touchIO1);
  gpio_init(touchIO2);
}

void setup() {
  // put your setup code here, to run once:
  //neopixel.begin();
  
  gpio_set_dir(touchIO1, GPIO_IN);
  gpio_set_dir(touchIO2, GPIO_IN);

  SetPWM();
}

void core1_entry() {
    multicore_fifo_push_blocking(FLAG_VALUE);
 
    uint32_t g = multicore_fifo_pop_blocking();
 
    if (g != FLAG_VALUE)
        printf("Hmm, that's not right on core 1!\n");
    else
        printf("Its all gone well on core 1!\n");
 
    while (1)
        core1_loop();
}

void core1_loop() {
  //neopixel.clear(); // set all pixel colors to 'off'

  //for (int red=0; red<255; red++) {
    //for (int blue=0; blue<255; blue++) {
      //for (int green=0; green<255; green++) {
        //neopixel.setPixelColor(0, neopixel.Color(green, red, blue));
        //neopixel.show();   // Send the updated pixel colors to the hardware.
        //sleep_ms(DELAYVAL); // Pause before next pass through loop
      //}
    //}
  //}
}

void loop() {
  // put your main code here, to run repeatedly:
  touchValue = gpio_get(touchIO1) || gpio_get(touchIO2);

  if (touchValue) { 
    //neopixel.setPixelColor(0, neopixel.Color(0, 25, 0));
    //neopixel.show();   // Send the updated pixel colors to the hardware.
    
    //uint8_t alist[] ={HH,EH,LL,AX,OW,PA5,WW,OR,LL,DD1};
    //uint8_t alist[] ={AR,PA5,SS,SS,IY,PA5,TT2,WH,EH,EH,NN1,PA2,PA3,TT2,IY,PA5,FF,OR,PA3,TT2,IY,PA5};
    //uint8_t alist[] ={HH,EH,LL,AX,OW,PA5,PA5,JH,EH,NN2,SS,NN};
    uint8_t alist[] ={HH,EH,LL,AX,OW};

    PlayAllophones(alist,sizeof(alist));

  }

  //Serial.println("Touch Input = " && touchValue);
}

int main(void) {
	init();

	setup();

  printf("Hello, multicore!\n");
  
  multicore_launch_core1(core1_entry);
 
  // Wait for it to start up
  uint32_t g = multicore_fifo_pop_blocking();
 
  if (g != FLAG_VALUE)
    printf("Hmm, that's not right on core 0!\n");
  else {
    multicore_fifo_push_blocking(FLAG_VALUE);
    printf("It's all gone well on core 0!\n");
  }

	for (;;) {
		loop();
	}
        
	return 0;
}