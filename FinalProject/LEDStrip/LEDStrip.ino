#include <FastLED.h>
#define LED_PIN 2
#define NUM_LEDS 60
#define DC_OFFSET  0  // DC offset in mic signal
#define SENSOR_PIN A0
#define TOP       (NUM_LEDS + 2) // Allow dot to go slightly off scale
#define NOISE     10  // Noise/hum/interference in mic signal

CRGB leds[NUM_LEDS];

int measureNum = 60; // number of measurements to take
long soundSignal;
float soundSum = 0;
float avgLevel = 0; // average sound value
unsigned int sample = 0;
int lvl = 10,      // Current "dampened" audio level
    minLvlAvg = 0,      // For dynamic adjustment of graph low & high
    maxLvlAvg = 512;

void setup() {
  // put your setup code here, to run once:
  //strip.begin();
  //strip.show();
  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  LEDS.setBrightness(50);
  FastLED.clear();
  FastLED.show();

  pinMode(SENSOR_PIN, INPUT);
  //pinMode(LED_PIN, OUTPUT);

  Serial.begin (9600);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
CRGB Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void intrepLightColor(int i, int height)
{
  int r, g, b;
  float param = (float)i / (float)height;
  asm(
    "start: \n"
    "ld r16, param \n"
    "ld r17, 0.5 \n"
    "cpc r16, r17 \n"
    "brlt .less \n"
    "brgt .greater \n"
    "jmp .else \n"
    
    ".less: \n"
    "ld r18, r \n"
    "ld r19, 2 \n"
    "mulf r16, r19"
    "ld r19, 1 \n"
    "sub r19, r16 \n"
    "ld r20, 255 \n"
    "mulf r19, r20 \n"
    "st r, r19 \n" 

    "ld r16, param \n"
    "ld r17, g \n"
    "ld r18, 2 \n"
    "mulf r16, r18 \n"
    "ld r18, 255 \n"
    "mulf r16, r18 \n"
    "st g, r16 \n"

    ".greater: \n"



    ".else: \n"
  );
  
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t  i;
  uint16_t minLvl, maxLvl;
  int      n, height;
  
  n   = analogRead(SENSOR_PIN);  // Raw reading from mic 
  n   = abs(n - 512 - DC_OFFSET); // Center on zero
  n   = (n <= NOISE) ? 0 : (n - NOISE); // Remove noise/hum
  lvl = ((lvl * 7) + n) >> 3;    // "Dampened" reading (else looks twitchy)
 
  // Calculate bar height based on dynamic min/max levels (fixed point):
  height = TOP * (lvl - minLvlAvg) / (long)(maxLvlAvg - minLvlAvg);
 
  if(height > TOP) 
    height = TOP;
  //if(height > peak)     
    //peak = height; // Keep 'peak' dot at top

   height = abs(height - NUM_LEDS + 2) * 2;
   if(height <= 2)
    height = 0;
    
   for(i = 0; i < NUM_LEDS; i++) 
   {
      if(i >= height)               
        leds[i] = CRGB(0, 0, 0);
      else
      {
        float param = (float)i / (float)height;
        int r, g, b;

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
        leds[i] = CRGB(r, g, b);
      }
  }
  LEDS.setBrightness(10);
  FastLED.show();
  delay(50);
  
  //Serial.print("Sound Level: ");
  //Serial.println (height);
}
