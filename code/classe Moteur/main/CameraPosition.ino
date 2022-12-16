#include <ADNS3080.h>
#include "CameraPosition.h"

#define PIN_RESET     49        // SPI pins:
#define PIN_CS        53
#define LED_MODE      false     // Enable LED Mode
#define RESOLUTION    false     // Enable high resolution mode 

ADNS3080 <PIN_RESET, PIN_CS> sensor;

// Initial position

/**
 * Constructeur de la classe caméra
 * 
 * Setup la caméra et initialise la position du robt 
 */
CameraPosition::CameraPosition(int pinLedRouge ) {
  this->pinLedRouge = pinLedRouge;
  this->x = 0;
  this->y = 0;
  
  sensor.setup( LED_MODE, RESOLUTION );
  pinMode(this->pinLedRouge, OUTPUT);
}

/**
 * Obtenir toute les informations de la caméra 
 * motion = Une mesure est éffectué (1) ou non (0)
 * overflow = Nombre de pixel capté
 * dx = déplacement en vitesse en x
 * dy = déplacement en vitesse en y
 * squal = 
 * shutter = 
 * maxpixel = 
 * x = position en x depuis le départ
 * y = position en y depuis le départ
 */
void CameraPosition::motionBurst(){
  sensor.motionBurst( &this->motion, &this->over_flow, &this->dx, &this->dy, &this->squal, &this->shutter, &this->max_pixel );
  this->x -= dy/10;//on inverse car la caméra est placé dans ce sens là sur le robot
  this->y += dx/10;//on divise par 10 pour passé en cm 
}

/**
 * Methode afin d'allumer la led rouge afin de faire fonctionnner mieux la caméra
 */
void  CameraPosition::upLed(){
  digitalWrite(this->pinLedRouge, HIGH);
}
/**
 * Methode afin d'allumer la led rouge afin de faire fonctionnner mieux la caméra
 */
void  CameraPosition::downLed(){
  digitalWrite(this->pinLedRouge, LOW);
}


int CameraPosition::getX(){
  return this->x;
}
int CameraPosition::getY(){
  return this->y;
}
