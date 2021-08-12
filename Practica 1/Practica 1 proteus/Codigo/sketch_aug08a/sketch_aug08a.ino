// Importacion de librerias
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Configuracion para las matrices
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 2
#define CS_PIN 10
#define DATA_PIN 11
#define CLK_PIN 13
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Scrolling
uint8_t scrollSpeed = 100;
//uint8_t scrollSpeed = 0;
textEffect_t scrollEffect = PA_SCROLL_LEFT;
//textEffect_t scrollEffect = PA_PRINT;
textPosition_t scrollAlign = PA_LEFT;
//textPosition_t scrollAlign = PA_CENTER;
uint16_t scrollPause = 0;

// Texto para la matriz
//#define BUF_SIZE 75
char message[20] = "Arqui 1";

// Constantes
#define DERECHA    0
#define IZQUIERDA  1
#define MOVIMIENTO 0
#define PASO       1
#define POTENCIOMETRO A0

// Variables
int velocidad = 100;
int valorPot;

// Botones
int btnCambioForma = 7;
int btnCambioDireccion = 6;
#define btnCambioCadena A1

// Display
#define A 12
#define B 9
#define C 8
#define D 5
#define E 4
#define F 3
#define G 2

void setup() {
  // Serial
  Serial.begin(9600);
  Serial.println("Iniciando Practica 1...\n");
  Serial.println();
  Serial.setTimeout(1500);

  // PINES
  pinMode(btnCambioForma, INPUT);
  pinMode(btnCambioDireccion, INPUT);
  pinMode(POTENCIOMETRO, INPUT);
  pinMode(btnCambioCadena, INPUT);

  // Display 7 seg
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

  myDisplay.begin();
  myDisplay.setIntensity(5);
  myDisplay.displayClear();
  myDisplay.displayText(message, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect); 
}

void verificarVelocidad() {
  int slideSpeed = map(velocidad, 1023, 0, 400, 15);
  myDisplay.setSpeed(slideSpeed);
}


//verificar accion
void cambioDireccion(){
  if(digitalRead(btnCambioForma) == MOVIMIENTO){
    // Verificar el cambio de Direccion
      if (digitalRead(btnCambioDireccion) == DERECHA){
        myDisplay.setTextEffect(PA_SCROLL_RIGHT, PA_SCROLL_RIGHT);
        //myDisplay.write(message);
        //delay(1000);
        //velocidad = 400;
        //verificarVelocidad();
      }
  
      if (digitalRead(btnCambioDireccion) == IZQUIERDA) {
        //velocidad = 50;
        myDisplay.setTextEffect(PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        //verificarVelocidad();
      }
  }
  if(digitalRead(btnCambioForma) == PASO){
       // Verificar el cambio de Direccion
      if (digitalRead(btnCambioDireccion) == DERECHA){
        //myDisplay.setTextEffect(PA_NO_EFFECT, PA_NO_EFFECT);
        for(int i = 0; i < sizeof(message); i++){
           //myDisplay.displayClear();
           //myDisplay.displayText(message, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
           myDisplay.setTextEffect(PA_NO_EFFECT, PA_NO_EFFECT);
           myDisplay.setTextAlignment(PA_CENTER);
           myDisplay.write(message[i]);
           //verificarVelocidad();
           delay(100 + velocidad);
        }
        myDisplay.displayClear();
        myDisplay.displayText(message, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect); 
      }
      
      if (digitalRead(btnCambioDireccion) == IZQUIERDA) {
        //myDisplay.setTextEffect(PA_NO_EFFECT, PA_NO_EFFECT);
        for(int i = sizeof(message)-1; i >= 0; i--){
           //myDisplay.displayClear();
           //myDisplay.displayText(message, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
           myDisplay.setTextEffect(PA_NO_EFFECT, PA_NO_EFFECT);
           myDisplay.setTextAlignment(PA_CENTER);
           myDisplay.write(message[i]);
           delay(100 + velocidad);
        }
        myDisplay.displayClear();
        myDisplay.displayText(message, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect); 
      } 
  }
}

void encenderDisplay7(int a, int b, int c, int d, int e, int f, int g) {
  digitalWrite(A, a);
  digitalWrite(B, b);
  digitalWrite(C, c);
  digitalWrite(D, d);
  digitalWrite(E, e);
  digitalWrite(F, f);
  digitalWrite(G, g);
}

void verificarNivelVelocidad() {
  valorPot = analogRead(POTENCIOMETRO);

  // Nivel 1
  if (valorPot >= 0 && valorPot <=205){
    encenderDisplay7(LOW, HIGH, HIGH, LOW, LOW, LOW, LOW);
    velocidad = 400;
    verificarVelocidad();
  }

  // Nivel 2
  if (valorPot >= 206 && valorPot <= 411){
    encenderDisplay7(HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH);
    velocidad = 300;
    verificarVelocidad();
    
  }

  // Nivel 3
  if (valorPot >= 412 && valorPot <= 617){
    encenderDisplay7(HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH);
    velocidad = 200;
    verificarVelocidad();
  }

  // Nivel 4
  if (valorPot >= 618 && valorPot <= 823){
    encenderDisplay7(LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH);
    velocidad = 100;
    verificarVelocidad();
  }

  // Nivel 5
  if (valorPot >= 824 && valorPot <= 1023){
    encenderDisplay7(HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH);
    velocidad = 50;
    verificarVelocidad();
  }
}

void cambioCadena(){
  boolean cambio = false;
  if(digitalRead(btnCambioCadena)==1){
    Serial.println("Ingrese Nueva Cadena: ");
    
    cambio = true;
    int cadena[sizeof(message)];
    int count = 0;
    
    while(cambio){
      if (Serial.available()){
            int entrada = Serial.read();

            if(entrada == 13){
              cambio = false;
            }else{
              if(count<20){
                cadena[count] = entrada;
                count++;
              }
            }     
      }//Fin Lectura
    }//fin while(cambio)
    
    for(int i = 0; i < sizeof(message); i++){
      message[i] = 0;
    }
    
    for(int i = 0; i < sizeof(message); i++){
      message[i] = cadena[i];
    }
    
    Serial.print("Cadena Cambiada a: ");
    Serial.println(message);
    Serial.println();
    delay(500);
  }
}

void loop() {
  cambioCadena();
  
  cambioDireccion();
  verificarNivelVelocidad();

  if (myDisplay.displayAnimate()) {
    myDisplay.displayReset();
  }
}
