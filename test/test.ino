#include <Servo.h>
Servo servo_head_1; //头部泵
Servo servo_head_2; //头部气阀
Servo servo_chest_1; //胸部泵
Servo servo_chest_2; //胸部气阀
Servo servo_l_hand_1; //左手泵
Servo servo_l_hand_2; //左手气阀
Servo servo_r_hand_1; //右手泵
Servo servo_r_hand_2; //右手气阀
Servo servo_l_leg_1; //左腿泵
Servo servo_l_leg_2; //左腿气阀
Servo servo_r_leg_1; //右腿泵
Servo servo_r_leg_2; //右腿气阀

void angry() {
  for(int i=0;i<3;i++)
  {
    servo_head_1.write(180);
    servo_head_2.write(0);
    servo_chest_1.write(180);
    servo_chest_2.write(0);
    servo_l_hand_1.write(180);
    servo_l_hand_2.write(0);
    servo_r_hand_1.write(180);
    servo_r_hand_2.write(0);
    delay(2000);
    servo_head_1.write(0);
    servo_head_2.write(180);
    servo_chest_1.write(0);
    servo_chest_2.write(180);
    servo_l_hand_1.write(0);
    servo_l_hand_2.write(180);
    servo_r_hand_1.write(0);
    servo_r_hand_2.write(180);
    delay(3000);
  }
}

void fear() {
  for(int i=0;i<3;i++)
  {
//    servopulse(servo_A0, 180);
//    servopulse(servo_A1, 0);
    servo_chest_1.write(180);
    servo_chest_2.write(0);
    delay(2000);
    servo_chest_1.write(0);
    servo_chest_2.write(180);
    delay(3000);
  }
}

void disgust() {
  for(int i=0;i<3;i++)
  {
    servo_head_1.write(180);
    servo_head_2.write(0);
    delay(2000);
    servo_head_1.write(0);
    servo_head_2.write(0);
    delay(500);
    servo_head_1.write(0);
    servo_head_2.write(180);
    delay(3000);
  }
}

void happy() {
  for(int i=0;i<3;i++)
  {
    servo_head_1.write(180);
    servo_head_2.write(0);
   servo_l_hand_1.write(180);
   servo_l_hand_2.write(0);
    servo_r_hand_1.write(180);
    servo_r_hand_2.write(0);
    servo_l_leg_1.write(180);
    servo_l_leg_2.write(0);
    servo_r_leg_1.write(180);
    servo_r_leg_2.write(0);
    delay(2000);
    servo_head_1.write(0);
    servo_head_2.write(180);
    servo_l_hand_1.write(0);
    servo_l_hand_2.write(180);
    servo_r_hand_1.write(0);
    servo_r_hand_2.write(180);
    servo_l_leg_1.write(0);
    servo_l_leg_2.write(180);
    servo_r_leg_1.write(0);
    servo_r_leg_2.write(180);
    delay(3000);
  }
}

void sad() {
  for(int i=0;i<3;i++)
  {
    servo_chest_1.write(180);
    servo_chest_2.write(0);
    servo_l_leg_1.write(180);
    servo_l_leg_2.write(0);
    servo_r_leg_1.write(180);
    servo_r_leg_2.write(0);
    delay(2000);
    servo_chest_1.write(0);
    servo_chest_2.write(180);
    servo_l_leg_1.write(0);
    servo_l_leg_2.write(180);
    servo_r_leg_1.write(0);
    servo_r_leg_2.write(180);
    delay(3000);
  }
}

void surprise() {
  for(int i=0;i<3;i++)
  {
    servo_head_1.write(180);
    servo_head_2.write(0);
    servo_chest_1.write(180);
    servo_chest_2.write(0);
    servo_l_leg_1.write(180);
    servo_l_leg_2.write(0);
    servo_r_leg_1.write(180);
    servo_r_leg_2.write(0);
    delay(2000);
    servo_head_1.write(0);
    servo_head_2.write(180);
    servo_chest_1.write(0);
    servo_chest_2.write(180);
    servo_l_leg_1.write(0);
    servo_l_leg_2.write(180);
    servo_r_leg_1.write(0);
    servo_r_leg_2.write(180);
    delay(3000);
  }
}

void setup() {
  Serial.begin(115200); 
  Serial.println("test");
  //Serial.setTimeout(50);
  servo_head_1.attach(2);
  servo_head_2.attach(3);
  servo_chest_1.attach(4);
  servo_chest_2.attach(5);
  servo_l_hand_1.attach(6);
  servo_l_hand_2.attach(7);
  servo_r_hand_1.attach(8);
  servo_r_hand_2.attach(9);
  servo_l_leg_1.attach(10);
  servo_l_leg_2.attach(11);
  servo_r_leg_1.attach(12);
  servo_r_leg_2.attach(13);
    servo_head_1.write(180);
    servo_head_2.write(0);
    servo_chest_1.write(180);
    servo_chest_2.write(0);
    servo_l_hand_1.write(180);
    servo_l_hand_2.write(0);
    servo_r_hand_1.write(180);
    servo_r_hand_2.write(0);
    servo_l_leg_1.write(180);
    servo_l_leg_2.write(0);
    servo_r_leg_1.write(180);
    servo_r_leg_2.write(0);
    delay(2000);
    servo_head_1.write(0);
    servo_head_2.write(180);
    servo_chest_1.write(0);
    servo_chest_2.write(180);
    servo_l_hand_1.write(0);
    servo_l_hand_2.write(180);
    servo_r_hand_1.write(0);
    servo_r_hand_2.write(180);
    servo_l_leg_1.write(0);
    servo_l_leg_2.write(180);
    servo_r_leg_1.write(0);
    servo_r_leg_2.write(180);
    delay(3000);
}

//void loop() {
//
//  String data;
//  if (Serial.available() > 0) {
//  // 读取传入的字符串直到遇到换行符
//    data = Serial.readString(); 
//    if (data.startsWith("happy"))
//    {
//      happy();  
//    }
//    if (data.startsWith("angry"))
//    { 
//      angry();
//    }
//    if (data.startsWith("sad"))
//    {
//      sad();
//    }
//    if (data.startsWith("fear"))
//    { 
//      fear();
//    }
//    if (data.startsWith("surprise"))
//    {
//      surprise();
//    }
//    if (data.startsWith("disgust"))
//    { 
//      disgust();
//    }
//    Serial.println(data);
//      while(Serial.read()>0);
//    data="";
//   }
// 
//   delay(200);
//    // 处理接收到的数据
//}

void loop() {

  String data;
  while (Serial.available() > 0) {
    data += char(Serial.read());
    delay(2); //延时一会，让串口缓存准备好下一个数字，不延时会导致数据丢失
  }
  if (data.length() > 0){
    if (data.startsWith("happy"))
    {
      happy();  
    }
    if (data.startsWith("angry"))
    { 
      angry();
    }
    if (data.startsWith("sad"))
    {
      sad();
    }
    if (data.startsWith("fear"))
    { 
      fear();
    }
    if (data.startsWith("surprise"))
    {
      surprise();
    }
    if (data.startsWith("disgust"))
    { 
      disgust();
    }
    Serial.println(data);
    data="";
   }
   while(Serial.read()>0);
   delay(200);
    // 处理接收到的数据
}
