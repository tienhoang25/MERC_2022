#include<PS2X_lib.h>
#include <AFMotor.h>
#include<math.h>

#define PS2_SEL 40
#define PS2_CMD 41
#define PS2_DAT 42
#define PS2_CLK 43


#define pressures   true
#define rumble      true

int error = 0;
int speed = 0;
int LX = 0;
int LY = 0;
int RX = 0;
int RY = 0;
int N_X = 128;
int N_Y = 127;
byte type = 0;
byte vibrate = 0;
int motorPin = 50;

PS2X ps2x;
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
  pinMode(motorPin, OUTPUT);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  if (error == 0) {
    Serial.println("Found Controller, configured successful");
  }

  else if (error == 1)
    Serial.println("No controller found, check wiring or reset the Arduino");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it.");
  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
    case 2:
      Serial.println("GuitarHero Controller Found");
      break;
  }
  motor1.setSpeed(speed);
  motor1.run(RELEASE);
  motor2.setSpeed(speed);
  motor2.run(RELEASE);
  motor3.setSpeed(speed);
  motor3.run(RELEASE);
  motor4.setSpeed(speed);
  motor4.run(RELEASE);
}

void setSPD(int speed) {
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);
  motor1.setSpeed(speed);
}
void stop() {
  setSPD(0);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
void loop() {
  ps2x.read_gamepad(false, vibrate);
  delay(50);
  if (ps2x.Button(PSB_CROSS)) {
    if (digitalRead(motorPin) == LOW) {
      digitalWrite(motorPin, HIGH);
    } else {
      digitalWrite(motorPin, LOW);
    }
  }
  if (ps2x.Button(PSB_R2)) {
    LX = ps2x.Analog(PSS_LX);
    LY = ps2x.Analog(PSS_LY);
    RX = ps2x.Analog(PSS_RX);
    RY = ps2x.Analog(PSS_RY);
    int diff_LX = abs(LX - N_X);
    int diff_LY = abs(LY - N_Y);
    int diff_RX = abs(RX - 128);
    int diff_RY = abs(RY - 127);
    Serial.print("LX:");
    Serial.println(LX);
    Serial.print("LY:");
    Serial.println(LY);
    Serial.print("RX:");
    Serial.println(RX);
    Serial.print("RY:");
    Serial.println(RY);
    if (diff_LX < 3 && diff_LY < 3 && diff_RX < 3 && diff_RY < 3) {
      stop();
    }
    if (RX > 180 && diff_RY < 10) { //ROT RIGHT
      speed = 0.7 * diff_RX;
      setSPD(speed);
      motor4.run(FORWARD);
      motor3.run(BACKWARD);
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
    }
    else if (RX < 80 && diff_RY < 10) { //ROT LEFT
      speed = 0.7 * diff_RX;
      setSPD(speed);
      motor4.run(BACKWARD);
      motor3.run(FORWARD);
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
    }
    else if (LX < 80 && diff_LY < 5) { //LEFT
      speed = 0.7 * diff_LX;
      Serial.println(speed);
      Serial.print("Im going LEFT");
      setSPD(speed);
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      motor3.run(FORWARD);
      motor4.run(BACKWARD);
    }
    else if (diff_LY < 5 && LX > 180) { //RIGHT
      speed = 0.7 * diff_LX;
      Serial.print("Im going RIGHT");
      //        Serial.println(speed);
      setSPD(speed);
      motor4.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(BACKWARD);
      motor1.run(BACKWARD);
    }
    else if (LY < 80 && diff_LX < 3) { //FORWARD
      Serial.print("Im going FORWARD");
      speed = 0.9 * diff_LY;
      setSPD(speed);
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
    } else if (LY > 180 && diff_LX < 3 ) { //BACKWARD
      Serial.print("Im going BACKWARD");
      speed = 0.7 * diff_LY;
      setSPD(speed);
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      motor3.run(BACKWARD);
      motor4.run(BACKWARD);
    }
  }
  LY = LX = 128;
  RY = RX = 128;
}
