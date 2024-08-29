#include "WiFiS3.h"
#include "arduino_secrets.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

//SSID及びPASSはコピペする際に必ず消去してください。個人情報です。
char ssid[] = "";
char pass[] = "";
int keyIndex = 0;

int status = WL_IDLE_STATUS;
WiFiServer server(80);

const int ledPin = 13;
bool ledState = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

    lcd.init();
    lcd.backlight();

// 接続エラー時
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WIFI ERROR");
    lcd.setCursor(0, 1);
    lcd.print("READ SERIAL PORT");
    while (true);
  }

// ファームウェアアップデート時
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FIRMWARE ERROR");
    lcd.setCursor(0, 1);
    lcd.print("READ SERIAL PORT");
  }

// WiFi接続時
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
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
    lcd.clear();
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
    lcd.clear();
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
    lcd.clear();
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
    lcd.clear();
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
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WIFI SUCCESSFUL");
    delay(500);
  }
  server.begin();
  printWifiStatus();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    boolean currentLineIsBlank = true;
    String currentRequest = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n' && currentLineIsBlank) {
          if (currentRequest.indexOf("GET /LED=TOGGLE") >= 0) {
            ledState = !ledState;
            digitalWrite(ledPin, ledState ? HIGH : LOW);
          }

          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<form action=\"/LED=TOGGLE\" method=\"GET\">");
          client.println("<input type=\"submit\" value=\"Toggle LED\">");
          client.println("</form>");
          client.println("</html>");
          break;
        }

        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
          currentRequest += c;
        }
      }
    }
    delay(1);
    client.stop();
    Serial.println("client disconnected");
    lcd.setCursor(0, 1);
    lcd.print("Hello World!");
  }
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(WiFi.localIP());
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
