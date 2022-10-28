
class CapteurDistance
{
  private :
  int trig ;
  int echo ;

  public :
   float calcul_echo;
   float vitesse;
   CapteurDistance(int trig, int echo);
   void CapturerDistance();
};

CapteurDistance::CapteurDistance( int trig, int echo){
  this->trig = trig; // on commence toujours par constructeur et le this pour préciser que le trug d'en bas metionne celui d'en haut
  this->echo = echo;
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
} 
 
void CapturerDistance::CapteurDistance(){
    digitalWrite(trig,HIGH);
    delayMicroseconds(10); // pour avoir en milliseconde 
    digitalWrite(trig,LOW);
       calcul_echo = pulseIn(echo,HIGH);
       delay(100);
       Serial.println(calcul_echo*0.034/2);
    
  };
CapturerDistance distance = CapteurDistance(8,9);
void setup(){
  Serial.begin(9600);

  };
void loop() {

   distance.CapturerDistance();

};



 
