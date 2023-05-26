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
  if (msg.charAt(1) == 'd' | msg.charAt(1) == 'g' |  msg.charAt(1) == 'a' |  msg.charAt(1) == 'b'|  msg.charAt(1) == 'l'){
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
  turn1.set(left, 0);
  sm.next(stop_go, 250);
}

void turn_right(){
  turn1.set(rigth, 0);//+250
  sm.next(stop_go, 250);
 }

void go_forward(){
  turn1.set(front, 0);//+250
  sm.next(stop_go, 1000);
}

void go_back(){
  turn1.set(back, 0);//+250
  sm.next(stop_go, 1000);
}


void rotationMoteur(){
  in_move = true;
  send_in_move();
  if (sensRotationArc == 'd'){
    sm.next(turn_right);
  }else if (sensRotationArc == 'g'){
    sm.next(turn_left);
  }else if (sensRotationArc == 'a'){
    sm.next(go_forward);
  }else if (sensRotationArc == 'b'){
    sm.next(go_forward);
  }else if (sensRotationArc == 'l'){
    sm.next(go_forward);
  }else {
    activateRotation = false;
    in_move = false;
  }
}

void stop_go(){
  controleMoteur.goForward(0);
  activateRotation = false; 
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
  distance = (distance_right+distance_left)/2;
  Serial.println(distance);
}

void refresh_value_distance_and_send(){
  refresh_value_distance();
  send_distance();
}
periodicTask pt1(refresh_value_distance_and_send, 200); //To be executed each 200 ms

void read_uart_data(){
  if (Serial3.available() && UART) {
    String commandFromJetson = Serial3.readStringUntil(TERMINATOR);
    decodage_uart(commandFromJetson);
  }
}
periodicTask pt2(read_uart_data, 100);

void face_wall(){
  int ratio = distance_left - distance_right;
  in_move = true;
  send_in_move();
  long start_time = millis();
  
  if(distance < 100){
    while(abs(ratio) > 2) {
      if(ratio < 0){
        left();
      }else{
        rigth();
      }
      refresh_value_distance();
      ratio = distance_left - distance_right;
      int c_time = millis();
      if ((start_time - c_time) > 4000){
        break;
      }
    }
  }
  in_move = false;
  controleMoteur.goForward(0);
}
//periodicTask pt3(face_wall, 4000);

void send_in_move(){
  if (!Serial3.available()){
    String message = "inmove="+(String)in_move + "\n";
    Serial3.write(message.c_str(), message.length());
  }
}
periodicTask pt4(send_in_move, 100);


void f_start(){
   //envoyer la valeur de la distance 
   if(activateRotation){
      sm.next(rotationMoteur);
   }else{
      in_move = false;
      send_in_move();
   }
}

//lance main en fonction de base


void loop() {
  easyRun();
}






 
