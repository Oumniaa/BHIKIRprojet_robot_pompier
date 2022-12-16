#ifndef H_CameraPosition
#define H_CameraPosition

class CameraPosition
{
  private :
    int pinLedRouge;
    uint8_t  motion;      // Did motion occur? true or false
    uint8_t  over_flow;   // Did the displacement registers overflow? true of false. Occurs if |dx| > 125 or |dy| > 125
    int8_t   dx, dy;      // Displacement since last function call
    uint8_t  squal;       // Surface quality value - Larger value means better tracking. If below ~15 the displacement is dissabled. Adjust focus for 30 or more.
    uint16_t shutter;     // Camera shutter rate in clock cycles.
    uint8_t  max_pixel;
    int x = 0;
    int y = 0;
    
  public :
    CameraPosition(int pinLedRouge );
    void motionBurst();
    int getX();
    int getY();
    void upLed();
    void downLed();
    
};

#endif 
