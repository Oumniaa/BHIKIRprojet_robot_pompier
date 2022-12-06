#include "CapteurDistance.h"

CapteurDistance::CapteurDistance( int trig, int echo){
  this->trig = trig; // on commence toujours par constructeur et le this pour préciser que le trug d'en bas metionne celui d'en haut
  this->echo = echo;
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
} 
 
void CapteurDistance::CapturerDistance(){
    digitalWrite(trig,HIGH);
    delayMicroseconds(10); // pour avoir en milliseconde 
    digitalWrite(trig,LOW);
    calcul_echo = pulseIn(echo,HIGH);
    delay(100);
    distance = calcul_echo*0.034/2;
    Serial.println(distance);
}
