#include "ota.h"
#include "led/Effects/ReprogrammingStatus.h"
#include "led/LedManager.h"
#include "screen.h"

extern LEDManager *gLEDManager;
ReprogrammingStatus *statusEffect;

void OTA_OnStart(void)
{
   Screen::GetInstance().clearLog();
   if (ArduinoOTA.getCommand() == U_FLASH)
      Screen::GetInstance().log.printf("Starting update flash\n");
   else
      Screen::GetInstance().log.printf("Starting update other\n");

   gLEDManager->ClearEffects();
   statusEffect = new ReprogrammingStatus(150);
   gLEDManager->AddEffect(*statusEffect);
   gLEDManager->PlayEffects();
}

void OTA_OnProgress(unsigned int progress, unsigned int total)
{
   Screen::GetInstance().log.printf("\rProgress: %u%%", (progress / (total / 100)));
   statusEffect->SetProgress((float)progress / (float)total);
   gLEDManager->PlayEffects();
}

void OTA_OnError(ota_error_t error)
{
   Screen::GetInstance().log.println("Failed update");
   Screen::GetInstance().log.println(error);
   statusEffect->SetFailed();
   gLEDManager->PlayEffects();
   ESP.restart();
}

void OTA_OnEnd(void)
{
   Screen::GetInstance().log.println("\nDone programming");
   statusEffect->SetSuccess();
   gLEDManager->PlayEffects();
}
