//pico SDK includes
#include <stdio.h>
#include <cstdint>
#include "pins_arduino.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/pwm.h"

#include "ws2812.h"

//program includes
#include "allophoneDefs.h"
#include "allophones.h"

//defines
#define neopixelIO1 D7
#define touchIO1 A0
#define touchIO2 A1
#define soundIO1 A3
#define soundIO2 A2
#define rate 90

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals.
WS2812 neopixel(1, neopixelIO1);

#define DELAYVAL 10 // Time (in milliseconds) to pause between pixels

#define FLAG_VALUE 123

//global variables
uint PWMslice;
bool touchValue;

int main(void);
void init();
void setup();
void loop();

void core1_entry();
void core1_loop();

void PlayAllophone(int al);
void PlayAllophones(uint8_t *alist, int listlength);

void SetPWM();

