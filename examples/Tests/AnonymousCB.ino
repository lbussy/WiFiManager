#include <AsyncWiFiManager.h> // https://github.com/lbussy/AsyncWiFiManager

bool _enteredConfigMode = false;

void setup(){
	Serial.begin(115200);
	AsyncWiFiManager wifiManager;

	// wifiManager.setAPCallback([this](AsyncWiFiManager* wifiManager) {
	wifiManager.setAPCallback([&](AsyncWiFiManager* wifiManager) {
		Serial.printf("Entered config mode:ip=%s, ssid='%s'\n", 
                        WiFi.softAPIP().toString().c_str(), 
                        wifiManager->getConfigPortalSSID().c_str());
		_enteredConfigMode = true;
	});
	wifiManager.resetSettings();
	if (!wifiManager.autoConnect()) {
		Serial.printf("*** Failed to connect and hit timeout\n");
		ESP.restart();
		delay(1000);
	}
}

void loop(){

}
