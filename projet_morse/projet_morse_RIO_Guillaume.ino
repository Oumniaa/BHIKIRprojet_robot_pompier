
struct LettreMorse {
    char lettre;
    String code;
};


class Traducteur {
  public:
    LettreMorse monTabLettre [26];
    Traducteur::Traducteur(LettreMorse monTabLettre [26]);
    convertionMotEnCligno(String mot);
    
};
Traducteur::Traducteur(LettreMorse monTabLettre [26]){
  for(int cpt=0;cpt<26;cpt++){
    this->monTabLettre[cpt] = monTabLettre[cpt];
  }
}

Traducteur::convertionMotEnCligno(String mot){
  int value;
  for(int cpt=0;cpt<mot.length();cpt++){
    for(int cpt2=0;cpt2<26;cpt2++){
      if(monTabLettre[cpt2].lettre == mot[cpt]){
        value = cpt2;
        break;
      }
    }
    for(int cpt=0;cpt <monTabLettre[value].code.length(); cpt++){
      if(monTabLettre[value].code[cpt]=='1'){
        digitalWrite(13, HIGH);
        delay(200);
      }else{
        digitalWrite(13, LOW);
        delay(200);
      }
    }
    
  }
  digitalWrite(13, LOW);
  
}
LettreMorse a = {'a',"01"};
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
LettreMorse monTabLettreMorse [26] = {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z};
Traducteur trad(monTabLettreMorse);






void setup () {
  Serial.begin(57600);
  Serial.print("Hello World");
  pinMode(13, OUTPUT);
}

void loop () {
  trad.convertionMotEnCligno("test");
}
