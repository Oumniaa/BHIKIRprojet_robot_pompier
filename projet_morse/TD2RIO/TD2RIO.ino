/*
 * Strucuture LettreMorse
 * 
 * structure permettant de lier une lettre et son code morse (1= led allumé, 0= led éteinte )
 */
struct LettreMorse {
    char lettre;
    String code;
};


//taille du tableau des données
const int lenghtTab = 37;
//pin correspondant à la led
const int pinLed = 13;
//temps d'attente lors des impultions du code 
const int timeStop = 200;
//variable pour faire fonctionner millis 
unsigned long time_now = 0;

/*
 * Class : Traducteur
 * 
 * Cette classe va traduire une phrase en morse à l'aide d'un tableau contenant des lettres morses 
 */
class Traducteur {
  public:
    LettreMorse monTabLettre [lenghtTab];
    Traducteur(LettreMorse monTabLettre [lenghtTab]);
    void convertionMotEnCligno(String mot);

  private:
    bool trouverLettre(int cpt, String phrase);
    int value = 0;
    
    
};

/*
 * Constructeur de Traducteur
 * 
 * param : LettreMorse monTabLettre [26] : Un tableau de lettre morse sur le lequel va s'appuyer le programme pour traduire les mots
 *  
 */
Traducteur::Traducteur(LettreMorse monTabLettre [lenghtTab]){
  for(int cpt=0;cpt<lenghtTab;cpt++){
    this->monTabLettre[cpt] = monTabLettre[cpt];
  }
}



/*
 * fonction trouverLettre
 * 
 * param : int cpt = compteur pointant la position de la lettre courante dans la phrase
 *         String phrase = notre phrase à traduire
 * 
 * Fonction cherchant une lettre dans le tableau est retourne True si la lettre à été trouvé sinon retourne false.
 * Si la lettre a été trouvé, cette fonction va également affecter à "value" la LettreMorse correspondante.
 * 
 */
bool Traducteur::trouverLettre(int cpt, String phrase){
  bool trouve = false;
  for(int cpt2=0;cpt2<lenghtTab-1;cpt2++){
    if(monTabLettre[cpt2].lettre == phrase[cpt]){
      this->value = cpt2;
      trouve = true;
      break;
    }
  }
  return trouve;
}

/*
 * convertionMotEnCligno(String phrase)
 * 
 * param : String phrase = un string contenant la phrase à traduire
 * 
 * Cettes fonction va traduire la phrase lettre par lettre en code morse (sur la led)
 * 
 */
void Traducteur::convertionMotEnCligno(String phrase){
  int value;
  for(int cpt=0;cpt<phrase.length()-1;cpt++){
    bool trouve = trouverLettre(cpt,phrase);
    if(trouve){
      Serial.print("en cour d'écriture de la lettre : "+monTabLettre[this->value].lettre);
      for(int cpt=0;cpt <monTabLettre[this->value].code.length()-1; cpt++){
        time_now = millis();
        if(monTabLettre[this->value].code[cpt]=='1'){
          digitalWrite(pinLed, HIGH);
          while(millis() < time_now + timeStop){
              //wait approx. [timeStop] ms
          }
        }else{
          digitalWrite(pinLed, HIGH);
          while(millis() < time_now + timeStop){
              //wait approx. [timeStop] ms
          }
        }
      }
    } else { //pour débug
      Serial.print("on saute "+ phrase[cpt]);
    }
    
  }
  digitalWrite(pinLed, LOW);  
}


//main :
LettreMorse a={'a',"01"};
LettreMorse b={'b',"1000"};
LettreMorse c={'c',"1010"};
LettreMorse d={'d',"100"};
LettreMorse e={'e',"0"};
LettreMorse f={'f',"0010"};
LettreMorse g={'g',"110"};
LettreMorse h={'h',"0000"};
LettreMorse i={'i',"00"};
LettreMorse j={'j',"0111"};
LettreMorse k={'k',"101"};
LettreMorse l={'l',"0100"};
LettreMorse m={'m',"11"};
LettreMorse n={'n',"10"};
LettreMorse o={'o',"111"};
LettreMorse p={'p',"0110"};
LettreMorse q={'q',"1101"};
LettreMorse r={'r',"010"};
LettreMorse s={'s',"000"};
LettreMorse t={'t',"1"};
LettreMorse u={'u',"001"};
LettreMorse v={'v',"0001"};
LettreMorse w={'w',"011"};
LettreMorse x={'x',"1001"};
LettreMorse y={'y',"1011"};
LettreMorse z={'z',"1100"};
LettreMorse v0={'0',"11111"};
LettreMorse v1={'1',"01111"};
LettreMorse v2={'2',"00111"};
LettreMorse v3={'3',"00011"};
LettreMorse v4={'4',"00001"};
LettreMorse v5={'5',"00000"};
LettreMorse v6={'6',"10000"};
LettreMorse v7={'7',"11000"};
LettreMorse v8={'8',"11100"};
LettreMorse v9={'9',"11110"};
LettreMorse esp={' ',"11111"};

LettreMorse monTabLettreMorse [lenghtTab] = {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,esp};
Traducteur trad(monTabLettreMorse);


void setup () {
  Serial.begin(57600);
  Serial.print("Hello World");
  pinMode(13, OUTPUT);
}

void loop () {
  //test une lettre
  trad.convertionMotEnCligno("a");
  //test un mot
  //trad.convertionMotEnCligno("test");
  //test une pharse
  //trad.convertionMotEnCligno("test une phrase !");
}
