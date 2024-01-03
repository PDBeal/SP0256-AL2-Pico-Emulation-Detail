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

void init() {}

void initVariant() {}

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

    // uint8_t alist[] = {HH, EH, LL, AX, OW, PA5, WW, OR, LL, DD1};
    // uint8_t alist[] ={AR,PA5,SS,SS,IY,PA5,TT2,WH,EH,EH,NN1,PA2,PA3,TT2,IY,PA5,FF,OR,PA3,TT2,IY,PA5};
    //uint8_t alist[] = {HH, EH, LL, AX, OW, PA5,AX,EL,EH,PA2,KK1,SS,AE,NN1,PA2,DD1,RR2,IH,AX,PA3};
    //uint8_t alist[] = {HH1, EH, LL, OW, PA3, AX, EL, EH, PA2, KK1, SS, AE, NN1, PA2, DD1, RR2, IH, AX, PA3}; // Hello Alexandria
    //uint8_t alist[] = {HH1, EH, LL, OW, PA3, PA1, JH, EH, NN1, SS, AX, NN1, PA3};                            // Hello Jenson
    uint8_t alist[] = {HH1, EH, LL, OW, PA3, AX, EL, EH, PA2, KK1, SS, AE, NN1, PA2, DD1, RR2, IH, AX, PA3, PA4, PA3, HH1, EH, LL, OW, PA3, PA1, JH, EH, NN1, SS, AX, NN1, PA3};

    //[AL] + [IG] + [ZAAN] + [DREE] + [UH]

    PlayAllophones(alist, sizeof(alist));
  }
  else
  {
    neopixel.setPixelColor(0, 0, 255, 0);
    neopixel.show();
  }

} // loop
