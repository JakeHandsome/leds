#include <EEPROM.h>
#include "nvm.h"

static NvmStructure_T nvm;

#define NVM_INDEX(i) i * (MAX_NVM_STRING_LENGTH + 1)
void Nvm_ReadAll()
{
   if (!EEPROM.begin(sizeof(NvmStructure_T)))
   {
      Screen::GetInstance().log.println("Nvm readAll failed");
      while(1){}
   }
   Screen::GetInstance().log.println("Reading Nvm");
   EEPROM.readString(NVM_INDEX(0), nvm.ssid, 31);
   EEPROM.readString(NVM_INDEX(1), nvm.password,31);
   EEPROM.readString(NVM_INDEX(2), nvm.name,31);
}

void Nvm_WriteAll()
{
   EEPROM.writeString(NVM_INDEX(0), nvm.ssid);
   EEPROM.writeString(NVM_INDEX(1), nvm.password);
   EEPROM.writeString(NVM_INDEX(2), nvm.name);
   if (!EEPROM.commit())
   {
      Screen::GetInstance().log.println("Nvm writeAll failed");
      while(1){}
   }
}

NvmStructure_T * GetNvmStruct()
{
   return &nvm;
}
