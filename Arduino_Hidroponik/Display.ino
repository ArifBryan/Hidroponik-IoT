#include <LiquidCrystal_I2C.h>

#define DISPLAY_UPDATE_INTERVAL 250

LiquidCrystal_I2C lcd(0x27,16,2);

uint32_t display_timer;

void Display_Init(){
  lcd.init();
  lcd.backlight();

  lcd.setCursor(1,0);
  lcd.print("Sistem Kontrol");
  lcd.setCursor(3,1);
  lcd.print("Hidroponik");

  delay(1500);
  lcd.clear();
  pinMode(13, OUTPUT);
}

void Display_Handler(){
  char buff[17];
  if(millis() - display_timer >= DISPLAY_UPDATE_INTERVAL){
    lcd.setCursor(0, 0);
    lcd.print(Sens_TDS_GetValue(), 0);
    lcd.print("ppm  ");
    lcd.setCursor(10, 0);
    lcd.print(Sens_Temp_GetValue(), 1);
    lcd.print((char)223);
    lcd.print("C  ");

    lcd.setCursor(3, 1);
    lcd.print("pH:");
    lcd.print(Sens_PH_GetValue(), 1);
    lcd.print("/");
    lcd.print(Control_PH_GetSetPoint(), 1);
    lcd.print("   ");

    digitalWrite(13, !digitalRead(13));

    display_timer = millis();
  }
}

void Display_Update(){
  lcd.clear();
  display_timer = millis() - DISPLAY_UPDATE_INTERVAL; 
}

void Display_WaitForConnection(){
  lcd.setCursor(3,0);
  lcd.print("Connecting");
  lcd.setCursor(5,1);
  lcd.print("to WiFi");
}