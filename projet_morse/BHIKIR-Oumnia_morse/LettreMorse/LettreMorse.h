//BHIKIR Oumnia
#include <arduino.h>

/**La classe morse contient : 
 * la fonction "void morse" résponsable de traduire chaque char en son equivalent en morse.
 * le constructeur.
 */
class LettreMorse {
  public:
    LettreMorse();
    void traduction(String, int);
    int timer;
    void space();
  private:
    void morse(char);
    void high();
    void low();
    
};
