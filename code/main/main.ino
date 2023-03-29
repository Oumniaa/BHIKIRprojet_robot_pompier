#include <TimerOne.h>
#include "CapteurDistance.h"
#include "CameraPosition.h"
#include "CapteurLaser.h"
#include "ControleMoteur.h"

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
  cameraPosition.upLed();  
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
 */
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
    distanceMiddleDoor = get_value_distance(msg);
  } else {
    return false;
  }
}

/*
 * reception d'un message UART 
 * Analyse du premier caractère pour savoir à quel demande correspond ce msg
 */
boolean decodage_uart(String msg){
  if (msg.charAt(0) == '1'){
    return decodage_commande_moteur(msg);
  }
  
  if (msg.equals("distance")){
    send_distance();
  }
  return false;
}

/*
 * envoyer la valeur de la distance
 */
 void send_distance(){
    String message = (String)distance  + "\n";
    Serial3.write(message.c_str(), message.length());
 }

/*
 * faire fonctionnner les moteurs selon le msg de la jetson nano
 */
void rotationMoteur(){
  int v = 160;
  if (sensRotationArc == 'd'){
    controleMoteur.goRight(v);
  }else if (sensRotationArc == 'g'){
    controleMoteur.goLeft(v);
  }else if (sensRotationArc == 'a'){
    controleMoteur.goForward(250);
  }else if (sensRotationArc == 'b'){
    controleMoteur.goForward(250);
    delay(1500);
  }else {
    activateRotation = false;
    return -1;
  }
  delay(250);
  controleMoteur.goForward(0);
  activateRotation = false;
  return 1;
}


/**
 * Fontion main 
 * 
 * Lancent les différentes fonctions afin de controller le robot
 */

void loop() {
  capteurLaser.capturerDistanceLaser();
  distance = capteurLaser.mesureLaser;
  if (Serial3.available() && UART) {
    String commandFromJetson = Serial3.readStringUntil(TERMINATOR);
    Serial.println(commandFromJetson);
    decodage_uart(commandFromJetson);
  }

  if(activateRotation){
    rotationMoteur();    
  }
  
 
  //capteur ultrason
  //capteurDistance.CapturerDistance();

  //stratégie
  //position 
  
  /*cameraPosition.motionBurst();
  cameraPosition.getX();
  Serial.print(" ultrason : ");
  Serial.println(capteurDistance.distance);*/
}




 
