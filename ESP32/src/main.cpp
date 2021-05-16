#include <Arduino.h>
#include <ArduinoOTA.h>
#include <U8g2lib.h>

#include "led/Effects/UnicornPoop.h"
#include "led/LedManager.h"
#include "my_wifi.h"
#include "nvm.h"
#include "ota.h"
#include "screen.h"
#include "server.h"

void setup()
{
   pinMode(LED_BUILTIN, OUTPUT);
   Screen::GetInstance().begin();
   Nvm_ReadAll();
   Wifi_Init();
   Server_Init();
   ArduinoOTA.setHostname(GetNvmStruct()->name);
   ArduinoOTA.onStart(OTA_OnStart).onProgress(OTA_OnProgress).onError(OTA_OnError).onEnd(OTA_OnEnd);
   ArduinoOTA.begin();
}

void loop()
{
   LEDManager LEDManager(150, 4000);
   UnicornPoop Effect1(70);
   UnicornPoop Reversed(70, 80, true);
   LEDManager.AddEffect(Effect1);
   LEDManager.AddEffect(Reversed);
   for (;;)
   {
      ArduinoOTA.handle();
      LEDManager.PlayEffects();
      // Blink LED to confirm we are alive
      digitalWrite(LED_BUILTIN, ((millis() % 1000) > 500));
   }
}
