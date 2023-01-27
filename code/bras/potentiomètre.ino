#include <Servo.h> // Call the library servo

// create servo object to control a servo
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

// analog pin used to connect the potentiometer
int pot1=0;
int pot2=1;
int pot3=2;
int pot4=3;
int pot5=4;
int pot6=5;

// variable to read the value from the analog pin
int val1;
int val2;
int val3;
int val4;
int val5;
int val6;

void setup() {
  // attaches the servo on pin 9 to the servo object
servo1.attach(5);
servo2.attach(6);
servo3.attach(9);
servo4.attach(10);
servo5.attach(11);
servo6.attach(3);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
val1=analogRead(pot1);            // reads the value of the potentiometer (value between 0 and 1023)
val1=map(val1,0,1023,0,180);     // scale it for use with the servo (value between 0 and 180)
servo1.write(val1);              // sets the servo position according to the scaled value
delay(15);                      // waits for the servo to get there
Serial.print(val1);
Serial.print("   ");

val2=analogRead(pot2);
val2=map(val2,0,1023,0,180);
servo2.write(val2);
delay(15);
Serial.print(val2);
Serial.print("   ");

val3=analogRead(pot3);
val3=map(val3,0,1023,0,180);
servo3.write(val3);
delay(15);
Serial.println(val3);
Seral.println("  ");

val4=analogRead(pot4);
val4=map(val4,0,1023,0,180);
servo4.write(val4);
delay(15);
Serial.println(val4);
Seral.println("  ");

val5=analogRead(pot5);
val5=map(val5,0,1023,0,180);
servo5.write(val45;
delay(15);
Serial.println(val5);
Seral.println("  ");

val6=analogRead(pot6);
val6=map(val6,0,1023,0,180);
servo4.write(val6);
delay(15);
Serial.println(val6);


}
