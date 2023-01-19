#define CONTROL_INTERVAL  3000 // Default : 10000

#define CONTROL_PH_GAIN   100

uint32_t control_timer;
float control_ph_setpoint;
float control_ph_tolerance;
float control_ph_error;

void Control_Handler(){
  if(millis() - control_timer >= CONTROL_INTERVAL){
    control_ph_error = control_ph_setpoint - Sens_PH_GetValue();
    if(control_ph_error < -control_ph_tolerance){
      // Override control gain
      Pump_PH_Down_Dose(3000);
      //Pump_PH_Down_Dose(abs(control_ph_error * CONTROL_PH_GAIN));
      Pump_Mixer_Enable();
    }
    else if(control_ph_error > control_ph_tolerance){
      // Override control gain
      Pump_PH_Up_Dose(3000);
      //Pump_PH_Up_Dose(control_ph_error * CONTROL_PH_GAIN);
      Pump_Mixer_Enable();
    }
    else{
      Pump_PH_Stop();
      Pump_Mixer_Disable();
    }

    control_timer = millis();
  }
}

void Control_PH_SetPoint(float sp){
  control_ph_setpoint = sp;
}
float Control_PH_GetSetPoint(){
  return control_ph_setpoint;
}
void Control_PH_SetTolerance(float tol){
  control_ph_tolerance = tol;
}

float Control_PH_GetError(){
  return control_ph_error;
}