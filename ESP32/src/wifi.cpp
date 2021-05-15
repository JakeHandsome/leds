#include <WiFi.h>
#include "screen.h"
#include "nvm.h"

void Wifi_Init()
{
   NvmStructure_T *nvm = GetNvmStruct();

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
