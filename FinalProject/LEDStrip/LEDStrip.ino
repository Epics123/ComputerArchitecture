#include <FastLED.h>
#define LED_PIN 2
#define NUM_LEDS 60
#define DC_OFFSET  0  // DC offset in mic signal
#define SENSOR_PIN A0
#define TOP       (NUM_LEDS + 2) // Allow dot to go slightly off scale
#define NOISE     10  // Noise/hum/interference in mic signal

CRGB leds[NUM_LEDS];
int lvl = 10,      // Current "dampened" audio level
    minLvlAvg = 0,      // For dynamic adjustment of graph low & high
    maxLvlAvg = 512;

uint16_t delay_count = 16000000 / 4000; // CPU frequcency divided by 4000 (needed for delay function) 

void setup() {  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  LEDS.setBrightness(50);
  FastLED.clear();
  FastLED.show();

  pinMode(SENSOR_PIN, INPUT);
  Serial.begin (9600);
}

// Re-imlplementaion of delay function in assembly
void delayMS(uint8_t ms)
{
uint16_t cnt;
asm volatile (
"\n"
"L_dl1%=:" "\n\t"
"mov %A0, %A2" "\n\t"
"mov %B0, %B2" "\n"
"L_dl2%=:" "\n\t"
"sbiw %A0, 1" "\n\t"
"brne L_dl2%=" "\n\t"
"dec %1" "\n\t"
"brne L_dl1%=" "\n\t"
: "=&w" (cnt)
: "r" (ms), "r" (delay_count)
);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t  i;
  uint16_t minLvl, maxLvl;
  int n;
  int height;
  
  n   = analogRead(SENSOR_PIN);  // Raw reading from mic 
  n   = abs(n - 512 - DC_OFFSET); // Center on zero
  n   = (n <= NOISE) ? 0 : (n - NOISE); // Remove noise/hum
  lvl = ((lvl * 7) + n) >> 3;    // "Dampened" reading (else looks twitchy)
 
  // Calculate bar height based on dynamic min/max levels (fixed point):
  height = TOP * (lvl - minLvlAvg) / (maxLvlAvg - minLvlAvg);
 
  if(height > TOP) 
    height = TOP;
  //if(height > peak)     
    //peak = height; // Keep 'peak' dot at top

   height = abs(height - NUM_LEDS + 2) * 2;
   if(height <= 2)
    height = 0;

   // loop throught LEDs to set colors in a rainbow effect
   for(i = 0; i < NUM_LEDS; i++) 
   {
      if(i >= height)               
        leds[i] = CRGB(0, 0, 0);
      else
      {
        // calculate color interpolation parameter
        float param = (float)i / (float)height;
        int r, g, b;

        // interpolate r, g, and b values based on param
        if(param < 0.5)
        {
           r = 255 * (1 - (2 * param));
           g = 255 * (2 * param);
           b = 0;
        }
        else if(param > 0.5)
        {
           g = 255 * (1 - (2 * (param - 0.5)));
           b = 255 * (2 * (param - 0.5));
           r = 0;
        }
        else
        {
           r = 0;
           b = 0;
           g = 255;
        }
        // Set final LED color
        leds[i] = CRGB(r, g, b);
      }
  }
  LEDS.setBrightness(10);
  FastLED.show();
  delayMS(50);
}
