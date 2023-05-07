#include <TimerOne.h>
#include "CapteurDistance.h"
#include "CameraPosition.h"
#include "CapteurLaser.h"
#include "ControleMoteur.h"
#include "easyRun.h"
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>
#include <math.h>
#include<Servo.h>



#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31

// set the pins to shutdown
#define SHT_LOX1 2
#define SHT_LOX2 3

// Creat object to represent PCA9685 at default I2C address
#define SERVOMIN 500   // Position minimale
#define SERVOMAX 2500  // Position maximale
#define SER0 0         //Servo Motor 0 on connector 0
#define SER1 1         //Servo Motor 1 on connector 1
#define SER2 2         //Servo Motor 2 on connector 2
#define SER4 4         //Servo Motor 2 on connector 2
#define SER5 5         //Servo Motor 2 on connector 3
#define valeur 20
#define RAD_TO_DEG 57


//pin du capteur de distance 
const int echo = 13;
const int trig = 12;

const int M2A = 4;
const int M2B = 5;
const int M1A = 6;
const int M1B = 7;

bool UART = true;

const char TERMINATOR = '|';
int valueRotationArc = 0;
int distanceMiddleDoor = 0;
char sensRotationArc = 'a';
boolean activateRotation = false;
int distance_left = 0;
int distance_right = 0;
int distance = 0;
int time_off = 0;
boolean in_move = false;

//analogie angle impulsion
int IMP[valeur] = { 2500, 2400, 2300, 2200, 2100, 2000, 1900, 1800, 1700, 1600, 1500, 1400, 1300, 1200, 1100 };
int ANG[valeur] = { 0, 11, 22, 33, 44, 55, 66, 77, 88, 99, 110, 121, 132, 143, 154 };

// just the three ones connected to the PCA9685
int pwm0;
int pwm1;
int pwm2;

// define global variables (Point to move)
int Xhand;  // X position of hand
int Yhand;  // y position of hand
int PosPoint;

// pre calculations
int humerus = 165;  // L1(mm)
int ulna = 110;     // L2(mm)

float hum_sq = humerus * humerus;  // humurus length squared
float uln_sq = ulna * ulna;        // ulna length squared

//Clump code
Servo servo1;
Servo servo2;
int potPin1 = A0;  // potentiomètre 1 connecté à la broche A0
int potPin2 = A1;  // potentiomètre 2 connecté à la broche A1


//CapteurDistance capteurDistance(trig, echo);

CapteurLaser capteurLaser;

ControleMoteur controleMoteur(M1A,M1B,M2A,M2B);

Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x40);

fullMachine sm(f_start);

/**
 * setup
 * 
 * Initialise les communications series.
 */

void setup() {
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  
  Serial3.begin(115200);
  while(!Serial3){
    ;
  }
  
  while (! Serial) { delay(1); }

  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);


  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  setID();

  servo1.attach(9);  // servomoteur 1 connecté à la broche 9
  servo2.attach(10); // servomoteur 2 connecté à la broche 10
  Serial.println("PCA9685 Servo Test");
  pca9685.begin();
  pca9685.setPWMFreq(50);
}

/*
 * retourne la valeur correspondant au nombre de pixel sur la photo permettant de viser le centre de la porte 
 * 
 */
int get_value_moteur(String msg){
  String nb = "";
  int i = 3;
  while(msg.charAt(i+1) != '!'){
    nb.concat(msg.charAt(i));
    i++;
  }
  return nb.toInt();
}

/*
 * on a reçu un message correspondant à une information pour la commande de nos moteur  
 * on va donc analysr selon les possibilité
 */
boolean decodage_commande_moteur(String msg){
  int value;
  if (msg.charAt(1) == 'd' | msg.charAt(1) == 'g' |  msg.charAt(1) == 'a' |  msg.charAt(1) == 'b'){
    activateRotation  = true;
    sensRotationArc = msg.charAt(1);
    valueRotationArc = get_value_moteur(msg);
  } else {
    return false;
  }
}

/*
 * reception d'un message UART 
 * Analyse du premier caractère pour savoir à quel demande correspond ce msg
 */
