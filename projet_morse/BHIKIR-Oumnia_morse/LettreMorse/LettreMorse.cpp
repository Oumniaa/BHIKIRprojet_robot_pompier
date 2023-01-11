#include "LettreMorse.h"
#include <arduino.h>

LettreMorse::LettreMorse() {}


/**Grace à la boucle while void space sert à créer un espace entre les mot de 5s grace à la boucle while
 * L'espace entre les signaux d'une même lettre est égal à un point.
 *L'espace entre deux lettres est égal à deux points.
 *L'espace entre deux mots est égal à trois points.
 */
void LettreMorse::space() {
  int montemp_2 = 3 * timer;
  int tempActuel = millis();
  while (millis() < tempActuel + montemp_2) {
  }
}


/** void high est la fonction responsable d'une courte illumination d' 1s de la led d'arduino.
 * illustré par un '.' dans le moniteur de série.
 * millis() se remet à 0 lorsqu'il atteint 1s.
*/
void LettreMorse::high() {
  //i == '.';
  digitalWrite(LED_BUILTIN, HIGH);
  int montemp_1 = 1 * timer;
  int tempActuel = millis();
  while (millis() < tempActuel + montemp_1) {
  }
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println(".");
  space();
}


/** void low est la fonction responsable d'une longue illumination de 3s de la led d'arduino. 
 * illustré par un '-' dans le moniteur de série.
 * millis() se remet à 0 lorsqu'il atteint 3s.
 */
void LettreMorse::low() {
  //i == '-';
  digitalWrite(LED_BUILTIN, HIGH);
  int montemp_2 = 3 * timer;
  int tempActuel = millis();
  while (millis() < tempActuel + montemp_2) {
  }
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("-");
  space();
}


/**On commence par determiner la longueur deu String avec la fonction .length(),on parcourt le nombre de char de notre String avec le for.
 * elle prend en entrée un string ( le mot à traduire) et un temps (entier).
 * on précise alors le position du char avec .charAt
 * on met toute les lettres en MAJ grace à to UpperCase.
 * Et on traduit.s
 */
void LettreMorse::traduction(String mCode, int tm) {
  timer = tm;
  byte mCodeLength = mCode.length();
  char i;
  for (int x = 0; x <= mCodeLength; x++) {
    i = mCode.charAt(x);
    i = toUpperCase(i);
    morse(i);
    space();
  }
}


/**Traduction des lettres en morse.
 * elle prend en entrée un charactere i ( qui constitue le mot à traduire).
 * Si c'est un ' A ' <=> ".-"
 */
void LettreMorse::morse(char i) {
  switch (i) {
    case 'A':
      high();
      low();
      space();
      break;

    case 'B':
      low();
      high();
      high();
      high();
      space();
      break;

    case 'C':
      low();
      high();
      low();
      high();
      space();
      break;

    case 'D':
      low();
      high();
      high();
      space();
      break;

    case 'E':
      high();
      space();
      break;

    case 'F':
      high();
      high();
      low();
      high();
      space();
      break;

    case 'G':
      low();
      low();
      high();
      space();
      break;

    case 'H':
      high();
      high();
      high();
      high();
      space();
      break;

    case 'I':
      high();
      high();
      space();
      break;

    case 'J':
      high();
      low();
      low();
      low();
      space();
      break;

    case 'K':
      low();
      high();
      low();
      space();
      break;

    case 'L':
      high();
      low();
      high();
      high();
      space();
      break;

    case 'M':
      low();
      low();
      space();
      break;

    case 'N':
      low();
      high();
      space();
      break;

    case 'O':
      low();
      low();
      low();
      space();
      break;

    case 'P':
      high();
      low();
      low();
      high();
      space();
      break;

    case 'Q':
      low();
      low();
      high();
      low();
      space();
      break;

    case 'R':
      high();
      low();
      high();
      space();
      break;

    case 'S':
      high();
      high();
      high();
      space();
      break;

    case 'T':
      low();
      space();
      break;

    case 'U':
      high();
      high();
      low();
      space();
      break;

    case 'V':
      high();
      high();
      high();
      low();
      space();
      break;

    case 'W':
      high();
      low();
      low();
      space();
      break;

    case 'X':
      low();
      high();
      high();
      low();
      space();
      break;

    case 'Y':
      low();
      high();
      low();
      low();
      space();
      break;

    case 'Z':
      low();
      low();
      high();
      high();
      space();
      break;

    case '1':
      high();
      low();
      low();
      low();
      low();
      space();
      break;

    case '2':
      high();
      high();
      low();
      low();
      low();
      space();
      break;

    case '3':
      high();
      high();
      high();
      low();
      low();
      space();
      break;

    case '4':
      high();
      high();
      high();
      high();
      low();
      space();
      break;

    case '5':
      high();
      high();
      high();
      high();
      high();
      space();
      break;

    case '6':
      low();
      high();
      high();
      high();
      high();
      space();
      break;

    case '7':
      low();
      low();
      high();
      high();
      high();
      space();
      break;

    case '8':
      low();
      low();
      low();
      high();
      high();
      space();
      break;

    case '9':
      low();
      low();
      low();
      low();
      high();
      space();
      break;

    case '0':
      low();
      low();
      low();
      low();
      low();
      space();
      break;

    case ' ':
      space();
      space();
      space();
      space();
      space();
      break;
    default:
      break;
  }
}
