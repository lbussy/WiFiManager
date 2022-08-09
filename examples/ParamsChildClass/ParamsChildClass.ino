/**
 * AsyncWiFiManagerParameter child class example
 */
#include <AsyncWiFiManager.h> // https://github.com/lbussy/AsyncWiFiManager
#include <Arduino.h>
#include <EEPROM.h>

#define SETUP_PIN 0

class IPAddressParameter : public AsyncWiFiManagerParameter {
public:
    IPAddressParameter(const char *id, const char *placeholder, IPAddress address)
        : AsyncWiFiManagerParameter("") {
        init(id, placeholder, address.toString().c_str(), 16, "", WFM_LABEL_BEFORE);
    }

    bool getValue(IPAddress &ip) {
        return ip.fromString(AsyncWiFiManagerParameter::getValue());
    }
};

class IntParameter : public AsyncWiFiManagerParameter {
public:
    IntParameter(const char *id, const char *placeholder, long value, const uint8_t length = 10)
        : AsyncWiFiManagerParameter("") {
        init(id, placeholder, String(value).c_str(), length, "", WFM_LABEL_BEFORE);
    }

    long getValue() {
        return String(AsyncWiFiManagerParameter::getValue()).toInt();
    }
};

class FloatParameter : public AsyncWiFiManagerParameter {
public:
    FloatParameter(const char *id, const char *placeholder, float value, const uint8_t length = 10)
        : AsyncWiFiManagerParameter("") {
        init(id, placeholder, String(value).c_str(), length, "", WFM_LABEL_BEFORE);
    }

    float getValue() {
        return String(AsyncWiFiManagerParameter::getValue()).toFloat();
    }
};

struct Settings {
    float f;
    int i;
    char s[20];
    uint32_t ip;
} sett;


void setup() {
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP    
    pinMode(SETUP_PIN, INPUT_PULLUP);
    Serial.begin(115200); 

    //Delay to push SETUP button
    Serial.println("Press setup button");
    for (int sec = 3; sec > 0; sec--) {
        Serial.print(sec);
        Serial.print("..");
        delay(1000);
    }

    // warning for example only, this will initialize empty memory into your vars
    // always init flash memory or add some checksum bits
    EEPROM.begin( 512 );
    EEPROM.get(0, sett);
    Serial.println("Settings loaded");
    
    if (digitalRead(SETUP_PIN) == LOW) {  
        // Button pressed 
        Serial.println("SETUP");

        AsyncWiFiManager wm;
        
        sett.s[19] = '\0';   //add null terminator at the end cause overflow
        AsyncWiFiManagerParameter param_str( "str", "param_string",  sett.s, 20);
        FloatParameter param_float( "float", "param_float",  sett.f);
        IntParameter param_int( "int", "param_int",  sett.i);

        IPAddress ip(sett.ip);
        IPAddressParameter param_ip("ip", "param_ip", ip);

        wm.addParameter( &param_str );
        wm.addParameter( &param_float );
        wm.addParameter( &param_int );
        wm.addParameter( &param_ip );

        //SSID & password parameters already included
        wm.startConfigPortal();

        strncpy(sett.s, param_str.getValue(), 20);
        sett.s[19] = '\0'; 
        sett.f = param_float.getValue();
        sett.i = param_int.getValue();

        Serial.print("String param: ");
        Serial.println(sett.s);
        Serial.print("Float param: ");
        Serial.println(sett.f);
        Serial.print("Int param: ");
        Serial.println(sett.i, DEC);
        
        if (param_ip.getValue(ip)) {
            sett.ip = ip;

            Serial.print("IP param: ");
            Serial.println(ip);
        } else {
            Serial.println("Incorrect IP");
        }

        EEPROM.put(0, sett);
        if (EEPROM.commit()) {
            Serial.println("Settings saved");
        } else {
            Serial.println("EEPROM error");
        }
    } 
    else {  
        Serial.println("WORK");

        //connect to saved SSID
        WiFi.begin();  

        //do smth
        Serial.print("String param: ");
        Serial.println(sett.s);
        Serial.print("Float param: ");
        Serial.println(sett.f);
        Serial.print("Int param: ");
        Serial.println(sett.i, DEC);
        Serial.print("IP param: ");
        IPAddress ip(sett.ip);
        Serial.println(ip);
    }
}

void loop() {
}
