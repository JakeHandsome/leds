#pragma once
#define FASTLED_INTERNAL
#include <FastLED.h>

class Effect
{
 protected:
   int _LEDCount;
   bool _Reversed;
   int _Offset;

 public:
   virtual void DrawEffect(struct CRGB *LEDs) = 0;
};
