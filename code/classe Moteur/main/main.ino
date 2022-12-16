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
  Serial.begin(9600);
}




int vitesse = 120;


//main 
void eviterObstacle(){
  int timeBack = 3000;
  int timeRight = 2000;
  while(true){
    if(capteurLaser.mesureLaser < 25){
      int time_now = millis();    
      while(millis() < time_now + timeBack){
        controleMoteur.goBack(vitesse);
      }
      time_now = millis(); 
      while(millis() < time_now + timeRight){
        controleMoteur.goRight(vitesse);
      }
      controleMoteur.goForward(vitesse);
    }else{
      break;
    }
    capteurLaser.capturerDistanceLaser();
  } 
}

int tmp = 0;
void loop() {
  tmp+=1;

  
  //capteur ultrason
  //capteurDistance.CapturerDistance();

  
  //capteur laser
  //capteurLaser.capturerDistanceLaser();


  //stratégie

  
  //position 
  /*Serial.print("x : ");
  Serial.println(cameraPosition.getX());
  Serial.print(" y : ");
  Serial.println(cameraPosition.getY());
  Serial.print(" laser : ");
  Serial.println(capteurLaser.mesureLaser);*/
  if (Serial.available() > 0) {
    String a= Serial.readString();
    if(a.equals("test\n")){
      cameraPosition.upLed();
    }
  }
  
  

  //Serial.print("toto");
  /*
  cameraPosition.motionBurst();

  controleMoteur.goForward(vitesse);
  eviterObstacle();
  
  */
  

  
  
}


 
