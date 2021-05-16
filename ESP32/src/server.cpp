#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <pb_encode.h>


#include "nvm.h"
#include "protobuf/ESP32Init.pb.h"
#include "screen.h"


#define APIHEADER(s) "/JakeHandsomeLEDApi" s

AsyncWebServer server(80);

void Server_Init()
{
   server.on(APIHEADER("/init"), HTTP_GET, [](AsyncWebServerRequest *request) {
      static uint32_t number = 0;
      uint8_t buffer[ESP32Init_size];
      ESP32Init message = ESP32Init_init_zero;
      pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
      message.has_name = true;
      strcpy(message.name, GetNvmStruct()->name);
      number++;
      pb_encode(&stream, ESP32Init_fields, &message);
      request->send_P(200, "application/protobuf", (const uint8_t *)&buffer, stream.bytes_written);
   });

   server.begin();
}
