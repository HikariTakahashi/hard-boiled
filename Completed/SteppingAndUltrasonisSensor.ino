#include <Stepper.h>

#define MOTOR_1   (4)   // blue
#define MOTOR_2   (5)   // pink
#define MOTOR_3   (6)   // yellow
#define MOTOR_4   (7)   // orange
#define MOTOR_STEPS (2048)

Stepper myStepper(MOTOR_STEPS, MOTOR_1, MOTOR_3, MOTOR_2, MOTOR_4);

// 定義するピンの番号
const int trigPin = 9;  // トリガーピン
const int echoPin = 10; // エコーピン

void setup() {
  // モーターの設定
  myStepper.setSpeed(10);  // モーターの速度を設定

  // 超音波センサーのピンモードの設定
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // シリアル通信を開始
  Serial.begin(9600);
}

void loop() {
  // モーターを45°回転させる
  myStepper.step(256);

  // モーターへの電流を止める
  stopMotor();

  // 距離を測定する
  long distance = measureDistance();

  // 測定された距離をシリアルモニタに表示
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // 2秒間待つ
  delay(500);
}

// モーターへの電流を止める
void stopMotor() {
  digitalWrite(MOTOR_1, LOW);
  digitalWrite(MOTOR_2, LOW);
  digitalWrite(MOTOR_3, LOW);
  digitalWrite(MOTOR_4, LOW);
}

// 超音波センサーで距離を測定する関数
long measureDistance() {
  // トリガーピンをLOWにして安定させる
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // トリガーピンをHIGHにして10マイクロ秒間パルスを送信
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // エコーピンで返ってくる信号の時間を計測
  long duration = pulseIn(echoPin, HIGH);

  // 時間から距離を計算（音速を340m/sとして計算）
  long distance = duration * 0.034 / 2;

  return distance;
}