#include <ADNS3080.h>
#include "CameraPosition.h"

#define PIN_RESET     49        // SPI pins:
#define PIN_CS        53
#define LED_MODE      false     // Enable LED Mode
#define RESOLUTION    false     // Enable high resolution mode 

ADNS3080 <PIN_RESET, PIN_CS> sensor;

// Initial position


int pinLEDRouge = 40;

CameraPosition::CameraPosition(int pinLedRouge ) {
  this->pinLedRouge = pinLedRouge;
  this->x = 0;
  this->y = 0;
  
  
  sensor.setup( LED_MODE, RESOLUTION );
  pinMode(pinLEDRouge, OUTPUT);
  Serial.begin(9600);
}

void CameraPosition::motionBurst(){
  sensor.motionBurst( &this->motion, &this->over_flow, &this->dx, &this->dy, &this->squal, &this->shutter, &this->max_pixel );
  this->x += dx;
  this->y += dy;
}

int CameraPosition::getX(){
  return this->x;
}
int CameraPosition::getY(){
  return this->y;
}
