#include <Braccio.h>
#include <Servo.h>


Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

int buttonPin = 7;
int old=2;
int sel=0;
char mystr[10]; //Initialized variable to store recieved data

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
  Braccio.begin();
  pinMode(buttonPin, INPUT);
}

void loop() {

  int novo;
  int re_but=0;

  novo=digitalRead(buttonPin);

  if((novo==1) and (novo!=old)){
    re_but=1;
  }
  
  if (re_but==1) {
    if(sel==0){
      sel=1; //separa por cor
    }
    else if(sel==1){
      sel=0; //separa por forma
    }
  }

  //posicao inicial -> Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  10);
  //primeira caixa das formas
  /*Braccio.ServoMovement(10,           180,  45, 65, 80,  86,  10);
  delay(2000);
  Braccio.ServoMovement(10,           180,  45, 65, 180,  86,  10);
  */
  //segunda caixa das formas
  /*Braccio.ServoMovement(10,           155,  45, 65, 80,  86,  10);
  delay(500);
  Braccio.ServoMovement(10,           155,  45, 65, 180,  86,  10);
  */

  //terceira caixa das formas
  /*Braccio.ServoMovement(10,           135,  45, 65, 80,  86,  10);
  delay(500);
  Braccio.ServoMovement(10,           135,  45, 65, 180,  86,  10);
  */

  //quarta caixa das formas
  /*
  Braccio.ServoMovement(10,           115,  45, 90, 50,  86,  10);
  delay(500);
  Braccio.ServoMovement(10,           115,  45, 90, 140,  86,  10); 
  */

  //primeira caixa das cores
  /*
   Braccio.ServoMovement(10,           0,  45, 80, 80,  86,  10);
  delay(500);
  Braccio.ServoMovement(10,           0,  45, 80, 155,  86,  10);
   */
  
  //segunda caixa das cores
  /*
   Braccio.ServoMovement(10,           20,  45, 80, 80,  86,  10);
  delay(500);
  Braccio.ServoMovement(10,           20,  45, 80, 155,  86,  10);
   */
  //terceira caixa das cores
  /*
   Braccio.ServoMovement(10,           42,  45, 80, 80,  86,  10);
  delay(500);
  Braccio.ServoMovement(10,           42,  45, 80, 155,  86,  10);
  delay(500);
   */
  Serial.readBytes(&mystr[0],1);
  Serial.println(mystr[0]);
  
  Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  10);
  delay(500);

  if(mystr[0]=='1'){
    Serial.readBytes(&mystr[1],1); 
    if(mystr[1]=='1'){
      //ESTRELA AMARELA
      Serial.println("Estrela amarela");  

      if(sel==0){
        //posicao forma estrela
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  50);
        delay(300);
        
        Braccio.ServoMovement(10,           180,  45, 80, 80,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           180,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           180,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           180,  45, 80, 80,  86,  10);
        
        
      }
      if(sel==1){
        //posicao cor amarela
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  50);
        delay(300);
        
        Braccio.ServoMovement(10,           42,  45, 80, 80,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           42,  45, 80, 150,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           42,  45, 80, 150,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           42,  45, 80, 80,  86,  10);
        
        
      }
      
    }
    else if(mystr[1]=='2'){
      //ESTRELA VERDE
      Serial.println("Estrela verde");

      if(sel==0){
        //posiçao forma estrela
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  50);
        delay(300);
        
        Braccio.ServoMovement(10,           180,  45, 80, 80,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           180,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           180,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           180,  45, 80, 80,  86,  10);
        
        
      }
      if(sel==1){
        //posicao cor verde
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  50);
        delay(300);
        
        Braccio.ServoMovement(10,           20,  45, 80, 80,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           20,  45, 80, 150,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           20,  45, 80, 150,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           20,  45, 80, 80,  86,  10);
        
        
      }
        
    }
    else if(mystr[1]=='3'){
      //ESTRELA VERMELHA
      Serial.println("Estrela vermelha");  

      if(sel==0){
        //posiçao forma estrela
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  50);
        delay(300);
        
        Braccio.ServoMovement(10,           180,  45, 80, 80,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           180,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           180,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           180,  45, 80, 80,  86,  10);
        
        
      }
      if(sel==1){
        //posicao cor vermelha
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  50);
        delay(300);
        
        Braccio.ServoMovement(10,           0,  45, 80, 80,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           0,  45, 80, 150,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           0,  45, 80, 150,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           0,  45, 80, 80,  86,  10);
        
        
      }
      
    }
  }
  else if(mystr[0]=='2'){
    Serial.readBytes(&mystr[1],1); 
    Serial.println(mystr[1]);
    if(mystr[1]=='1'){
      //CIRCULO AMARELO
      Serial.println("CIRCULO AMARELO"); 

      if(sel==0){
        //posiçao forma circulo
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  50);
        delay(300);
        
        Braccio.ServoMovement(10,           155,  45, 80, 80,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           155,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           155,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           155,  45, 80, 80,  86,  10);
        
        
      }
      if(sel==1){
        //posicao cor amarela
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  50);
        delay(300);
        
        Braccio.ServoMovement(10,           42,  45, 80, 80,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           42,  45, 80, 150,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           42,  45, 80, 150,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           42,  45, 80, 80,  86,  10);
        
        
      }
       
    }
    else if(mystr[1]=='2'){
      //CIRCULO VERDE
      Serial.println("CIRCULO VERDE"); 

      if(sel==0){
        //posiçao forma circulo
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  50);
        delay(300);
        
        Braccio.ServoMovement(10,           155,  45, 80, 80,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           155,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           155,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           155,  45, 80, 80,  86,  10);
        
        
      }
      if(sel==1){
        //posicao cor verde
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  50);
        delay(300);
        
        Braccio.ServoMovement(10,           20,  45, 80, 80,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           20,  45, 80, 150,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           20,  45, 80, 150,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           20,  45, 80, 80,  86,  10);
        
        
      }
       
    }
    else if(mystr[1]=='3'){
      //CIRCULO VERMELHO
      Serial.println("CIRCULO VERMELHO"); 
  
      if(sel==0){
        //posiçao forma circulo
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  50);
        delay(300);
        
        Braccio.ServoMovement(10,           155,  45, 80, 80,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           155,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           155,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           155,  45, 80, 80,  86,  10);
        
        
      }
      if(sel==1){
        //posicao cor vermelho
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  50);
        delay(300);
        
        Braccio.ServoMovement(10,           0,  45, 80, 80,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           0,  45, 80, 150,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           0,  45, 80, 150,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           0,  45, 80, 80,  86,  10);
        
        
      }
       
    }
  }
  else if(mystr[0]=='3'){
    Serial.readBytes(&mystr[1],1); 
    if(mystr[1]=='1'){
      //TRIANGULO AMARELO
      Serial.println("TRIANGULO AMARELO");  

      if(sel==0){
        //posiçao forma triangulo
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  55);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  55);
        delay(300);
        
        Braccio.ServoMovement(10,           135,  45, 80, 80,  86,  55);
        delay(300);
        Braccio.ServoMovement(10,           135,  45, 80, 155,  86,  55);
        delay(300);
        Braccio.ServoMovement(10,           135,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           135,  45, 80, 80,  86,  10);
        
        
      }
      if(sel==1){
        //posicao cor amarela
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  55);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  55);
        delay(300);
        
        Braccio.ServoMovement(10,           42,  45, 80, 80,  86,  55);
        delay(300);
        Braccio.ServoMovement(10,           42,  45, 80, 150,  86,  55);
        delay(300);
        Braccio.ServoMovement(10,           42,  45, 80, 150,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           42,  45, 80, 80,  86,  10);
        
        
      }
      
    }
    else if(mystr[1]=='2'){
      //TRIANGULO VERDE
      Serial.println("TRIANGULO VERDE"); 

      if(sel==0){
        //posiçao forma triangulo
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  55);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  55);
        delay(300);
        
        Braccio.ServoMovement(10,           135,  45, 80, 80,  86,  55);
        delay(300);
        Braccio.ServoMovement(10,           135,  45, 80, 155,  86,  55);
        delay(300);
        Braccio.ServoMovement(10,           135,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           135,  45, 80, 80,  86,  10);
        
        
      }
      if(sel==1){
        //posicao cor verde
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  55);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  55);
        delay(300);
        
        Braccio.ServoMovement(10,           20,  45, 80, 80,  86,  55);
        delay(300);
        Braccio.ServoMovement(10,           20,  45, 80, 150,  86,  55);
        delay(300);
        Braccio.ServoMovement(10,           20,  45, 80, 150,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           20,  45, 80, 80,  86,  10);
        
        
      }
       
    }
    else if(mystr[1]=='3'){
      //TRIANGULO VERMELHO
      Serial.println("TRIANGULO VERMELHO"); 

      if(sel==0){
        //posiçao forma triangulo
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  55);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  55);
        delay(300);
        
        Braccio.ServoMovement(10,           135,  45, 80, 80,  86,  55);
        delay(300);
        Braccio.ServoMovement(10,           135,  45, 80, 155,  86,  55);
        delay(300);
        Braccio.ServoMovement(10,           135,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           135,  45, 80, 80,  86,  10);
        
        
      }
      if(sel==1){
        //posicao cor vermelho
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  55);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  55);
        delay(300);
        
        Braccio.ServoMovement(10,           0,  45, 80, 80,  86,  55);
        delay(300);
        Braccio.ServoMovement(10,           0,  45, 80, 150,  86,  55);
        delay(300);
        Braccio.ServoMovement(10,           0,  45, 80, 150,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           0,  45, 80, 80,  86,  10);
        
        
      }
       
    }
  }
  else if(mystr[0]=='4'){
    Serial.readBytes(&mystr[1],1); 
    if(mystr[1]=='1'){
      //RETANGULO AMARELO
      Serial.println("RETANGULO AMARELO"); 

      if(sel==0){
        //posiçao forma retangulo
        Braccio.ServoMovement(10,           91,  45, 80, 158,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 158,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  50);
        delay(300);
        
        Braccio.ServoMovement(10,           115,  45, 90, 50,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           115,  45, 90, 140,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           115,  45, 90, 140,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           115,  45, 90, 50,  86,  10);
        
        
      }
      if(sel==1){
        //posicao cor amarela
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  50);
        delay(300);
        
        Braccio.ServoMovement(10,           42,  45, 80, 80,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           42,  45, 80, 150,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           42,  45, 80, 150,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           42,  45, 80, 80,  86,  10);
        
        
      }
       
    }
    else if(mystr[1]=='2'){
      //RETANGULO VERDE
      Serial.println("RETANGULO VERDE"); 

      if(sel==0){
        //posiçao forma retangulo
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  50);
        delay(300);
        
        Braccio.ServoMovement(10,           115,  45, 90, 50,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           115,  45, 90, 140,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           115,  45, 90, 140,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           115,  45, 90, 50,  86,  10);
        
        
      }
      if(sel==1){
        //posicao cor verde
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  50);
        delay(300);
        
        Braccio.ServoMovement(10,           20,  45, 80, 80,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           20,  45, 80, 150,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           20,  45, 80, 150,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           20,  45, 80, 80,  86,  10);
        
        
      }
       
    }
    else if(mystr[1]=='3'){
      //RETANGULO VERMELHO
      Serial.println("RETANGULO VERMELHO");  

      if(sel==0){
        //posiçao forma retangulo
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  50);
        delay(300);
        
        Braccio.ServoMovement(10,           115,  45, 90, 50,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           115,  45, 90, 140,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           115,  45, 90, 140,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           115,  45, 90, 50,  86,  10);
        
        
      }
      if(sel==1){
        //posicao cor vermelho
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 155,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           91,  45, 80, 80,  86,  50);
        delay(300);
        
        Braccio.ServoMovement(10,           0,  45, 80, 80,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           0,  45, 80, 150,  86,  50);
        delay(300);
        Braccio.ServoMovement(10,           0,  45, 80, 150,  86,  10);
        delay(300);
        Braccio.ServoMovement(10,           0,  45, 80, 80,  86,  10);
        
        
      }
      
    }
  }

  //Serial.readBytes(mystr,5); //Read the serial data and store in var
  //Serial.println(mystr); //Print data on Serial Monitor
  delay(1000);
  old=novo;
}
