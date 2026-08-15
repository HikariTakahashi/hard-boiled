// 定義するピンの番号
const int sensorPin = A0;  // センサーの出力が接続されるアナログピン

void setup() {
  // シリアル通信を開始
  Serial.begin(9600);
}

void loop() {
  // アナログ値を読み取る
  int sensorValue = analogRead(sensorPin);

  // 読み取った値を電圧に変換
  float voltage = sensorValue * (5.0 / 1023.0);

  // 電圧から距離を計算 (公式に基づいて適切な係数を設定)
  float distance = 27.86 / (voltage - 0.42); // 公式の例: a / (voltage - b) 形式

  // 測定された距離をシリアルモニタに表示
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // 次の測定までの待機時間
  delay(500);
}