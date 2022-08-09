// Basic.ino
// Simple autoConnect usage example

#define WM_ASYNC // Turn on Async mode
#include "AsyncWiFiManager.h" // https://github.com/lbussy/AsyncWiFiManager


void setup() {
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.

    // put your setup code here, to run once:
    Serial.begin(115200);
    
    //AsyncWiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    AsyncWiFiManager wm;

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name
    // ( "AutoConnectAP"), if empty will auto generate SSID, if password is
    // blank it will be an anonymous AP (wm.autoConnect()) then goes into a
    // blocking loop awaiting configuration and will return success result.

    bool res;
    // res = wm.autoConnect(); // Auto generated AP name from chipid, anonymous
    res = wm.autoConnect("AutoConnectAP"); // Anonymous AP
    // res = wm.autoConnect("AutoConnectAP","password"); // Password protected named AP

    if(!res) {
        Serial.println("Failed to connect.");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("Connected.");
    }
}

void loop() {
    // Put your main code here, to run repeatedly:
}
