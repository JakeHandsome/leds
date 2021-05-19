#include <Arduino.h>
#include <ArduinoOTA.h>
#include <U8g2lib.h>

#include "led/Effects/ReprogrammingStatus.h"
#include "led/Effects/UnicornPoop.h"
#include "led/LedManager.h"
#include "my_wifi.h"
#include "nvm.h"
#include "ota.h"
#include "screen.h"
#include "server.h"

LEDManager *gLEDManager;

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
   gLEDManager = new LEDManager(150, 4000);
   UnicornPoop Effect1(70);
   UnicornPoop Reversed(70, 80, true);
   gLEDManager->AddEffect(Effect1);
   gLEDManager->AddEffect(Reversed);
   for (;;)
   {
      ArduinoOTA.handle();
      gLEDManager->PlayEffects();
   }
}
