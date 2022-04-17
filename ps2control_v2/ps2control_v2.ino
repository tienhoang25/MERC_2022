#include<PS2X_lib.h>
#include <AFMotor.h>
#include<math.h>
#include<Servo.h>

#define PS2_SEL 30
#define PS2_CMD 31
#define PS2_DAT 32
#define PS2_CLK 33


#define pressures   true
#define rumble      true

int error = 0;
int speed = 0;
int steeringSpd = 80;
int LX = 0;
int LY = 0;
int RX = 0;
int RY = 0;
int N_X = 128;
int N_Y = 127;
byte type = 0;
byte vibrate = 0;
int motorPin = 50;
int pos = 70;
int upperLimitAng = 70;
int lowerLimitAng = -20;

PS2X ps2x;
AF_DCMotor motor1(2);
AF_DCMotor motor2(3);
AF_DCMotor motor3(4);
AF_DCMotor motor4(1);
Servo frontservo;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  delay(300);
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
  //Servo
  frontservo.attach(9);
  frontservo.write(pos);
}

void setSPD(int speed) {
  motor1.setSpeed(1.014 * speed);
  motor2.setSpeed(0.97 * speed);
  motor3.setSpeed(0.996 * speed);
  motor4.setSpeed(0.82 * speed);
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
  if (ps2x.Button(PSB_L1)) {
    if (digitalRead(motorPin) == LOW) {
      digitalWrite(motorPin, HIGH);
    } else {
      digitalWrite(motorPin, LOW);
    }
  }
  //  if (ps2x.Button(PSB_R2)) {
  //    LX = ps2x.Analog(PSS_LX);
  //    LY = ps2x.Analog(PSS_LY);
  //    RX = ps2x.Analog(PSS_RX);
  //    RY = ps2x.Analog(PSS_RY);
  //    int diff_LX = abs(LX - N_X);
  //    int diff_LY = abs(LY - N_Y);
  //    int diff_RX = abs(RX - 128);
  //    int diff_RY = abs(RY - 127);
  //    Serial.print("LX:");
  //    Serial.println(LX);
  //    Serial.print("LY:");
  //    Serial.println(LY);
  //    Serial.print("RX:");
  //    Serial.println(RX);
  //    Serial.print("RY:");
  //    Serial.println(RY);
  if (!ps2x.Button(PSB_TRIANGLE) && !ps2x.Button(PSB_SQUARE) && !ps2x.Button(PSB_CIRCLE) && !ps2x.Button(PSB_CROSS) && !ps2x.Button(PSB_L2) && !ps2x.Button(PSB_R2)) {
    stop();
  } else {
    speed = 120;
    if (ps2x.Button(PSB_R2)) { //ROT RIGHT
      Serial.println("Im going ROTRIGHT");
      setSPD(steeringSpd);
      motor4.run(FORWARD);
      motor3.run(BACKWARD);
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
    }
    else if (ps2x.Button(PSB_L2)) { //ROT LEFT
      Serial.println("Im going ROTLEFT");
      setSPD(steeringSpd);
      motor4.run(BACKWARD);
      motor3.run(FORWARD);
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
    }
    else if (ps2x.Button(PSB_SQUARE)) { //LEFT
      Serial.println("Im going LEFT");
      setSPD(speed);
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      motor3.run(FORWARD);
      motor4.run(BACKWARD);
    }
    else if (ps2x.Button(PSB_CIRCLE)) { //RIGHT

      Serial.println("Im going RIGHT");
      setSPD(speed);
      motor4.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(BACKWARD);
      motor1.run(BACKWARD);
    }
    else if (ps2x.Button(PSB_TRIANGLE)) { //FORWARD
      Serial.println("Im going FORWARD");
      setSPD(speed);
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
    } else if (ps2x.Button(PSB_CROSS) ) { //BACKWARD
      Serial.println("Im going BACKWARD");
      setSPD(speed);
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      motor3.run(BACKWARD);
      motor4.run(BACKWARD);
    }
  }
  //  }
  if (ps2x.Button(PSB_PAD_UP)) {
    pos += 10;
    if (pos >= upperLimitAng) {
      pos = upperLimitAng;
    }
    frontservo.write(pos);
    delay(25);
    Serial.println(pos);
  }
  else if (ps2x.Button(PSB_PAD_DOWN)) {
    pos -= 10;
    if (pos <= lowerLimitAng) {
      pos =  lowerLimitAng;
    }
    frontservo.write(pos);
    delay(25);
    Serial.println(pos);
  }
  //  LY = LX = 128;
  //  RY = RX = 128;
}
