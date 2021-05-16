#include "led/LedManager.h"
#include "Arduino.h"
#include "screen.h"

LEDManager::LEDManager(const uint16_t NumberOfLeds, const uint16_t PowerLimit)
{
   _PowerLimit = PowerLimit;
   _NumberOfLEDs = NumberOfLeds;
   _LEDs = new CRGB[NumberOfLeds];
   memset(_LEDs, 0, NumberOfLeds * sizeof(CRGB));
   pinMode(SS, OUTPUT);
   FastLED.addLeds<WS2812B, SS, EOrder::GRB>(_LEDs, NumberOfLeds);
   FastLED.setMaxPowerInMilliWatts(PowerLimit);
   FastLED.setBrightness(255);
}

LEDManager::~LEDManager()
{
   delete[] _LEDs;
}

void LEDManager::PlayEffects()
{
   float start_time = millis() / 1000.f;
   for (auto &e : Effects)
   {
      e->DrawEffect(_LEDs);
   }
   FastLED.show();
   Diagnostics(start_time);
}

float LEDManager::CalculateFPS(float seconds) const
{
   static float framesPerSecond;
   framesPerSecond = (framesPerSecond * .9) + (1.0 / seconds * .1);
   return framesPerSecond;
}

void LEDManager::Diagnostics(float StartTime) const
{
   float fps = CalculateFPS(millis() / 1000.f - StartTime);

   uint32_t PowerUsage = calculate_unscaled_power_mW(_LEDs, _NumberOfLEDs);
   if (PowerUsage > _PowerLimit)
   {
      digitalWrite(BUILTIN_LED, 1);
   }
   EVERY_N_MILLISECONDS(1000)
   {
      Screen::GetInstance().log.printf("PowerUsage:%d\nFPS:%.1lf\n", PowerUsage, fps);
   }
}

void LEDManager::AddEffect(Effect &Effect)
{
   Effects.push_back(&Effect);
}
