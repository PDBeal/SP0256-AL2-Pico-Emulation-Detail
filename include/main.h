#pragma
/**
 * SPO256 -AL2
 * samples from https://www.cpcwiki.eu/index.php/SP0256_Allophones
 *
 * Pico code Derek Woodroffe 4/5/2022
 *
 * Adapted for Hackerbox 0098 - HAL9000
 * P.Beal - 2023/12/31
 *
 */

// pico SDK includes
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <Adafruit_NeoPixel.h>

// program includes
#include "allophones.h"
#include "allophoneDefs.h"

// Define speaker pins (differential)
#define SOUNDIO1 A3
#define SOUNDIO2 A2

// Define touch inputs
#define TOUCHIO1 A0
#define TOUCHIO2 A1

// Define RGB pin
#define NEOPIXELIO D7

// How many NeoPixels are attached?
#define LED_COUNT 1

#define rate 90

// Declare our NeoPixel strip object:
Adafruit_NeoPixel neopixel(LED_COUNT, NEOPIXELIO, NEO_RGB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

uint PWMslice;

void PlayAllophone(int al);

void PlayAllophones(uint8_t *alist, int listlength);

void SetPWM(void);

void init();

void initVariant();

void setup();

void loop();

int main(void)
{
    init();

    initVariant();

#if defined(USBCON)
    USBDevice.attach();
#endif

    setup();

    for (;;)
    {
        loop();
        if (serialEventRun)
            serialEventRun();
    }

    return 0;
} // main

/**
#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}
**/