#include <FastLED.h>
#define LED_PIN 2
#define NUM_LEDS 60

CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // put your main code here, to run repeatedly:
   for(int i = 0; i < NUM_LEDS; i++)
   {
      leds[i] = CRGB(0, 255 - 20*i, 20 * i);
      //FastLED.setBrightness(6 * i);
      FastLED.show();
      delay(50);
   }

   for(int j = NUM_LEDS; j > 0; j--)
   {
      leds[j] = CRGB(20 * j, 0, 255 - 20 * j);
      //FastLED.setBrightness(6-2 * j);
      FastLED.show();
      delay(50);
   }
}
