#include "led/Effects/UnicornPoop.h"

UnicornPoop::UnicornPoop(uint16_t NumberOfLed, uint16_t Offset, bool Reversed)
{
   _LEDCount = NumberOfLed;
   _Hue = 0;
   _Reversed = Reversed;
   _Offset = Offset;
}

void UnicornPoop::DrawEffect(struct CRGB *Leds)
{
   if (_Reversed)
      fill_rainbow(&Leds[_Offset], _LEDCount, _Hue -= 16, 4);
   else
      fill_rainbow(&Leds[_Offset], _LEDCount, _Hue += 16, 4);
   delay(28);
}

UnicornPoop::~UnicornPoop()
{
}
