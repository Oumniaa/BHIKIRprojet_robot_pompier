#include <arduino.h>

/**La classe morse contient : 
 * la fonction "void morse" résponsable de traduire chaque char en son equivalent en morse.
 * le constructeur.
 * void toDo appelée ensuite dans la loop.
 * void high low et space chargé de gerer l'intensité du clignotement
 */
class LettreMorse {
  public:
    LettreMorse();
    void toDo(String, int);
    int timer;
  private:
    void morse(char);
    void high();
    void low();
    void space();
};
