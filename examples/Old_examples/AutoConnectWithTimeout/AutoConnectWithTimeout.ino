#include <AsyncWiFiManager.h> // https://github.com/lbussy/AsyncWiFiManager

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  //AsyncWiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  AsyncWiFiManager AsyncWiFiManager;
  //reset settings - for testing
  //AsyncWiFiManager.resetSettings();

  //sets timeout until configuration portal gets turned off
  //useful to make it all retry or go to sleep
  //in seconds
  AsyncWiFiManager.setConfigPortalTimeout(180);
  
  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if(!AsyncWiFiManager.autoConnect("AutoConnectAP")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.restart();
    delay(5000);
  } 

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
 
}

void loop() {
  // put your main code here, to run repeatedly:

}
