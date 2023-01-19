#include "Pins.h"

#define PUMP_PH_UP    RELAY_1_PIN
#define PUMP_PH_DOWN  RELAY_2_PIN
#define PUMP_MIXER    RELAY_3_PIN

#define PUMP_PH_TIME_MAX  5000

uint32_t pump_ph_timer;
uint32_t pump_ph_time;
bool pump_ph_active;

void Pump_Init(){
  digitalWrite(RELAY_1_PIN, HIGH);
  digitalWrite(RELAY_2_PIN, HIGH);
  digitalWrite(RELAY_3_PIN, HIGH);
  digitalWrite(RELAY_4_PIN, HIGH);

  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);
  pinMode(RELAY_3_PIN, OUTPUT);
  pinMode(RELAY_4_PIN, OUTPUT);
}

void Pump_Handler(){
  if(millis() - pump_ph_timer >= pump_ph_time && pump_ph_active){
    Pump_PH_Stop();
  }
}

bool Pump_PH_Up_GetState(){
  return !digitalRead(PUMP_PH_UP);
}
bool Pump_PH_Down_GetState(){
  return !digitalRead(PUMP_PH_DOWN);
}
bool Pump_Mixer_GetState(){
  return !digitalRead(PUMP_MIXER);
}

void Pump_Mixer_Enable(){
  digitalWrite(PUMP_MIXER, LOW);
}
void Pump_Mixer_Disable(){
  digitalWrite(PUMP_MIXER, HIGH);
}

void Pump_PH_Stop(){
  digitalWrite(PUMP_PH_UP, HIGH);
  digitalWrite(PUMP_PH_DOWN, HIGH);
  pump_ph_active = 0;
}

void Pump_PH_Up_Dose(uint16_t t){
  if(!pump_ph_active){
    pump_ph_active = 1;
    pump_ph_time = (t > PUMP_PH_TIME_MAX ? PUMP_PH_TIME_MAX : t);
    pump_ph_timer = millis();
    digitalWrite(PUMP_PH_UP, LOW);
  }
}

void Pump_PH_Down_Dose(uint16_t t){
  if(!pump_ph_active){
    pump_ph_active = 1;
    pump_ph_time = (t > PUMP_PH_TIME_MAX ? PUMP_PH_TIME_MAX : t);
    pump_ph_timer = millis();
    digitalWrite(PUMP_PH_DOWN, LOW);
  }
}