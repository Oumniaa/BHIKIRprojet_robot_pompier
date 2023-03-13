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

CapteurDistance capteurDistance (trig, echo);

CameraPosition cameraPosition(pinLedRougeCamera);

CapteurLaser capteurLaser;

ControleMoteur controleMoteur(M1A,M1B,M2A,M2B);

int vitesse = 250;

const char TERMINATOR = '|';

int valueRotationArc = 0;
char sensRotationArc = 'a';
boolean activateRotation = false;

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



/**
 * eviterObstacle
 * 
 * Fonction définissant la stratégie afin déviter un obstacle. 
 * On va reculer timeBack ms et tourner à droite pendant timeRight ms.
 */
void eviterObstacle(){
  unsigned int timeBack = 2000;
  unsigned int timeRight = 2000;
  while(true){
    if(capteurLaser.mesureLaser < 45 && capteurLaser.mesureLaser > 0){
      unsigned int time_now = millis();
      Serial.print("time_now = ");  
      Serial.println(time_now);  
      Serial.print("time_now + timeBack = ");  
      Serial.println(time_now + timeBack);  
      controleMoteur.goBack(vitesse);  
      while(millis() < time_now + timeBack){
        
      }
      time_now = millis(); 
      Serial.print("right ");
      controleMoteur.goRight(vitesse);  
      while(millis() < time_now + timeRight){
        
      }
      controleMoteur.goForward(vitesse);
    }else{
      break;
    }
    capteurLaser.capturerDistanceLaser();
  } 
}


int get_value_moteur(String msg){
  String nb = "";
  for(int i = 3; i < msg.length(); i++) {
    nb.concat(msg.charAt(i));
  }
  return nb.toInt();
}

boolean decodage_commande_moteur(String msg){
  int value;
  if (msg.charAt(1) == 'd' | msg.charAt(1) == 'g'){
    activateRotation  = true;
    sensRotationArc = msg.charAt(1);
    valueRotationArc = get_value_moteur(msg);
  } else if (msg.charAt(1) == 'a'){
    activateRotation  = true;
    sensRotationArc = msg.charAt(1);
    valueRotationArc = 0;
  } else {
    return false;
  }
}


boolean decodage_uart(String msg){
  if (msg.charAt(0) == '1'){
    return decodage_commande_moteur(msg);
  }
  if (msg.equals("distance")){
    capteurLaser.capturerDistanceLaser();
    cameraPosition.downLed(); 
    String message = String(capteurLaser.mesureLaser);
    Serial3.write(message.c_str(), message.length());
  }
  return false;
}



void aimToDoor(){
  int v = 160;
  if (sensRotationArc == 'd'){
    controleMoteur.goRight(v);
  }else if (sensRotationArc == 'g'){
    controleMoteur.goLeft(v);
  }else{
    activateRotation = false;
    return -1;
  }
  delay(200);
  controleMoteur.goForward(0);
  activateRotation = false;
  return 1;
  
}


/**
 * Fontion main 
 * 
 * Lancent les différentes fonctions afin de controller le robot
 */
//Communication UART
bool UART = true;

void loop() {
  //capteur laser
  capteurLaser.capturerDistanceLaser();

  if (Serial3.available() && UART) {
    String commandFromJetson = Serial3.readStringUntil(TERMINATOR);
    Serial.println(commandFromJetson);
    //lors du décodage on démarre les fonctionnnalités 
    decodage_uart(commandFromJetson);
  }

  if(activateRotation){
    int v = 130;
    if (capteurLaser.mesureLaser>100 && valueRotationArc < 70){
      controleMoteur.goForward(v);
      delay(1000);
      controleMoteur.goForward(0);
      activateRotation = false;
    } else if(0<=valueRotationArc && valueRotationArc<25 && capteurLaser.mesureLaser < 30){
      controleMoteur.goForward(v);
      while (capteurLaser.mesureLaser < 5){
        capteurLaser.capturerDistanceLaser();
      }
      controleMoteur.goForward(0);
      activateRotation = false;
    } else if (0<=valueRotationArc && valueRotationArc<35 && capteurLaser.mesureLaser > 10){
      controleMoteur.goForward(v);
      delay(300);
      controleMoteur.goForward(0);
      activateRotation = false;
    }else{
      aimToDoor();     
    }
  }
  
  

 
  //capteur ultrason
  //capteurDistance.CapturerDistance();

  
  


  //stratégie

  
  //position 
  /*cameraPosition.motionBurst();
  Serial.print("x : ");
  Serial.println(cameraPosition.getX());
  Serial.print(" y : ");
  Serial.println(cameraPosition.getY());
  Serial.print(" laser : ");
  Serial.println(capteurLaser.mesureLaser);
  Serial.print(" ultrason : ");
  Serial.println(capteurDistance.distance);*/

  
}




 
