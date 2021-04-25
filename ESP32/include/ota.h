#ifndef OTA_H
#define OTA_H
#include <ArduinoOTA.h>

void OTA_OnStart(void);
void OTA_OnEnd(void);
void OTA_OnProgress(unsigned int progress, unsigned int total);
void OTA_OnError(ota_error_t error);
#endif
