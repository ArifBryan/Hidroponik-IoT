#include <SoftwareSerial.h>
#include "Pins.h"

SoftwareSerial unoSerial(UNO_TX_PIN, UNO_RX_PIN);

uint32_t unoComm_timer;

float unoData_PH;
float unoData_PH_SP;
float unoData_TDS;
float unoData_Temp;

void UnoComm_Init(){
  unoSerial.begin(9600);
  unoSerial.println();
}

void UnoComm_Handler(){
  if(unoSerial.available()){
    char rxBuffer[250];
    uint8_t rxBufferPtr = 0;

    rxBuffer[rxBufferPtr++] = unoSerial.read();
    if(rxBuffer[0] != ':'){return;}

    while(1){
      if(unoSerial.available()){
        rxBuffer[rxBufferPtr++] = unoSerial.read();
        if(rxBuffer[rxBufferPtr-1] == '\n'){break;}
      }
    }
    rxBuffer[rxBufferPtr] = 0;
    unoSerial.println(":OK");

    char *data = rxBuffer;

    data = strchr(data, ':') + 1;
    unoData_PH = atof(data);
    data = strchr(data, ',') + 1;
    unoData_PH_SP = atof(data);
    data = strchr(data, ',') + 1;
    unoData_TDS = atof(data);
    data = strchr(data, ',') + 1;
    unoData_Temp = atof(data);

    // Serial.print("PH: ");
    // Serial.print(unoData_PH);
    // Serial.print("/");
    // Serial.print(unoData_PH_SP);
    // Serial.print(" TDS: ");
    // Serial.print(unoData_TDS);
    // Serial.print(" Temp.: ");
    // Serial.print(unoData_Temp);
    // Serial.println();
  }
}

float UnoData_PH_GetValue(){
  return unoData_PH;
}

float UnoData_PH_SP_GetValue(){
  return unoData_PH_SP;
}
void UnoData_PH_SP_SetValue(float sp){
  unoSerial.print(":PH_SP=");
  unoSerial.println(sp);
  unoData_PH_SP = sp;
}

float UnoData_TDS_GetValue(){
  return unoData_TDS;
}

float UnoData_Temp_GetValue(){
  return unoData_Temp;
}