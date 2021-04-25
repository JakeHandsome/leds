#include "ota.h"
#include "screen.h"

void OTA_OnStart(void)
{
   Screen::GetInstance().clearLog();
   if (ArduinoOTA.getCommand() == U_FLASH)
      Screen::GetInstance().log.printf("Starting update flash\n");
   else
      Screen::GetInstance().log.printf("Starting update other\n");
}

void OTA_OnProgress(unsigned int progress, unsigned int total)
{
   Screen::GetInstance().log.printf("\rProgress: %u%%", (progress / (total / 100)));
}

void OTA_OnError(ota_error_t error)
{
   Screen::GetInstance().log.println("Failed update");
   Screen::GetInstance().log.println(error);
}

void OTA_OnEnd(void)
{
   Screen::GetInstance().log.println("\nDone programming");
}
