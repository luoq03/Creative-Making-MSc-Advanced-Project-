#include <Servo.h>
Servo servo_4;
Servo servo_5;
Servo servo_6;
Servo servo_8;
Servo servo_9;
Servo servo_10;


void setup() {
  servo_4.attach(4);
  servo_5.attach(5);
  servo_6.attach(6);
  servo_8.attach(8);
  servo_9.attach(9);
  servo_10.attach(10);

  
  for (int index = 0; index < 2; index++) {   

    servo_8.write(180);
    servo_9.write(0);
    servo_10.write(0);
    delay(4000);


    servo_8.write(0);
    servo_9.write(0);
    servo_10.write(180);
    delay(500);
 

    servo_8.write(0);
    servo_9.write(180);
    servo_10.write(180);
    delay(4000);


    servo_8.write(0);
    servo_9.write(0);
    servo_10.write(0);
 

    servo_4.write(180);
    servo_5.write(0);
    servo_6.write(0);
    delay(4000);


    servo_4.write(0);
    servo_5.write(0);
    servo_6.write(180);
    delay(500);
 

    servo_4.write(0);
    servo_5.write(180);
    servo_6.write(180);
    delay(4000);


    servo_4.write(0);
    servo_5.write(0);
    servo_6.write(0);
 
  }
}
void loop() {

}
