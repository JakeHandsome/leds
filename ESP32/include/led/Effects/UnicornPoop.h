#pragma once
#include "Effect.h"

class UnicornPoop : public Effect
{
 private:
   int _Hue;

 public:
   UnicornPoop(uint16_t NumberOfLEDs, uint16_t Offset = 0U, bool Reversed = false);
   ~UnicornPoop();
   virtual void DrawEffect(struct CRGB *LED);
};