void decodage_uart(String msg){
  if (msg.charAt(0) == '1'){
    decodage_commande_moteur(msg);
  }
  
  if (msg.charAt(0) == '2'){
    send_distance();
  }
}

void left(){
  controleMoteur.goLeft(160);
}
void rigth(){
  controleMoteur.goRight(160);
}
void back(){
  controleMoteur.goBack(250);
}
void front(){
  controleMoteur.goForward(250);
}

asyncTask turn1;
asyncTask turn2;
asyncTask turn3;
asyncTask turn4;
void turn_left(){
  if(distance_left > 100){
    turn1.set(left, 0);//+450
    turn2.set(front, 450);//+250
    turn3.set(rigth, 900);//+250
    turn4.set(back, 1150);//+250
    sm.next(stop_go, 1400);
  } else {
    turn1.set(left, 0);
    sm.next(stop_go, 250);
  }
}

void turn_right(){
  if(distance_left > 100){
    turn1.set(rigth, 0);//+450
    turn2.set(front, 450);//+250
    turn3.set(left, 900);//+250
    turn4.set(back, 1150);//+250
    sm.next(stop_go, 1400);
  }else{
    turn1.set(rigth, 0);//+250
    sm.next(stop_go, 250);
  }
 }

void go_forward(){
  controleMoteur.goForward(250);
  sm.next(stop_go, time_off);
}

void go_back(){
  controleMoteur.goBack(250);
  sm.next(stop_go, time_off);
}


void rotationMoteur(){
  in_move = true;
  send_in_move();
  if (sensRotationArc == 'd'){
    sm.next(turn_right);
  }else if (sensRotationArc == 'g'){
    sm.next(turn_left);
  }else if (sensRotationArc == 'a'){
    time_off = 250;
    sm.next(go_forward);
  }else if (sensRotationArc == 'b'){
    time_off = 1000;
    sm.next(go_forward);
  }else if (sensRotationArc == 'l'){
    time_off = 500;
    sm.next(go_back);
  }else {
    activateRotation = false;
    in_move = false;
  }
}

void stop_go(){
  controleMoteur.goForward(0);
  activateRotation = false; 
  in_move = false;
  sm.next(f_start);
}

void send_distance(){
    String message = "distance="+(String)distance + "\n";
    Serial3.write(message.c_str(), message.length());
}

void refresh_value_distance(){
  capteurLaser.capturerDistanceLaser();
  distance_left = capteurLaser.get_mesure_cap_1();
  distance_right = capteurLaser.get_mesure_cap_2();
}

void refresh_value_distance_and_send(){
  refresh_value_distance();
  distance = (distance_right+distance_left)/2;
  send_distance();
}
periodicTask pt1(refresh_value_distance_and_send, 200); //To be executed each 200 ms

void read_uart_data(){
  if (Serial3.available() && UART) {
    Serial.print("on decode");
    String commandFromJetson = Serial3.readStringUntil(TERMINATOR);
    decodage_uart(commandFromJetson);
  }
}
periodicTask pt2(read_uart_data, 50); //To be executed each 200 ms

void face_wall(){
  int ratio = distance_left - distance_right;
  in_move = true;
  send_in_move();
  long start_time = millis();
  if(distance < 100){
    while(abs(ratio) > 2) {
      Serial.print("bloque");
      if(ratio < 0){
        left();
      }else{
        rigth();
      }
      refresh_value_distance();
      ratio = distance_left - distance_right;
      if (start_time - millis() > 4000){
        break;
      }
    }
  }
  in_move = false;
  controleMoteur.goForward(0);
}
periodicTask pt3(face_wall, 4000);

void send_in_move(){
  
  if (!Serial3.available()){
    Serial.print(in_move);
    String message = "inmove="+(String)in_move + "\n";
    Serial3.write(message.c_str(), message.length());
  }
}
periodicTask pt4(send_in_move, 300);


void f_start(){
   //envoyer la valeur de la distance 
   if(activateRotation){
    sm.next(rotationMoteur);
   }  
}

//lance main en fonction de base

