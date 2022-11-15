#ifndef H_CapteurDistance
#define H_CapteurDistance


class CapteurDistance
{
  private :
  int trig ;
  int echo ;

  public :
   float calcul_echo;
   float distance;
   CapteurDistance(int trig, int echo);
   void CapturerDistance();
};

#endif 
