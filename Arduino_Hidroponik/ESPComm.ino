#include <SoftwareSerial.h>
#include "Pins.h"

#define ESPCOMM_TRANSMISSION_INTERVAL 1000

SoftwareSerial espSerial(ESP_TX_PIN, ESP_RX_PIN);

uint32_t espComm_timer;
bool espComm_isConnected;

void ESPComm_Init(){
  espSerial.begin(9600);
  espSerial.println();
}

void ESPComm_Handler(){
  if(millis() - espComm_timer >= ESPCOMM_TRANSMISSION_INTERVAL){
    espSerial.print(":");
    espSerial.print(Sens_PH_GetValue());
    espSerial.print(",");
    espSerial.print(Control_PH_GetSetPoint());
    espSerial.print(",");
    espSerial.print(Sens_TDS_GetValue());
    espSerial.print(",");
    espSerial.print(Sens_Temp_GetValue());
    espSerial.println();

    espComm_timer = millis();
  }

  if(espSerial.available()){
    char rxBuffer[250];
    uint8_t rxBufferPtr = 0;

    rxBuffer[rxBufferPtr++] = espSerial.read();
    if(rxBuffer[0] != ':'){return;}

    while(1){
      if(espSerial.available()){
        rxBuffer[rxBufferPtr++] = espSerial.read();
        if(rxBuffer[rxBufferPtr-1] == '\n'){break;}
      }
    }
    rxBuffer[rxBufferPtr] = 0;

    char *data = rxBuffer;

    if(MatchString(rxBuffer, ":OK")){
      espComm_isConnected = 1;
    }
    else if(MatchString(rxBuffer, ":PH")){
      data = strchr(data, '=') + 1;
      Control_PH_SetPoint(atof(data));
    }
  }
}

bool ESPComm_IsConnected(){
  return espComm_isConnected;
}

bool MatchString(char data, const char *str){
  return strncmp(data, str, strlen(str)) == 0;
}