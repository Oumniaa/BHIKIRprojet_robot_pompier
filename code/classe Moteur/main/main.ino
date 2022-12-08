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


void setup() {
  //initialisation du serial 
  Serial.begin(57600);
}




int vitesse = 100;


//main 
void eviterObstacle(){
  int timeBack = 3000;
  int timeRight = 2000;
  while(true){
    if(capteurDistance.distance < 10){
      int time_now = millis();    
      while(millis() < time_now + timeBack){
        controleMoteur.goRight(vitesse);
      }
      controleMoteur.goForward(vitesse);
    }else{
      break;
    }
    capteurDistance.CapturerDistance();
  }
  
}


void loop() {
  
  //capteur ultrason
  capteurDistance.CapturerDistance();
  //capteur laser
  capteurLaser.capturerDistanceLaser();


  //stratégie
  //eviterObstacle();

  
  //position 
  cameraPosition.upLed();
  cameraPosition.motionBurst();
  Serial.print("x : ");
  Serial.println(cameraPosition.getX());
  Serial.print("y : ");
  Serial.println(cameraPosition.getY());
  controleMoteur.goRight(vitesse);

  
  
}


 
