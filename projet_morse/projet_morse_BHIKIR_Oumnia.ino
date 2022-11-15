class LettreMorse {
  public :
    LettreMorse ();
    void morse(char ch); 
};
int pin = 13;
int t=1000;
// On définit le constructeur meme s'il n y a rien dedans.
LettreMorse::LettreMorse(){
}

// first : on traduit les lettres individuellement en clignotement.
// ma classe ne contion que la fonction void morse chargée de traduire les lettres en clignotement.
    // En morse 3*t representera la durée longue et t la courte.pinMode(pin,OUTPUT); // on définit le pin 13 en OUTPUT.
void LettreMorse::morse(char ch){
   if(ch=='a')
  {
    digitalWrite(pin,HIGH);
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='b')
  {
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH); 
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH); 
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH); 
    delay(t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='c')
  {
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='d')
  {
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='e')
  {
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='f')
  {
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='g')
  {
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='h')
  {
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='i')
  {
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='j')
  {
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='k')
  {
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='l')
  {
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='m')
  {
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='n')
  {
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='o')
  {
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='p')
  {
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='q')
  {
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='r')
  {
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='s')
  {
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='t')
  {
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='u')
  {
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='v')
  {
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='w')
  {
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='x')
  {
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='y')
  {
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
  else if(ch=='z')
  {
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(3*t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(t);
    digitalWrite(pin,HIGH);  
    delay(t);
    digitalWrite(pin,LOW);
    delay(3*t);
  }
}     // fin de la fonction morse traductrice des lettres.

LettreMorse lm;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);  // Baudrate.
pinMode(pin,OUTPUT); // on définit le pin 13 en OUTPUT.

}

void loop() {
  // put your main code here, to run repeatedly:
    String mot = "hello"; // test de la convertion du mot hello en morse.
if (mot.length () > 0){   //lire le dernier charachtère stocké. 
 
  Serial.println(mot);

  char emplacement;
       for (int i=0; i< mot.length() ; i++){
           emplacement = mot.charAt(i); // accéder à l'emplacement d'un string.
           Serial.println(emplacement);
           lm.morse(emplacement);
  }
 }
  
}
