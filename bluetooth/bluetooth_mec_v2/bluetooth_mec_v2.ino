//#include<PS2X_lib.h>
#include <AFMotor.h>
#include<Servo.h>

//#define ENREAD 30
#define RELAY 50
#define RELAY2 30

char received;
int speed = 0;
int steeringSpd = 140;
int pos =12;
int botPos = 90;
int upperLimitAng = 120;
int lowerLimitAng = 20;
int pulse = 0;


AF_DCMotor motor1(2);
AF_DCMotor motor2(3);
AF_DCMotor motor3(4);
AF_DCMotor motor4(1);
Servo topServo;
Servo bottomServo;


void setup() {
  // put your setup code here, to run once:
  Serial3.begin(115200);
  Serial.begin(115200);
  motor1.setSpeed(speed);
  motor1.run(RELEASE);
  motor2.setSpeed(speed);
  motor2.run(RELEASE);
  motor3.setSpeed(speed);
  motor3.run(RELEASE);
  motor4.setSpeed(speed);
  motor4.run(RELEASE);
  //Servo
  topServo.attach(9);
  bottomServo.attach(10);
  topServo.write(pos);
  bottomServo.write(botPos);
//  pinMode(ENREAD, INPUT_PULLUP);
  pinMode(RELAY, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  delay(10);
  digitalWrite(RELAY, HIGH); // HIGH IS OFF FOR NORMALLY CLOSED RELAY
}

void setSPD(int speed) {
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(1.04 * speed);
  motor4.setSpeed(speed);
}
void stop() {
  setSPD(0);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
void loop() {
//  int a = digitalRead(ENREAD);
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
  if (Serial3.available()) {
    received = Serial3.read();
    Serial.println(received);
    //    Serial.println(speed);
  }
  if (received == '0') {
    stop();
    received = 0;
  } else {
    speed = 120;
    if (received == 'c') { //ROT LEFT
      setSPD(steeringSpd);
      motor4.run(FORWARD);
      motor3.run(BACKWARD);
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      received = 0;
      delay(5);
    }
    else if (received == 'b') { //ROT RIGHT
      setSPD(steeringSpd);
      motor4.run(BACKWARD);
      motor3.run(FORWARD);
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
      received = 0;
      delay(5);
    }
    else if (received == 'a') { //LEFT
      setSPD(speed);
      Serial.print("Im going LEFT");
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      motor3.run(FORWARD);
      motor4.run(BACKWARD);
      received = 0;
      delay(5);
    }
    else if (received == 'd') { //RIGHT
      setSPD(speed);
      Serial.print("Im going RIGHT");

      motor4.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(BACKWARD);
      motor1.run(BACKWARD);
      received = 0;
      delay(5);
    }
    else if (received == 'w') { //FORWARD
      setSPD(speed);
      Serial.print("Im going FORWARD");
      motor4.setSpeed(speed);
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
      received = 0;
      delay(5);
    } else if (received == 's') { //BACKWARD
      setSPD(speed);
      Serial.print("Im going BACKWARD");
      motor4.setSpeed(speed);
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      motor3.run(BACKWARD);
      motor4.run(BACKWARD);
      received = 0;
      delay(5);
    }
  }
  if (received == 'v') { //Sut bong & nâng arm
    pos = 90;
    botPos = 80;
    //    delay(100);
    digitalWrite(RELAY, LOW);
    delay(100); // Thời gian delay từ lúc bật động cơ đến lúc nâng arm
    writeServo();
    delay(778); // Thời gian động cơ hoạt động = (130+778)
    digitalWrite(RELAY, HIGH);
  }
  //  if (received == 'v') {
  //    pos += 10;
  //    if (pos >= upperLimitAng) {
  //      pos = upperLimitAng;
  //    }
  //    topServo.write(pos);
  //    delay(25);
  //    received = 0;
  ////    Serial.println(pos);
  //  }
  //  else if (received == 'z') {
  //    pos -= 10;
  //    if (pos <= lowerLimitAng) {
  //      pos = lowerLimitAng;
  //    }
  //    topServo.write(pos);
  //    delay(25);
  //    received = 0;
  ////    Serial.println(pos);
  //  }
  if (received == 'x') {
    pos = 70;
    botPos = 60;
    //    setPos(70, 60);
    writeServo();
  }
  if (received == 'j') {
    pos = 90;
    botPos = 70;
    writeServo();
  }
  if (received == 'z') { //Chinh sua goc giu bong
    botPos = 55;
    pos = 48 ;
    writeServo();
  }
  if (received == 'k') { //re bong
    if (digitalRead(RELAY2) == HIGH) {
      digitalWrite(RELAY2, LOW);
    }
    else {
      digitalWrite(RELAY2, HIGH);
    }
//      digitalWrite(RELAY2, LOW);
//      delay(2000);
//      digitalWrite(RELAY2, HIGH);
  }
}

void writeServo() {
  topServo.write(pos);
  bottomServo.write(botPos);
}
