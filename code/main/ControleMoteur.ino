#include "ControleMoteur.h"

ControleMoteur::ControleMoteur(int M1A, int M1B, int M2A, int M2B) {
  this->m1.pinMA = M1A;
  this->m1.pinMB = M1B;
  this->m2.pinMA = M2A;
  this->m2.pinMB = M2B;
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
}

void ControleMoteur::goForward(int vitesse){
  analogWrite(m1.pinMA, vitesse);
  analogWrite(m1.pinMB, 0);
  analogWrite(m2.pinMA, vitesse);
  analogWrite(m2.pinMB, 0);
}

void ControleMoteur::goRight(int vitesse){
  analogWrite(m1.pinMA, 0);
  analogWrite(m1.pinMB, vitesse);
  analogWrite(m2.pinMA, vitesse);
  analogWrite(m2.pinMB, 0);
}


void ControleMoteur::goLeft(int vitesse){
  analogWrite(m1.pinMA, vitesse);
  analogWrite(m1.pinMB, 0);
  analogWrite(m2.pinMA, 0);
  analogWrite(m2.pinMB, vitesse);
}


void ControleMoteur::goBack(int vitesse){
  analogWrite(m1.pinMA, 0);
  analogWrite(m1.pinMB, vitesse);
  analogWrite(m2.pinMA, 0);
  analogWrite(m2.pinMB, vitesse);
}
