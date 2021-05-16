#pragma once
#include <array>
#include <vector>
#define FASTLED_INTERNAL
#include "Effects/Effect.h"
#include <FastLED.h>

class LEDManager
{
 private:
   uint16_t _PowerLimit;
   uint16_t _NumberOfLEDs;
   CRGB *_LEDs;
   std::vector<Effect *> Effects;
   float CalculateFPS(float Time) const;
   void Diagnostics(float StartTime) const;

 public:
   LEDManager(const uint16_t NumberOfLEDs, const uint16_t PowerLimitmW);
   ~LEDManager();
   void PlayEffects(void);
   void AddEffect(Effect &Effect);
   void RemoveEffect(Effect &Effect);
   void ClearEffects(void);
};
