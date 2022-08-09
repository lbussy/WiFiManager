#include <AsyncWiFiManager.h> // https://github.com/lbussy/AsyncWiFiManager

bool _enteredConfigMode = false;

void setup(){
	Serial.begin(115200);
	AsyncWiFiManager wm;

	// wm.setAPCallback([this](AsyncWiFiManager* wm) {
	wm.setAPCallback([&](AsyncWiFiManager* wm) {
		Serial.printf("Entered config mode:ip=%s, ssid='%s'\n", 
                        WiFi.softAPIP().toString().c_str(), 
                        wm->getConfigPortalSSID().c_str());
		_enteredConfigMode = true;
	});
	wm.resetSettings();
	if (!wm.autoConnect()) {
		Serial.printf("*** Failed to connect and hit timeout\n");
		ESP.restart();
		delay(1000);
	}
}

void loop(){

}
