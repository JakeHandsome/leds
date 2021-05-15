#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include "screen.h"

#define LED_PIN SS
#define NUM_LEDS 150
#define MAX_POWER_MW 5000

static void Diagnostics(void);

static CRGB my_LEDS[NUM_LEDS] = {0};

uint8_t hue = 0;

float timeStart;

void LED_Init(void)
{
   pinMode(LED_PIN, OUTPUT);
   FastLED.addLeds<WS2812B, LED_PIN, GRB>(my_LEDS, NUM_LEDS);
   FastLED.setMaxPowerInMilliWatts(MAX_POWER_MW);
   FastLED.setBrightness(255);
}

void LED_Task(void)
{
   timeStart = millis() / 1000.f;
   fill_rainbow(my_LEDS, NUM_LEDS, hue += 16, 4);
   FastLED.show();
   Diagnostics();
   delay(33);
}

float FramesPerSecond(float seconds)
{
  static float framesPerSecond;
  framesPerSecond = (framesPerSecond * .9) + (1.0 / seconds * .1);
  return framesPerSecond;
}

static void Diagnostics(void)
{
   float fps = FramesPerSecond(millis() / 1000.f - timeStart);

   uint32_t PowerUsage = calculate_unscaled_power_mW(my_LEDS, NUM_LEDS);
   if (PowerUsage > MAX_POWER_MW)
   {
      digitalWrite(BUILTIN_LED, 1);
   }
   EVERY_N_MILLISECONDS(1000)
   {
      Screen::GetInstance().log.printf("PowerUsage:%d\nFPS:%.1lf\n", PowerUsage, fps);
   }
}
