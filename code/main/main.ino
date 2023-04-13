#include <TimerOne.h>
#include "CapteurDistance.h"
#include "CameraPosition.h"
#include "CapteurLaser.h"
#include "ControleMoteur.h"
#include "easyRun.h"

//pin du capteur de distance 
const int echo = 13;
const int trig = 12;

const int pinLedRougeCamera = 48;

const int M2A = 4;
const int M2B = 5;
const int M1A = 6;
const int M1B = 7;

bool UART = true;

CapteurDistance capteurDistance (trig, echo);

CameraPosition cameraPosition(pinLedRougeCamera);

CapteurLaser capteurLaser;

ControleMoteur controleMoteur(M1A,M1B,M2A,M2B);

const char TERMINATOR = '|';
int valueRotationArc = 0;
int distanceMiddleDoor = 0;
char sensRotationArc = 'a';
boolean activateRotation = false;
int distance;

fullMachine sm(f_start);

int time_off = 0;




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
  /*
  Serial3.begin(115200);
  while(!Serial3){
    ;
  }*/
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

/*
 * envoyer la valeur de la distance
 */
 void send_distance(){
    String message = (String)distance + "\n";
    //Serial3.write(message.c_str(), message.length());
    Serial.write(message.c_str(), message.length());
 }
 

 void turn_left(){
  if(distance < 100){
    controleMoteur.goLeft(160);
    delay(450);
    controleMoteur.goForward(250);
    delay(250);
    controleMoteur.goRight(160);
    delay(250);
    controleMoteur.goBack(250);
    delay(250);
  } else {
    controleMoteur.goLeft(160);
    delay(250);
  }
 }

 
 void turn_right(){
  if(distance < 100){
    controleMoteur.goRight(160);
    delay(450);
    controleMoteur.goForward(250);
    delay(250);
    controleMoteur.goLeft(160);
    delay(250);
    controleMoteur.goBack(250);
    delay(250);
  }else{
    controleMoteur.goRight(160);
    delay(250);
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

void stop_go(){
  controleMoteur.goForward(0);
  activateRotation = false; 
  sm.next(f_start);
}

/*
 * faire fonctionnner les moteurs selon le msg de la jetson nano
 */
void rotationMoteur(){
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
  }
}


void refresh_value_distance(){
  Serial.println("refresh_value_distance");
  capteurLaser.capturerDistanceLaser();
  distance = capteurLaser.mesureLaser;
  Serial.println("End refresh_value_distance");
}
periodicTask pt1(refresh_value_distance, 1000); //To be executed each 1000 ms


void send_value_distance(){
  Serial.println(distance);
}


void read_uart_data(){
  Serial.print("read_uart_data");
  //if (Serial3.available() && UART) {
  if (Serial.available() && UART) {
    //String commandFromJetson = Serial3.readStringUntil(TERMINATOR);
    String commandFromJetson = Serial.readStringUntil(TERMINATOR);
    decodage_uart(commandFromJetson);
  }
  Serial.print("end read_uart_data");
}
periodicTask pt2(read_uart_data, 1000); //To be executed each 1000 ms


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




 
