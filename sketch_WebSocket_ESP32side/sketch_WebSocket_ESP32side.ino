#include <WiFi.h> //WiFi機能を使用するためのライブラリ//
#include <WebSocketsClient.h> //WebSocketクライアント機能を使用するためのライブラリ

const char* ssid = "your_SSID";      // ESPが接続するWiFiのSSID指定
const char* password = "your_PASSWORD";  // WiFiネットワークのパスワードを指定
const char* webSocketServer = "ws://<PCのIPアドレス>:8080";  
// WebSocketサーバーのURLを指定、Node.jsサーバーのIPアドレスとポート番号


WebSocketsClient webSocket; //WebSocket通信を行うためのクライアントオブジェ

void handleNumber(int number) {
  String message = String(number); //数値を文字列に//
  webSocket.sendTXT(message);      //WebSocketサーバーにテキストメッセージ送信
}
// handleNumber:数値を受け取り、WebSocketサーバーに送信するための関数 

void handleWebSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  // WebSocketイベントの処理が必要ない場合、空にしておくこともできます
}

void setup() {
  Serial.begin(115200); //デバッグメッセージをシリアルモニターに表示//

  // WiFi接続の設定
  WiFi.begin(ssid, password); // WiFiに接続開始
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); //WiFi接続が確立するまで待機、接続状況をシリアルモニターに表示
  }
  Serial.println("Connected to WiFi");

  // WebSocketクライアントの設定
  webSocket.begin(webSocketServer); // WebSocketサーバーへの接続を開始
  webSocket.onEvent(handleWebSocketEvent); // WebSocketのイベントが発生したときに handleWebSocketEvent関数を呼ぶ

  // Arduinoから数値を受信するための設定ことも可
  // 例: Serialポートから数値を読み取って送信するなど
}

void loop() {
  webSocket.loop(); //WebSocketの通信処理を継続的に実行,メッセージの受信や送信、接続の維持など
                    //この関数を呼ぶことで、WebSocket通信を常に最新の状態にkeep
  // Arduinoからの数値をシリアルポートから読み取って送信
  if (Serial.available() > 0) {     //シリアルポートに読み取り可能なデータが存在するかどうか、０より大きければデータ//
    int number = Serial.parseInt(); //シリアルポートから連続する文字列を整数に変換して読み取る、読み取りが完了後、number変数に格納
    handleNumber(number);           //handleNumber: 受け取った数値をWebSocketサーバーに送信する関数
  }
  

}