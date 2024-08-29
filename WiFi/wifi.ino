#include "WiFiS3.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

// SSID及びPASSはコピペする際に必ず消去してください。個人情報です。
#define SECRET_SSID "1319-Network"
#define SECRET_PASS "ymks1319"

void setup() {
    Serial.begin(9600);

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("CONNECT WIFI ");
    
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CONNECT WIFI.");
    
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CONNECT WIFI..");
    
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CONNECT WIFI...");
    delay(500);

    Serial.println(SECRET_SSID);
    WiFi.begin(SECRET_SSID, SECRET_PASS);
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ALL SUCCESSFUL");
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ERROR");
    }

    delay(1000);
}
