
void setup() {
  Terminal_Init();
  Display_Init();
  Pump_Init();
  Sensor_Init();
  ESPComm_Init();

  Control_PH_SetPoint(7.0);
  Control_PH_SetTolerance(0.5);

  WaitForESP();
}

void loop() {
  Sensor_Handler();
  Control_Handler();
  Pump_Handler();
  ESPComm_Handler();
  Terminal_Handler();
  Display_Handler();
}

void WaitForESP(){
  Serial.println("Waiting for ESP to boot...");
  Display_WaitForConnection();
  while(!ESPComm_IsConnected()){
    Sensor_Handler();
    ESPComm_Handler();
  }
  Display_Update();
}