#include <ESP8266AutoWifi.h>

ESPAutoWifi aWifi("Hidroponik");

void WiFi_Init(){
  Serial.println("Connecting to WiFi");

  //aWifi.reset(); // Untuk reset WiFi
  if(aWifi.connect() != WL_CONNECTED){
    Serial.println("No saved WiFi!");
    aWifi.reset();
    aWifi.startAP();
    aWifi.startConfig();
    Serial.println("Connect to " + aWifi.getAPSSID());
    Serial.println("Setup WiFi configuration at 192.168.4.1");
    while(!aWifi.checkCredentials());
    aWifi.connect();
  }
  
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}