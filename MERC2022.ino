#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT



#include <AFMotor.h>
char received;
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
int speed = 255;

void setup()
{
  
  // TODO you setup code
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

}

void loop()
{
 
  if (Serial3.available()) {
    received = Serial3.read();
    Serial.println(received);
    Serial.println(speed);
  }
  //  if(received.length==7){
  //    String angle = received.substring(0,3);
  //    String strength = received.substring(3,6);
  //    String button = received.substring(6,8);
  //    }

  if ( received == 'w')
  {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    received = 0;
    delay(5);
  }
  if (received == 's')
  {
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    received = 0;
    delay(5);
  }
  if (received == 'a')
  {

    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
    received = 0;
    delay(5);
  }
  if (received == 'd')
  {

    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
    received = 0;
    delay(5);
  }
  if (received == 'k')
  {

    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
    received = 0;
    delay(5);
  } if (received == 'p')
  {

    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
    received = 0;
    delay(5);
  }
  if (received == 'x')
  {
    if (speed > 0) {
      speed -= 5;
      motor1.setSpeed(speed);
      motor2.setSpeed(speed);
      motor3.setSpeed(speed);
      motor4.setSpeed(speed);
    }
    received = 0;
  }
  if (received == 'o')
  {
    if (speed < 255) {
      speed += 5;
      motor1.setSpeed(speed);
      motor2.setSpeed(speed);
      motor3.setSpeed(speed);
      motor4.setSpeed(speed);
    }
    received = 0;
  }

  //  if (received == 'FR')//Foward Right
  //  {
  //    motor1.run(RELEASE);
  //    motor2.run(FORWARD);
  //    motor3.run(RELEASE);
  //    motor4.run(FORWARD);
  //    received = 0;
  //    delay(5);
  //  }  if (received == 'BL')//BL
  //  {
  //    motor1.run(RELEASE);
  //    motor2.run(BACKWARD);
  //    motor3.run(RELEASE);
  //    motor4.run(BACKWARD);
  //    received = 0;
  //    delay(5);
  //  } if (received == 'FL' )//FL
  //  {
  //    motor1.run(FORWARD);
  //    motor2.run(RELEASE);
  //    motor3.run(FORWARD);
  //    motor4.run(RELEASE);
  //    received = 0;
  //    delay(5);
  //  }
  //  if (received == 'BR')//BR
  //  {
  //    motor1.run(BACKWARD);
  //    motor2.run(RELEASE);
  //    motor3.run(BACKWARD);
  //    motor4.run(RELEASE);
  //    received = 0;
  //    delay(5);
  //  }
  if (received == '0') {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    received = 0;
    delay(5);
  }

}
