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



/**
 * setup
 * 
 * Initialise les communications series.
 */
void setup() {
  //initialisation du serial
  Serial.begin(9600);
  cameraPosition.upLed();
}




int vitesse = 250;


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

/**
 * uartSendMsg
 * 
 * Envoyer un message dans UART 3
 * 
 * 
 */

void uartSendMsg(String msg, boolean doFlush=false){
  if(doFlush){
    Serial3.flush();
  }
  Serial3.print(msg + "\n"); 
}


int tmp = 0;


/**
 * Fontion main 
 * 
 * Lancent les différentes fonctions afin de controller le robot
 */

void loop() {
  

 
  //capteur ultrason
  capteurDistance.CapturerDistance();

  
  //capteur laser
  capteurLaser.capturerDistanceLaser();


  //stratégie

  
  //position 
  cameraPosition.motionBurst();
  Serial.print("x : ");
  Serial.println(cameraPosition.getX());
  Serial.print(" y : ");
  Serial.println(cameraPosition.getY());
  Serial.print(" laser : ");
  Serial.println(capteurLaser.mesureLaser);
  Serial.print(" ultrason : ");
  Serial.println(capteurDistance.distance);

  
  //Communication UART
  /*
  uartSendMsg("test",true);
  delay(3000);
  delay(1000);
  Serial.println(Serial3.read(),HEX);
  */
  /*
  while(Serial3.available() > 0) {
    String msg= Serial3.readString();
    cameraPosition.upLed();
    uartSendMsg(msg,true);
    if(msg.equals("test\n")){
      cameraPosition.upLed();
    }
  }*/
  
  

  
  controleMoteur.goForward(vitesse);
  //eviterObstacle();
  
  
}




 
