#include "BHIKIR_morse.h"

LettreMorse lm;               // on definit un objet lm appartenant à la classe LettreMorse.

String mCode = "So< s";      // Mot à traduire.
int timer = 200;             // Vitesse de période d'affichage en ms, à modifier selon le besoin.


void setup() {
  Serial.begin(9600);    // Baudrate.
  pinMode(LED_BUILTIN, OUTPUT);  // Led_Builtin représente la led de l'arduino. 
}

void loop() {
  lm.toDo(mCode, timer);
  /** Si vous voulez tester une phrase à partir du moniteur série :
     On définit un nouveau char monitChar, qu'on rajoute à notre mCode à traduire.
     Si notre char est equivalent à une nouvelle ligne c'est la fin de notre boucle.
     Et on traduit :
     while (Serial.available()) {
    char monitChar = (char)Serial.read();
    mCode += monitChar;
    if (inChar == '\n') {
      Serial.println(mCode);
      toDo();
    }
    }*/
}
