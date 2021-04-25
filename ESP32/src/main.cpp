#include <Arduino.h>
#include <U8g2lib.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

#include "screen.h"
#include "nvm.h"
#include "ota.h"

void Wifi_Init(void);
NvmStructure_T *nvm;
void setup()
{
   pinMode(LED_BUILTIN, OUTPUT);
   Screen::GetInstance().begin();
   Nvm_ReadAll();
   nvm = GetNvmStruct();
   Wifi_Init();
   ArduinoOTA.setHostname(nvm->name);
   ArduinoOTA
       .onStart(OTA_OnStart)
       .onProgress(OTA_OnProgress)
       .onError(OTA_OnError)
       .onEnd(OTA_OnEnd);
   ArduinoOTA.begin();
}

void loop()
{
   ArduinoOTA.handle();
   digitalWrite(LED_BUILTIN, 0);
   delay(500);
   digitalWrite(LED_BUILTIN, 1);
   delay(500);
}

void Wifi_Init()
{
   Screen::GetInstance().log.println("Wifi init");
   Screen::GetInstance().log.printf("ssid: %s\n", nvm->ssid);
   Screen::GetInstance().log.printf("pass: %s\n", nvm->password);
   WiFi.mode(WIFI_MODE_STA);
   WiFi.setHostname(nvm->name);
   WiFi.begin(nvm->ssid, nvm->password);
   for (int i = 0; WiFi.status() != WL_CONNECTED; i++)
   {
      Screen::GetInstance().log.printf("\rConnecting %d %d", i, WiFi.status());
      delay(1000);
   }
   Screen::GetInstance().log.printf("\rConnected! %s\n", WiFi.localIP().toString().c_str());
}
