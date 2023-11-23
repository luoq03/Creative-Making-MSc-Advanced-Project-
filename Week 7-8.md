# Week 7-8: Hardware fabrication.

## 形变动力分析——充气变形

![屏幕截图 2023-11-23 005637](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/7b25eb44-44b9-4472-87d4-5c224ba8bf9e)

![屏幕截图 2023-11-23 005553](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/1e39c485-da0d-41ab-ad7f-5b91db7ce626)

## 与模型结合的充气变形测试

用4，5，6，8，9，10号引脚控制两组气泵进行交替充气和放气，记录3D模型在气球挤压下发生形变的过程

```ruby
#include <Servo.h>
Servo servo_4; # Define a servo object for servo connected to pin 4
Servo servo_5; # Define a servo object for servo connected to pin 5
Servo servo_6; # Define a servo object for servo connected to pin 6
Servo servo_8; # Define a servo object for servo connected to pin 8
Servo servo_9; # Define a servo object for servo connected to pin 9
Servo servo_10; # Define a servo object for servo connected to pin 10


void setup() {
  servo_4.attach(4); # Attach servo_4 to pin 4
  servo_5.attach(5); # Attach servo_5 to pin 5
  servo_6.attach(6); # Attach servo_6 to pin 6
  servo_8.attach(8); # Attach servo_8 to pin 8
  servo_9.attach(9); # Attach servo_9 to pin 9
  servo_10.attach(10); # Attach servo_10 to pin 10

  
  for (int index = 0; index < 2; index++) {   
    #  Rotate servo_8 to 180 degrees, servo_9 to 0 degrees, and servo_10 to 0 degrees
    servo_8.write(180);
    servo_9.write(0);
    servo_10.write(0);
    delay(4000);

    #  Rotate servo_8 to 0 degrees, servo_9 to 0 degrees, and servo_10 to 180 degrees
    servo_8.write(0);
    servo_9.write(0);
    servo_10.write(180);
    delay(500);
 
    #  Rotate servo_8 to 0 degrees, servo_9 to 180 degrees, and servo_10 to 180 degrees
    servo_8.write(0);
    servo_9.write(180);
    servo_10.write(180);
    delay(4000);

    #  Rotate servo_8, servo_9, and servo_10 back to 0 degrees
    servo_8.write(0);
    servo_9.write(0);
    servo_10.write(0);
 
    #  Similar movements for servo_4, servo_5, and servo_6
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

```

https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/f71f6524-bf53-4927-9fd4-573f5afd9f6a

## 最终装置制作-硬件部分

参考模特身形画出具体需要的尺寸

![f8d7f23dee19596305bc269703ee1a4](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/e9adc17e-cc64-4294-9ce5-43b5800d3650)

![fc53f5888aba720923e9656153a4ddc](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/1ee86fef-3d8d-427d-815e-346e59bf309b)

打印最终3D模型
![屏幕截图 2023-11-23 001042](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/86fa494b-5bea-4fd2-95f2-d196ec870777)

![屏幕截图 2023-11-23 001052](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/f21fcfbc-f366-4a24-9ee7-29f9d4ea0a97)

![屏幕截图 2023-11-23 001103](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/c2d4a472-608c-4ac8-93c1-97db8bbe416e)

![屏幕截图 2023-11-23 001115](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/d15c4422-19a4-4d80-946c-ca4a37563c41)

将道具服与3D打印模型简单固定

![屏幕截图 2023-11-23 001456](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/84dc2338-2a8c-4f53-be13-06a5913ec50a)

模特试穿

![屏幕截图 2023-11-23 001545](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/7801f543-c9c6-4fd4-a747-592a4f080bac)

最终将道具服与3D打印模型缝合

![屏幕截图 2023-11-23 014304](https://github.com/luoq03/Creative-Making-MSc-Advanced-Project-/assets/57748663/96c35f78-7df3-4a20-993b-339955519335)
