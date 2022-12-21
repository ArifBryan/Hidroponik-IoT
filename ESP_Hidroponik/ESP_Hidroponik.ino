#include "Blynk_Config.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer;

void setup() {
  Terminal_Init();
  UnoComm_Init();
  WiFi_Init();
  Blynk_Init();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  Terminal_Handler();
  UnoComm_Handler();
  Blynk_Handler();
}

void Blynk_Init(){
  Blynk.config(BLYNK_AUTH_TOKEN);
  timer.setInterval(1500L, Blynk_UpdateData);
}

void Blynk_Handler(){
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V2){
  float value = param.asFloat();
  UnoData_PH_SP_SetValue(value);
  // Serial.print("RX_BLYNK: ");
  // Serial.println(value);
}

void Blynk_UpdateData(){
  digitalWrite(LED_BUILTIN, HIGH);
  Blynk.virtualWrite(V1, UnoData_PH_GetValue());
  Blynk.virtualWrite(V2, UnoData_PH_SP_GetValue());
  Blynk.virtualWrite(V3, UnoData_TDS_GetValue());
  Blynk.virtualWrite(V4, UnoData_Temp_GetValue());
  digitalWrite(LED_BUILTIN, LOW);
}