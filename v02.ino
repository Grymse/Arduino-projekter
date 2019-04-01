#include <FastLED.h>
#define NUM_LEDS    238
CRGB led1[NUM_LEDS];
CRGB led2[NUM_LEDS];

void setup() {

  // Redegører for LED'ernes eksistens og at de kan kommunikeres med via 4 og 6
  FastLED.addLeds<WS2812B, 6, GRB>(led1, NUM_LEDS);
  FastLED.addLeds<WS2812B, 4, GRB>(led2, NUM_LEDS);

}


// Farvekode-tabel
int farve[6][3] = {
  {255, 0, 0},
  {0, 255, 0},
  {150, 150, 0},
  {150, 0, 150},
  {0, 0, 255},
  {0, 150, 150}
};

int antalfarver = 6;



// Funktion der sætter alle LED'er til sort, uden at opdatere LED'erne.
void blank(){

  for (int i = 0;i<230;i++){
     led1[i] = CRGB(0,0,0);
     led2[i] = CRGB(0,0,0);
  }
}



/*
Funktion der sætter alle 46 LED'er pr lampe sammen under et ID.
Da jeg har to LED udgange, har jeg også samlet dem, så højre side
har ID'erne 0-4 og venstre side har 5-9. På den måde kan jeg lave
andre fede effekter, og let komme til lamperne gennem en funktion.
*/

void lampe(int id, int f1, int f2, int f3){
  // Under ID 5, brug led1
  if(id<5){
    for (int i=0;i<46;i++){
      led1[i+id*46] = CRGB(f1, f2, f3);
    }
    
  // Under ID 10 og over 4, brug led2
  }else if(id<10){
    for (int i=0;i<46;i++){    
      led2[i+(id-5)*46] = CRGB(f1, f2, f3);
    }
  }
};

////////////////////////////
/////// ANIMATIONER ///////
////////////////////////////

// Havde brug for et par int's til efterfølgende funktion.
int rdm1;
int rdm2;

// SKIFTER FRA SIDE TIL SIDE
void sideskift(){

  // Sættes til 0, da den skal bruges til at finde ud af hvilken farvekode der skal bruges.
  rdm1 = 0;
  
  for (int gentag = 0;gentag<8;gentag++){
    // Det følge skal gentages to gange, da der er to sider:
    for (int z = 0;z<2;z++){    
    
      // Sæt alle 5 lamper i højre side til den nuværende farve
      for (int i = 0;i<5;i++){
        
        //Hidkalder min tidligere funktion og sætter farven til den nuværende farve, fra farveskemaet.
        // Jeg har ganget det med 0.15, da det gav alt for meget lys i rummet ellers.
        lampe(i+z*5,farve[rdm1][0]*0.15,farve[rdm1][1]*0.15,farve[rdm1][2]*0.15);
    
      }
      // Funktion som opdaterer lamperne
      FastLED.show();
      // Delay funktion, så der går tid mellem hvert farveskift
      delay(200);
    
      for (int i = 0;i<5;i++){

        lampe(i+z*5,0,0,0);
    
      }

      // Ny farvekode
      rdm1++;
      if(rdm1>=antalfarver){
        rdm1=0;
      }
    
      delay(200);
    }
  }
};


// Sideskift, men lamperne blinker, og giver derfor noget mørke i lokalet.
void sideskiftblink(){

  rdm1 = 0;
  
  for (int gentag = 0;gentag<8;gentag++){
    
    for (int z = 0;z<2;z++){    
    
      for (int i = 0;i<5;i++){
        
        lampe(i+z*5,farve[rdm1][0]*0.15,farve[rdm1][1]*0.15,farve[rdm1][2]*0.15);
    
      }
      // Funktion som opdaterer lamperne
      FastLED.show();
      // Delay funktion, så der går tid mellem hvert farveskift
      delay(200);
    
      for (int i = 0;i<5;i++){

        lampe(i+z*5,0,0,0);
    
      }

      // Ny farvekode
      rdm1++;
      if(rdm1>=antalfarver){
        rdm1=0;
      }

      FastLED.show();
      delay(200);
    }
  }
};

// Løbelys animation.
void loeb(){

  for (int z = 0;z<antalfarver;z++){
  for (int i = 0;i<5;i++){

    lampe(i,farve[z][0],farve[z][1],farve[z][2]);
    lampe(i+5,farve[z][0],farve[z][1],farve[z][2]);
    FastLED.show();
    delay(60);
    lampe(i,0,0,0);
    lampe(i+5,0,0,0);
    delay(60);
  }
  FastLED.show();
  delay(120);
  }
  
};

// Sideskift løb
void loeb2(){

  for (int z = 0;z<antalfarver;z++){
  for (int i = 0;i<10;i++){

    int z = i-2;
    if(0<=z){
      lampe(z,0,0,0);
    }else{
      lampe(10+z,0,0,0);
    }
    
    lampe(i,farve[z][0],farve[z][1],farve[z][2]);
    FastLED.show();
    delay(120);
  }
  }
  
};


// Sideskift løb 2
void loeb3(){

  for (int z = 0;z<antalfarver;z++){
    for (int i = 0;i<5;i++){
      for (int iz = 0;iz<2;iz++){
        lampe(i+iz*5,farve[z][0],farve[z][1],farve[z][2]);
        FastLED.show();
        delay(60);
        lampe(i+iz*5,0,0,0);
      
      }
    }
  }
};

// Funktion der får en tilfældig lampe til at lyse op.
void rdm(){

  for (int z = 0;z<antalfarver;z++){  

  rdm1 = random(0,9);

  lampe(rdm1,farve[z][0],farve[z][1],farve[z][2]);
  FastLED.show();
  delay(200);

  lampe(rdm1,0,0,0);
  delay(200);
  }
};

// En tabel, hvori jeg har lavet et 16-step lang animation.
int k[16][3] = {
  {0,2,4},
  {6,8,10},
  {1,3,10},
  {5,7,9},
  {0,5,10},
  {2,7,10},
  {4,9,10},
  {0,9,10},
  {2,7,10},
  {4,5,10},
  {0,4,10},
  {1,3,10},
  {2,11,10},
  {5,9,10},
  {6,7,10},
  {7,11,10}
};

// Tabellen ovenover overføres til virkelighed gennem nedenstående funktion.
void pattern() {
  for(int z = 0;z<16;z++){
    rdm1++;
    if(rdm1>=antalfarver){
      rdm1=0;
    }

    for(int i = 0;i<3;i++){
      lampe(k[z][i],farve[rdm1][0]*0.6,farve[rdm1][1]*0.6,farve[rdm1][2]*0.6);
    }
    FastLED.show();
    delay(200);
    blank();
    delay(200);
}
}

// Overstående funktion, men med mørke ind i mellem.
void patternblink() {
  for(int z = 0;z<16;z++){
    rdm1++;
    if(rdm1>=antalfarver){
      rdm1=0;
    }

    for(int i = 0;i<3;i++){
      lampe(k[z][i],farve[rdm1][0],farve[rdm1][1],farve[rdm1][2]);
    }
    FastLED.show();
    delay(200);
    blank();
    FastLED.show();
    delay(200);
}
}




// ANIMATIONERNES RÆKKEFØLGE:
void loop() {
  pattern();
  patternblink();
  rdm();
  loeb();
  patternblink();
  loeb3();
  sideskift();
  sideskiftblink();
  loeb2();
}
