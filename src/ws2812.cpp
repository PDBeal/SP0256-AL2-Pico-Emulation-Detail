#include "ws2812.h"

WS2812::WS2812(uint16_t num, uint8_t pin, PIO pio, int sm) {
    alloc(num);

    pixelSm = sm;
    pixelPio = pio;
}

WS2812::WS2812(uint16_t num, uint8_t pin) {
    alloc(num);
    
    PIO pio = pio0;
    int sm;
    // Find a free SM on one of the PIO's
    sm = pio_claim_unused_sm(pio, false); // don't panic
    // Try pio1 if SM not found
    if (sm < 0) {
        pio = pio1;
        sm = pio_claim_unused_sm(pio, true); // panic if no SM is free
    }
    
    pixelSm = sm;
    pixelPio = pio;
    pixelGpio = pin;
}

void WS2812::begin() {
    uint offset = pio_add_program(pixelPio, &ws2812_program);
    ws2812_program_init(pixelPio, pixelSm, offset, pixelGpio, 800000, false);
}

// Allocate 3 bytes per pixel, init to RGB 'off' state:
void WS2812::alloc(uint16_t num)
{
    numLEDs = ((pixels = (uint8_t *)calloc(num, 3)) != NULL) ? num : 0;
}

// Release memory (as needed):
WS2812::~WS2812(void)
{
    if (pixels)
        free(pixels);
}

// Set pixel color from separate 8-bit R, G, B components:
void WS2812::setPixelColor(uint16_t led, uint8_t red, uint8_t green, uint8_t blue)
{
    if (led < numLEDs)
    {
        uint8_t *p = &pixels[led * 3];
        *p++ = red;
        *p++ = green;
        *p++ = blue;
    }
}

// Set pixel color from 'packed' 32-bit RGB value:
void WS2812::setPixelColor(uint16_t led, uint32_t color)
{
    if (led < numLEDs)
    {
        uint8_t *p = &pixels[led * 3];
        *p++ = color >> 16; // Red
        *p++ = color >> 8;  // Green
        *p++ = color;       // Blue
    }
}

// Clear all pixels
void WS2812::clear()
{
    if (pixels != NULL)
    {
        memset(pixels, 0, numLEDs * 3);
    }
}

void WS2812::show(void) {
    // show the neopixels in the buffer
    for (uint16_t i = 0; i < numLEDs; i++) 
    {
        uint8_t redPtr = this->pixels[i*3];
        uint8_t greenPtr = this->pixels[(i*3)+1];
        uint8_t bluePtr = this->pixels[(i*3)+2];

        setPixel(color(redPtr, greenPtr, bluePtr));
    }
}

uint32_t WS2812::color(uint8_t red, uint8_t green, uint8_t blue)
{
    return ((uint32_t)(red) << 8) | ((uint32_t)(green) << 16) | (uint32_t)(blue);
}

void WS2812::setPixel(uint32_t color)
{
    pio_sm_put_blocking(pixelPio, pixelSm, color << 8u);
}

void WS2812::fillPixelColor(uint8_t red, uint8_t green, uint8_t blue)
{
    // fill all the neopixels in the buffer with the specified rgb values.
    for (uint16_t i = 0; i < numLEDs; i++)
    {    
        uint8_t *p = &pixels[i * 3];
        *p++ = red;
        *p++ = green;
        *p++ = blue;
    }
}