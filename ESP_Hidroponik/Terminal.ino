#define TERMINAL_TRANSMISSION_INTERVAL 500

uint32_t terminal_timer;

void Terminal_Init(){
  Serial.begin(115200);
  Serial.println();

  Serial.println("================");
  Serial.println("   Sistem IoT   ");
  Serial.println("   Hidroponik   ");
  Serial.println("----------------");
  Serial.println(" Convetech 2022 ");
  Serial.println("================");
  Serial.println();
}

void Terminal_Handler(){
  if(millis() - terminal_timer >= TERMINAL_TRANSMISSION_INTERVAL){
    
    terminal_timer = millis();
  }
}