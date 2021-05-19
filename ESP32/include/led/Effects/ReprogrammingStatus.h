#pragma once
#include "Effect.h"
#include <ArduinoOTA.h>

class ReprogrammingStatus : public Effect
{
   enum Status
   {
      Normal,
      Failed,
      Success
   };

 private:
   float _Progress;
   bool _ProgressUpdated;
   enum Status _Status;

 public:
   ReprogrammingStatus(uint16_t NumberOfLEDs, uint16_t Offset = 0U, bool Reversed = false);
   virtual void DrawEffect(struct CRGB *LED);
   void SetProgress(float progress);
   void SetSuccess();
   void SetFailed();
};
