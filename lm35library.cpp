#include "lm35library.h" 
#include <Arduino.h>

//const byte LED_PIN = 13; //use the LED @ Arduino pin 13
// déclaration des variables globales de classe
// -- diviseur de base
float divider = 0.48828125 ;
// -- offset de base pour les lectures. C'est une température à rajouter
float offset = 0.8 ;
// -- tableau des 20 dernieres mesures afin de faire une moyenne
int lastsens[20] ;
int nbmesures = 20;
int maxindex = 0;
int pin_LM35 ;


//<<constructor>>
LM35::LM35(){
}


//<<destructor>>
LM35::~LM35(){/*nothing to destruct*/}

// méthode de démarrage
void LM35::begin(int lm35pin){
  float templm35 ;
  // affectation de la pin de lecture
  pin_LM35 = lm35pin ;
  maxindex = nbmesures-1;
  // premiere lecture
  templm35 = analogRead(pin_LM35) * divider ;
  // remplissage du tableau des moyennes
  for (int i = 0 ; i < nbmesures ; i++) {
    templm35 = analogRead(pin_LM35) * divider ;
    lastsens[i] = templm35 ; 
    delay(1);
  }
}

// lecture de la valeur en cours
float LM35::lm35read(){
  float correctedtemp;
  float templm35;
  float total ;
  
  // lecture brute
  templm35 = analogRead(pin_LM35) * divider;
  // on fait une moyenne des x dernieres mesures
  total = 0;
  for (int i=0; i < maxindex; i++) {
    int j;
    j = i+1;
    lastsens[i] = lastsens[j];
    total = total + lastsens[i];    
  }
  lastsens[maxindex] = templm35;
  total = total + lastsens[maxindex];
  correctedtemp = total / nbmesures;

  return correctedtemp;
}
