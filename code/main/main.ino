#include <TimerOne.h>
#include "CapteurDistance.h"
#include "CameraPosition.h"
#include "CapteurLaser.h"
#include "ControleMoteur.h"
#include "easyRun.h"


#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31

// set the pins to shutdown
#define SHT_LOX1 2
#define SHT_LOX2 3


//pin du capteur de distance 
const int echo = 13;
const int trig = 12;

const int pinLedRougeCamera = 48;

const int M2A = 4;
const int M2B = 5;
const int M1A = 6;
const int M1B = 7;

bool UART = true;

CapteurDistance capteurDistance(trig, echo);

CameraPosition cameraPosition(pinLedRougeCamera);

CapteurLaser capteurLaser;

ControleMoteur controleMoteur(M1A,M1B,M2A,M2B);

const char TERMINATOR = '|';
int valueRotationArc = 0;
int distanceMiddleDoor = 0;
char sensRotationArc = 'a';
boolean activateRotation = false;
int distance_left = 0;
int distance_right = 0;
int distance = 0;


fullMachine sm(f_start);

int time_off = 0;
boolean in_move = false;




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
 * lire la distance que l'on doit placer dans la variable distance (afin de faire fonctionnner les moteurs un certain temps 
 *
int get_value_distance(String msg){
  String nb = "";
  int i = 3;
  while(msg.charAt(i+1) != '!'){
    i++;
  }
  i=i+2;
  for(i;i< msg.length();i++){
    nb.concat(msg.charAt(i));
  }
  return nb.toInt();
}
*
 */

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

void loop() {
  easyRun();

  //capteur ultrason
  //capteurDistance.CapturerDistance();

  //stratégie
  //position 
  
  /*cameraPosition.motionBurst();
  cameraPosition.getX();
  Serial.print(" ultrason : ");
  Serial.println(capteurDistance.distance);*/
}






 
