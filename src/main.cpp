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
#include "main.h"

void setup()
{
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

  // Setup PWM for allophone
  SetPWM();

  // Setup Touch inputs
  gpio_init(TOUCHIO1);
  gpio_set_dir(TOUCHIO1, GPIO_IN);
  gpio_set_irq_enabled_with_callback(TOUCHIO1, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

  gpio_init(TOUCHIO2);
  gpio_set_dir(TOUCHIO2, GPIO_IN);
  gpio_set_irq_enabled_with_callback(TOUCHIO2, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

  // setup NeoPixel Output
  gpio_init(BUILTIN_NEOPIXEL);
  gpio_set_dir(BUILTIN_NEOPIXEL, GPIO_OUT);

  gpio_init(NEOPIXELIO);
  gpio_set_dir(NEOPIXELIO, GPIO_OUT);

  gpio_init(BUILTIN_NEOPIXEL_PWR);
  gpio_set_dir(BUILTIN_NEOPIXEL_PWR, GPIO_OUT);
  gpio_put(BUILTIN_NEOPIXEL_PWR, HIGH);

  mobo_neopixel.begin();
  mobo_neopixel.clear();

  neopixel.begin();
  neopixel.clear(); // Initialize all pixels to 'off'
} // setup

void loop()
{
  mobo_neopixel.clear();
  mobo_neopixel.setPixelColor(0, mobo_neopixel.Color(15, 25, 205));
  sleep_ms(400);
  mobo_neopixel.show();
  mobo_neopixel.clear();
  mobo_neopixel.setPixelColor(0, mobo_neopixel.Color(103, 25, 205));
  sleep_ms(400);
  mobo_neopixel.show();
  mobo_neopixel.clear();
  mobo_neopixel.setPixelColor(0, mobo_neopixel.Color(233, 242, 205));
  sleep_ms(400);
  mobo_neopixel.show();
  mobo_neopixel.clear();
  mobo_neopixel.setPixelColor(0, mobo_neopixel.Color(233, 23, 23));
  sleep_ms(400);
  mobo_neopixel.show();
  mobo_neopixel.clear();
  mobo_neopixel.setPixelColor(0, mobo_neopixel.Color(12, 66, 101));
  sleep_ms(400);
  mobo_neopixel.show();
  sleep_ms(500);

} // loop

void gpio_callback(uint gpio, uint32_t events)
{
  neopixel.setPixelColor(0, neopixel.Color(0, 0, 25));
  neopixel.show();

  // The quick red fox jumped over the lazy brown dog
  uint8_t alist[] = {DH1, AX, PA3, PA2, KK1, WW, IH, PA2, KK1, PA3, RR2, EH, PA2, DD1, PA3, FF, AA, PA2, KK1, SS, PA3, PA1, JH, UH, MM, PA3, PP, PA3, TT1, PA3, OW, VV, ER1, PA3, DH1, AX, PA3, LL, EY, ZZ, IY, PA3, PA1, BB1, RR2, OW, NN1, PA3, PA2, DD1, AA, PA1, GG1, PA3, PA5, PA3};

  PlayAllophones(alist, sizeof(alist));

  neopixel.setPixelColor(0, neopixel.Color(0, 0, 255));
  neopixel.show();
} // gpio_callback

void PlayAllophone(int al)
{
  int b, s;
  uint8_t v;
  s = allophonesizeCorrected[al];
  for (b = 0; b < s; b++)
  {
    v = allophoneindex[al][b]; // get delta value
    sleep_us(rate);
    pwm_set_both_levels(PWMslice, v, ~v);
  }
} // PlayAllophone

void PlayAllophones(uint8_t *alist, int listlength)
{
  int a;
  for (a = 0; a < listlength; a++)
  {
    PlayAllophone(alist[a]);
  }
} // PlayAllophones

void SetPWM(void)
{
  gpio_init(SOUNDIO1);
  gpio_set_dir(SOUNDIO1, GPIO_OUT);
  gpio_set_function(SOUNDIO1, GPIO_FUNC_PWM);

  gpio_init(SOUNDIO2);
  gpio_set_dir(SOUNDIO2, GPIO_OUT);
  gpio_set_function(SOUNDIO2, GPIO_FUNC_PWM);

  PWMslice = pwm_gpio_to_slice_num(SOUNDIO1);
  pwm_set_clkdiv(PWMslice, 16);
  pwm_set_both_levels(PWMslice, 0x80, 0x80);

  pwm_set_output_polarity(PWMslice, true, false);

  pwm_set_wrap(PWMslice, 256);
  pwm_set_enabled(PWMslice, true);
} // SetPWM
