#include <TimerOne.h>
#include <struc_moteur.h>
#include "CapteurDistance.h"
#include "CameraPosition.h"
#include "CapteurLaser.h"

//definition constante 
const int deltaTime = 20;
const int pinInteruptMoteurG = 0; //corespond au pin 2 de la carte
const int pinInteruptMoteurD = 1; //corespond au pin 3 de la carte

//pas d'encoder
const float multG = -1; //mult du moteur gauche 
const float multD = -1; //mult du moteur droit


//pin enable moteur gère la vitesse du moteur gauche (G)
const int ENG = 9;
//pin enable moteur gère la vitesse du moteur droite (D)
const int END = 10;
//pin permettant de controller le sens de rotation du moteur Gauche
const int ING1 = 4;
const int ING2 = 5;
//pin permettant de controller le sens de rotation du moteur Droit
const int IND1 = 6;
const int IND2 = 7;

//pin du capteur de distance 
const int echo = 13;
const int trig = 12;

const int pinLedRougeCamera = 48;

CapteurDistance capteurDistance (trig, echo);

CameraPosition cameraPosition(pinLedRougeCamera);

CapteurLaser capteurLaser;

//initialisation du moteur gauche 
struct Moteur moteurG = { 
    pinInteruptMoteurG,
    0, 
    multG,
    ENG,
    ING1,
    ING2,
    0,
    0
 };

//initialisation du moteur gauche 
struct Moteur moteurD = { 
    pinInteruptMoteurD,
    0, 
    multD,
    END,
    IND1,
    IND2,
    0,
    0
 };


void setup() {
  //initialisation du serial 
  Serial.begin(57600);
  //confugration des pin du pont en h du moteur gauche
  pinMode(moteurG.pinEnable, OUTPUT);
  pinMode(moteurG.pinIN1, OUTPUT);
  pinMode(moteurG.pinIN2, OUTPUT);
  analogWrite(moteurG.pinEnable, 0);

  //confugration des pin du pont en h du moteur droite
  pinMode(moteurD.pinEnable, OUTPUT);
  pinMode(moteurD.pinIN1, OUTPUT);
  pinMode(moteurD.pinIN1, OUTPUT);
  analogWrite(moteurD.pinEnable, 0);
}

void goBackMoteurD(){
  digitalWrite(moteurD.pinIN1,HIGH);
  digitalWrite(moteurD.pinIN2,LOW);
}

void goBackMoteurG(){
  digitalWrite(moteurG.pinIN1,LOW);
  digitalWrite(moteurG.pinIN2,HIGH);
}

void goFrontMoteurD(){
  digitalWrite(moteurD.pinIN1,LOW);
  digitalWrite(moteurD.pinIN2,HIGH);
}

void goFrontMoteurG(){
  digitalWrite(moteurG.pinIN1,HIGH);
  digitalWrite(moteurG.pinIN2,LOW);
}

void goBack(){
  goBackMoteurD();
  goBackMoteurG();
}

void goFront(){
  goFrontMoteurD();
  goFrontMoteurG();
}

void turnR(){
  goBackMoteurG();
  goFrontMoteurD();
}
void turnL(){
  goBackMoteurD();
  goFrontMoteurG();
}


//vitessse set to 0
void stopMoteurG(){
  analogWrite(moteurG.pinEnable, 0);
}

//vitessse set to 0
void stopMoteurD(){
  analogWrite(moteurD.pinEnable, 0);
}

void stopM(){
  stopMoteurD();
  stopMoteurG();
}


//vit compris entre 0 et 255 avec 255 en max
void setVitesseMoteurD(int vit){
  analogWrite(moteurD.pinEnable, vit);
}
void setVitesseMoteurG(int vit){
  analogWrite(moteurG.pinEnable, vit);
}

//main 
void eviterObstacle(){
  int timeBack = 3000;
  int timeRight = 2000;
  while(true){
    if(capteurDistance.distance < 10){
      int time_now = millis();    
      while(millis() < time_now + timeBack){
        turnR();
      }
      goFront();
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
  
  //sens des moteurs
  goFront();
  //vitesse
  setVitesseMoteurD(255);
  setVitesseMoteurG(255);
  //stratégie
  eviterObstacle();
  //position 
  cameraPosition.upLed();
  cameraPosition.motionBurst();
  Serial.print("x : ");
  Serial.println(cameraPosition.getX());
  Serial.print("y : ");
  Serial.println(cameraPosition.getY());

  
  
}


 
