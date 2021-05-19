#include "led/Effects/ReprogrammingStatus.h"
#include "screen.h"

ReprogrammingStatus::ReprogrammingStatus(uint16_t NumberOfLEDs, uint16_t Offset, bool Reversed)
{
   _Offset = Offset;
   _LEDCount = NumberOfLEDs;
   _Reversed = Reversed;
   _Progress = 0;
   _ProgressUpdated = false;
   _Status = Status::Normal;
}

void ReprogrammingStatus::DrawEffect(struct CRGB *LED)
{
   switch (_Status)
   {
   case Status::Normal:
      if (_ProgressUpdated)
      {
         _ProgressUpdated = false;
         // Draw a color gradient red to green
         fill_gradient_RGB(LED, _LEDCount, CRGB::Red, CRGB::Green);
         float filledLEDs = _Progress * _LEDCount;
         int fadeIndex = filledLEDs;
         float fillPercentage = filledLEDs - (long)filledLEDs;
         int unfilledLEDs = _LEDCount - filledLEDs;
         int fadeAmount = (255 * (1.0f - fillPercentage));

         LED[fadeIndex].fadeToBlackBy(fadeAmount);
         // Turn a certain number of pixel black based on the status
         if (_Progress < 1.f)
            fill_solid(&LED[fadeIndex + 1], unfilledLEDs, CRGB::Black);
         else
            fill_solid(LED, _LEDCount, CRGB::Green);
      }
      break;
   case Status::Failed:
      fill_solid(LED, _LEDCount, CRGB::Red);
      break;
   case Status::Success:
      fill_solid(LED, _LEDCount, CRGB::Green);
      break;
   }
}

void ReprogrammingStatus::SetProgress(float progress)
{
   if (_Progress != progress)
   {
      _Progress = progress;
      _ProgressUpdated = true;
   }
}

void ReprogrammingStatus::SetFailed()
{
   _Status = Status::Failed;
}
void ReprogrammingStatus::SetSuccess()
{
   _Status = Status::Success;
}
