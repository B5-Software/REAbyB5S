#include <Wire.h>

// IIC addrs
const int MPU6050_ADDR = 0x68;

// MPU6050 addrs
const int ACCEL_XOUT_H = 0x3B;
const int ACCEL_YOUT_H = 0x3D;
const int ACCEL_ZOUT_H = 0x3F;

// set 灵敏度
const int shakeThreshold = 15000; // Rewrite 2 set 灵敏度

void setup() {
  // init s1
  Wire.begin();
  pinMode(PA13, OUTPUT);
  pinMode(PA14, INPUT);
  pinMode(PA3, OUTPUT);
  digitalWrite(PA3, LOW);

  Serial.begin(9600);
  Serial.print("Radio Exam Assistant v0.1 by B5-Software");
  Serial.print("[Note] Starting...");
  
  // init s2
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

}

void loop() {
  delay(2000);
  Serial.print("[Note] Started up.");
  // read sensor
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR, 6, true);

  int accX = Wire.read() << 8 | Wire.read();
  int accY = Wire.read() << 8 | Wire.read();
  int accZ = Wire.read() << 8 | Wire.read();

  Serial.print("[Log] Acc X: "); Serial.println(accX);
  Serial.print("[Log] Acc Y: "); Serial.println(accY);
  Serial.print("[Log] Acc Z: "); Serial.println(accZ);

  // detect shake
  if (abs(accX) > shakeThreshold || abs(accY) > shakeThreshold || abs(accZ) > shakeThreshold) {
    Serial.print("[Note] Shake Detected.");
    digitalWrite(PA13, HIGH);
    delay(1000);
    digitalWrite(PA13, LOW);
  }

  // read radio receiver
  if (digitalRead(PA14) == HIGH) {
  Serial.print("[Note] Msg Got.");
    digitalWrite(PA3, HIGH);
    delay(1000);
    digitalWrite(PA3, LOW);
  }
}