//  Move the arm to specified x,y position
void moveArm(float x, float y, float z) {

  // calculate required servo angles using inverse kinematics
  Serial.println("Calculate servo angles:");

  // Work out the length of an imaginery line from the arms shoulder to the x,y position and call it B
  // using pythagoras theorem - length of b squared = x sqared + y squared
  float B = sqrt((x * x) + (y * y));
  Serial.print("  B = ");
  Serial.println(B);

  // Calculate the angle of the imaginary line from the x axis and call it QA
  float QA = atan2(y, x);
  Serial.print("  QA = ");
  Serial.println(QA);

  // Calculate the angle from the imaginary line to the humerus (using cosine rule) and call it QB
  float B_sq = B * B;  // B squared
  float tvala = hum_sq - uln_sq + B_sq;
  float tvalb = 2.0 * humerus * B;
  float QB = acos(tvala / tvalb);
  Serial.print("  QB = ");
  Serial.println(QB);

  // Calculate angle of shoulder servo by ading the two calculated angles together
  float angleS = QA + QB;
  Serial.print("  angleS = ");
  Serial.println(angleS);

  // Calculate angle of elbow servo
  // this is done using the cosine rule
  tvala = hum_sq + uln_sq - B_sq;
  tvalb = 2.0 * humerus * ulna;
  float angleE = acos(tvala / tvalb);
  Serial.print("  angleE = ");
  Serial.println(angleE);

 //calcul angle base with hpothenus
  int Rz = sqrt(z * z + x * x);
  Serial.println("Rz = ");
  Serial.println(Rz);
   //float angleB = asin(z / Rz);
  float angleB = atan2(y, x);
  Serial.print("  angleB = ");
  Serial.println(angleB);

  //Calculate angle base
  //float angleB= asin(tvala / hum_sq);

  // convert angles from radians to degrees
  angleE = angleE * RAD_TO_DEG;
  angleS = angleS * RAD_TO_DEG;
  angleB = angleB * RAD_TO_DEG;


  Serial.print("moving arm to x=");
  Serial.print(x);
  Serial.print(" Y=");
  Serial.println(y);
  Serial.print(" Z=");
  Serial.println(z);
  Serial.print("  angleS in degrees = ");
  Serial.println(angleS);
  Serial.print("  angleE in degrees = ");
  Serial.println(angleE);
  Serial.print("  angleB in degrees = ");
  Serial.println(angleB);
  moveServos(angleS, angleE, angleB);  // move the servos
}




// Adjust the mesure
void moveServos(int s, int e, int b) {

  // adjust shoulder servo
  s = s * 0.9;

  // adjust elbow servo
  e = e * 0.8;

  // adjust base servo
  b = b * 0, 8;
  
  pca9685.writeMicroseconds(0, angle_to_pulse(b));
  delay(1000);
  pca9685.writeMicroseconds(1, angle_to_pulse(s));
  delay(1000);
  pca9685.writeMicroseconds(2, angle_to_pulse(e));
  delay(1000);
  
  
  delay(30);
}

// need another angle to pulse for sg90

int angle_to_pulse(int angle) {
  return 2500 - angle * 9;
}


void arm() {
  //X,Y,Z
  //moveArm(100, -120, 130);
  pca9685.writeMicroseconds(0, 2500 - 40 * 9);
  pca9685.writeMicroseconds(1, 2500 - 0 * 9);
  pca9685.writeMicroseconds(2, 2500 - 120 * 9);
  
  /*int pos1 = map(analogRead(potPin1), 0, 1023, 0, 180); // Lecture de la valeur du potentiomètre 1 et la transformation de la plage de valeurs en 0-180 degrés
  int pos2 = map(analogRead(potPin2), 0, 1023, 0, 180); // Lecture de la valeur du potentiomètre 2 et la transformation de la plage de valeurs en 0-180 degrés
  servo1.write(pos1); // Déplacement du servo1 à la position lue depuis le potentiomètre 1
  servo2.write(pos2); // Déplacement du servo2 à la position lue depuis le potentiomètre 2*/

}



void loop() {
  arm();
  //easyRun();
}






 
