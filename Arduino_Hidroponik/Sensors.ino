#include <GravityTDS.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Pins.h"

#define SENS_TDS_SAMPLE_INTERVAL  503
#define SENS_TDS_FILTER_KF        8
#define SENS_PH_SAMPLE_INTERVAL   308
#define SENS_PH_FILTER_KF         6
#define SENS_TEMP_SAMPLE_INTERVAL 1007
#define SENS_TEMP_FILTER_KF       3

#define SENS_PH_CAL_VALUE        0.013685
#define SENS_PH_OFFS_VALUE       0

GravityTDS tds;
OneWire oneWire(SENS_Temp_PIN);
DallasTemperature temp(&oneWire);

uint32_t sens_tds_timer;
uint32_t sens_ph_timer;
uint32_t sens_temp_timer;

float sens_tds_filtValue;
float sens_temp_filtValue;
uint16_t sens_ph_filtValue;

void Sensor_Init(){
  pinMode(SENS_PH_PIN, INPUT);

  temp.begin();
  temp.requestTemperatures();
  temp.setWaitForConversion(false);
  sens_temp_filtValue = temp.getTempCByIndex(0);

  tds.setPin(SENS_TDS_PIN);
  tds.setAref(5.0); 
  tds.setAdcRange(1024);  
  tds.begin();
  tds.setTemperature(sens_temp_filtValue);
  tds.update();

  sens_tds_filtValue = tds.getTdsValue();
  sens_ph_filtValue = analogRead(SENS_PH_PIN);
}

void Sensor_Handler(){
  if(millis() - sens_tds_timer >= SENS_TDS_SAMPLE_INTERVAL){
    sens_tds_filtValue = ((sens_tds_filtValue * SENS_TDS_FILTER_KF) + tds.getTdsValue()) / (SENS_TDS_FILTER_KF + 1);
    tds.update();

    sens_tds_timer = millis();
  }

  if(millis() - sens_ph_timer >= SENS_PH_SAMPLE_INTERVAL){
    sens_ph_filtValue = ((sens_ph_filtValue * SENS_PH_FILTER_KF) + analogRead(SENS_PH_PIN)) / (SENS_PH_FILTER_KF + 1);

    sens_ph_timer = millis();
  }

  if(millis() - sens_temp_timer >= SENS_TEMP_SAMPLE_INTERVAL){
    sens_temp_filtValue = ((sens_temp_filtValue * SENS_TEMP_FILTER_KF) + temp.getTempCByIndex(0)) / (SENS_TEMP_FILTER_KF + 1);
    tds.setTemperature(sens_temp_filtValue);
    temp.requestTemperatures();

    sens_temp_timer = millis();
  }
}

float Sens_Temp_GetValue(){
  return sens_temp_filtValue;
}

float Sens_TDS_GetValue(){
  return sens_tds_filtValue;
}

float Sens_PH_GetValue(){
  return ((int16_t)sens_ph_filtValue - SENS_PH_OFFS_VALUE) * SENS_PH_CAL_VALUE;
}
uint16_t Sens_PH_GetRawValue(){
  return sens_ph_filtValue;
}