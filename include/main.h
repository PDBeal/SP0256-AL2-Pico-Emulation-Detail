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

// How many NeoPixels are attached?
#define LED_COUNT 1

#define rate 90

// const for Built-in LED
const uint LED_PIN = LED_BUILTIN;

// const for speaker pins (differential)
const uint SOUNDIO1 = 29;
const uint SOUNDIO2 = 28;

// const for touch inputs
const uint TOUCHIO1 = 26;
const uint TOUCHIO2 = 27;

// Define RGB pin
const uint NEOPIXELIO = 1;
const uint BUILTIN_NEOPIXEL_PWR = 11;
const uint BUILTIN_NEOPIXEL = 12;

// Declare our NeoPixel strip object:
Adafruit_NeoPixel neopixel(LED_COUNT, NEOPIXELIO, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel mobo_neopixel(LED_COUNT, BUILTIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

uint PWMslice;

void gpio_event_string(char *buf, uint32_t events);

void gpio_callback(uint gpio, uint32_t events);

void PlayAllophone(int al);

void PlayAllophones(uint8_t *alist, int listlength);

void SetPWM(void);

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