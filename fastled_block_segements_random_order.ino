#include "FastLED.h"
#define NUM_LEDS 200
CRGB leds[NUM_LEDS];
#define PIN 9

int v;
int rd;
int gn;
int bl;
int w;
int start;
int fin;
int state;
int last_state;
int pot_read;
const int pos_num = 16;
int pos_array[pos_num];

void setup() {
  FastLED.addLeds<WS2812, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
}


void loop() {
    blocks(0, 0, 255);
    blocks(0, 0, 0);
}

void blocks(int rd, int gn, int bl) {
  randomizelist();
  for (w = 0; w < pos_num; w++) {
    start = pos_array[w];
    start = start * 15;
    fin = start + 15;
    for (v = start; v < fin; v++) {
      setPixel(v, rd, gn, bl);
    }
    showStrip();
    // escape/change function with pot (optional)
    pot_read = analogRead(A0);
    state = map(pot_read, 0, 1023, 1, 10);
    if (state != last_state) {
      return;
    }
    delay(750);
  }
}

void randomizelist() {
  unsigned char chosen[pos_num];
  unsigned char index_pt, log_pt;
  for (index_pt = 0; index_pt < pos_num; index_pt++)
    chosen[index_pt] = 0;
  randomSeed(analogRead(A0));
  for (index_pt = 0; index_pt < pos_num; index_pt++)  {
    int r = random(pos_num - index_pt);
    for (log_pt = 0; log_pt <= r; log_pt++)    {
      r += chosen[log_pt];
    }
    chosen[r] = 1;
    pos_array[index_pt] = r;
  }
}

void showStrip() {
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  strip.show();
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  FastLED.show();
#endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  strip.setPixelColor(Pixel, strip.Color(red, green, blue));
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
#endif
}

void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}
