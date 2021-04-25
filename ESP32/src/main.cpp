#include <Arduino.h>
#include <U8g2lib.h>
#include <WiFi.h>

#include "screen.h"
#include "nvm.h"
Screen Console;
void Wifi_Init(void);
NvmStructure_T * nvm;
void setup()
{
   pinMode(LED_BUILTIN, OUTPUT);
   Console.begin();
   Nvm_ReadAll(Console);
   nvm = GetNvmStruct();
   /*
   if (strlen(nvm->ssid) == 0)
   {
      Screen.log.println("Resetting Nvm values");
      strcpy(nvm->ssid,"Mumbo");
      strcpy(nvm->password, "fourwordsalluppercase");
      Nvm_WriteAll(Screen);
   }*/
   Wifi_Init();
}

void loop()
{
   digitalWrite(LED_BUILTIN, 0);
   delay(500);
   digitalWrite(LED_BUILTIN, 1);
   delay(500);
}

void Wifi_Init()
{
   Console.log.println("Wifi init");
   char* ssid = nvm->ssid;
   char* password = nvm->password;
   Console.log.printf("ssid: %s\n", ssid);
   Console.log.printf("pass: %s\n", password);
   WiFi.begin(ssid, password);
   for (int i = 0; WiFi.status() != WL_CONNECTED; i++)
   {
      Console.log.printf("\rConnecting %d %d", i, WiFi.status());
      delay(1000);
   }
   Console.log.printf("\rConnected! %s\n",WiFi.localIP().toString().c_str());
}
