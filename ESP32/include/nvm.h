#ifndef NVM_H
   #define NVM_H
   #include "screen.h"

   #define MAX_NVM_STRING_LENGTH 30
   typedef struct
   {
      char ssid[MAX_NVM_STRING_LENGTH + 1];
      char password[MAX_NVM_STRING_LENGTH + 1];
      char name[MAX_NVM_STRING_LENGTH + 1];
   } NvmStructure_T;

   NvmStructure_T *GetNvmStruct();
   void Nvm_ReadAll();
   void Nvm_WriteAll();
#endif
