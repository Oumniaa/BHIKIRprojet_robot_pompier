#ifndef H_ControleMoteur
#define H_ControleMoteur
struct Moteur {
    int pinMA;
    int pinMB;
};

class ControleMoteur
{
  private :
    Moteur m1;
    Moteur m2;

  public :
   ControleMoteur(int M1A, int M1B, int M2A, int M2B);
   void goForward(int vitesse);
   void goRight(int vitesse);
   void goBack(int vitesse);
   void goLeft(int vitesse);
   
};

#endif 
