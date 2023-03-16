#include "CapteurLaser.h"
#include "Adafruit_VL53L0X.h"


Adafruit_VL53L0X capteur = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t mesure;
 
CapteurLaser::CapteurLaser() {
}

 
void CapteurLaser::capturerDistanceLaser() {
  capteur.begin();
  capteur.rangingTest(&mesure, false); // 'true' informations de debuggage
  // RangeStatus = 4 signifie que le mesure est erronée
  if (mesure.RangeStatus != 4) {   
    mesureLaser = mesure.RangeMilliMeter/10;
  }
  else {
    mesureLaser = -1;
    
  }
}
