#include "BHIKIR_morse.h"
#include <arduino.h>

LettreMorse::LettreMorse(){}


/**void space sert à créer un espace entre les mot de 5s
 * Entre les lettre de 1s
 */
void LettreMorse::space () {
  int montemp_2 = 1*timer;
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
  int montemp_1 = 1*timer;
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
  int montemp_2 = 3*timer;
  int tempActuel = millis();
  while (millis() < tempActuel + montemp_2) {
  }
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("-");
  space();
}


/**On commence par determiner la longueur deu String avec la fonction .length(),on parcourt le nombre de char de notre String avec le for.
 * on précise alors le position du char avec .charAt
 * on met toute les lettres en MAJ grace à to UpperCase.
 * Et on traduit.s
 */
void LettreMorse::toDo(String mCode, int tm) {
  timer = tm;
  byte mCodeLength = mCode.length();
  char i;
  for (int x = 0; x <= mCodeLength; x++) {
    i = mCode.charAt(x);
    i = toUpperCase(i);
    morse(i);
  }
}


/**Traduction des lettres en morse.
 * Si c'est un ' A ' <=> ".-"
 */
void LettreMorse::morse(char i) {
  switch (i) {
    case 'A':
      high();
      low();
      break;
      
    case 'B':
      low();
      high();
      high();
      high();
      break;
      
    case 'C':
      low();
      high();
      low();
      high();
      break;

    case 'D':
      low();
      high();
      high();
      break;
      
    case 'E':
      high();
      break;
      
    case 'F':
      high();
      high();
      low();
      high();
      break;
      
    case 'G':
      low();
      low();
      high();
      break;
      
    case 'H':
      high();
      high();
      high();
      high();
      
    case 'I':
      high();
      high();
      break;
      
    case 'J':
      high();
      low();
      low();
      low();
      break;
      
    case 'K':
      low();
      high();
      low();
      break;
      
    case 'L':
      high();
      low();
      high();
      high();
      break;
      
    case 'M':
      low();
      low();
      break;
      
    case 'N':
      low();
      high();
      break;
      
    case 'O':
      low();
      low();
      low();
      break;
      
    case 'P':
      high();
      low();
      low();
      high();
      break;
      
    case 'Q':
      low();
      low();
      high();
      low();
      break;
      
    case 'R':
      high();
      low();
      high();
      break;
      
    case 'S':
      high();
      high();
      high();
      break;
      
    case 'T':
      low();
      break;
      
    case 'U':
      high();
      high();
      low();
      break;
      
    case 'V':
      high();
      high();
      high();
      low();
      break;
      
    case 'W':
      high();
      low();
      low();
      break;
      
    case 'X':
      low();
      high();
      high();
      low();
      break;
      
    case 'Y':
      low();
      high();
      low();
      low();
      break;
      
    case 'Z':
      low();
      low();
      high();
      high();
      break;

     case '1' :
      high();
      low();
      low();
      low();
      low();
      break;

      case '2':
      high();
      high();
      low();
      low();
      low();
      break;

       case '3' :
      high();
      high();
      high();
      low();
      low();
      break;

       case '4' :
      high();
      high();
      high();
      high();
      low();
      break;

       case '5' :
      high();
      high();
      high();
      high();
      high();
      break;

      case '6' :
      low();
      high();
      high();
      high();
      high();
      break;

      case '7' :
      low();
      low();
      high();
      high();
      high();

      case '8' :
      low();
      low();
      low();
      high();
      high();

      case '9' :
      low();
      low();
      low();
      low();
      high();

      case '0' :
      low();
      low();
      low();
      low();
      low();

      case ' ' :
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
