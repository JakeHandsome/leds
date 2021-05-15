#include <Arduino.h>
#include <U8g2lib.h>
#include <ArduinoOTA.h>

#include "screen.h"
#include "nvm.h"
#include "ota.h"
#include "server.h"
#include "my_wifi.h"
#include "led/led.h"

void Wifi_Init(void);
void setup()
{
   pinMode(LED_BUILTIN, OUTPUT);
   Screen::GetInstance().begin();
   Nvm_ReadAll();
   Wifi_Init();
   Server_Init();
   ArduinoOTA.setHostname(GetNvmStruct()->name);
   ArduinoOTA
       .onStart(OTA_OnStart)
       .onProgress(OTA_OnProgress)
       .onError(OTA_OnError)
       .onEnd(OTA_OnEnd);
   ArduinoOTA.begin();
   LED_Init();
}

void loop()
{
   ArduinoOTA.handle();
   LED_Task();
   // Blink LED to confirm we are alive
   digitalWrite(LED_BUILTIN, ((millis() % 1000)>500));
}
