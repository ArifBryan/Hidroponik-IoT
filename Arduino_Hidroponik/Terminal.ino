#define TERMINAL_TRANSMISSION_INTERVAL 500

uint32_t terminal_timer;

void Terminal_Init(){
  Serial.begin(115200);
  Serial.println();

  Serial.println("================");
  Serial.println(" Sistem Kontrol ");
  Serial.println("   Hidroponik   ");
  Serial.println("----------------");
  Serial.println(" Convetech 2022 ");
  Serial.println("================");
  Serial.println();
}

void Terminal_Handler(){
  if(millis() - terminal_timer >= TERMINAL_TRANSMISSION_INTERVAL){
    Serial.print("PH: ");
    Serial.print(Sens_PH_GetValue());
    Serial.print("/");
    Serial.print(Control_PH_GetSetPoint());
    Serial.print(" TDS: ");
    Serial.print(Sens_TDS_GetValue());
    Serial.print(" Temp.: ");
    Serial.print(Sens_Temp_GetValue());
    Serial.print(" P_UP: ");
    Serial.print(Pump_PH_Up_GetState());
    Serial.print(" P_DN: ");
    Serial.print(Pump_PH_Down_GetState());
    Serial.print(" P_MX: ");
    Serial.print(Pump_Mixer_GetState());
    Serial.println();

    terminal_timer = millis();
  }
}