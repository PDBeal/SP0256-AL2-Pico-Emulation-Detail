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
}

void PlayAllophones(uint8_t *alist, int listlength)
{
  int a;
  for (a = 0; a < listlength; a++)
  {
    PlayAllophone(alist[a]);
  }
}

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
}

void setup()
{
  // Setup PWM for allophone
  SetPWM();

  // Setup Touch inputs
  pinMode(TOUCHIO1, INPUT);
  pinMode(TOUCHIO2, INPUT);

  // setup NeoPixel Output
  pinMode(NEOPIXELIO, OUTPUT);

  neopixel.begin();
  neopixel.clear(); // Initialize all pixels to 'off'
}

void loop()
{
  bool touch1 = digitalReadFast(TOUCHIO1);
  bool touch2 = digitalReadFast(TOUCHIO2);

  if (touch1 || touch2)
  {
    neopixel.setPixelColor(0, 0, 25, 0);
    neopixel.show();

    // The quick red fox jumped over the lazy brown dog
    uint8_t alist[] = {DH1, AX, PA3, PA2, KK1, WW, IH, PA2, KK1, PA3, RR2, EH, PA2, DD1, PA3, FF, AA, PA2, KK1, SS, PA3, PA1, JH, UH, MM, PA3, PP, PA3, TT1, PA3, OW, VV, ER1, PA3, DH1, AX, PA3, LL, EY, ZZ, IY, PA3, PA1, BB1, RR2, OW, NN1, PA3, PA2, DD1, AA, PA1, GG1, PA3, PA5, PA3};

    PlayAllophones(alist, sizeof(alist));
  }
  else
  {
    neopixel.setPixelColor(0, 0, 255, 0);
    neopixel.show();
    delay(100);
  }

} // loop
