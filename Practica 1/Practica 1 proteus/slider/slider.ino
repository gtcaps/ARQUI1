#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

//Borrar empezando aqui
// Define hardware type, size, and output pins:
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1
#define CS_PIN 10
// Create a new instance of the MD_Parola class with hardware SPI connection:
//MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// Setup for software SPI:
 #define DATA_PIN 11
 #define CLK_PIN 13
 MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
const int buttonPin1 = 6; 
//borrar aqui

const int pinCS = 10;
const int MatricesX =2;
const int MatricesY = 1;
/* Para crear  un nuevo controlador necesitamos los 
    * Parámetros:
    * Pin CS
    * El número de pantallas horizontalmente
    * El número de pantallas verticalmente
     */
Max72xxPanel matriz = Max72xxPanel (pinCS,MatricesX,MatricesY);
String mensaje = "Laboratorio"; 
const int tiempo = 100; //milisegundos 
const int espacio = 1; //1 columna de espacio entre cada led 
const int ancho = 5 + espacio;  //El ancho de la fuente será de 5 píxeles, cada letra va a ocupar en total 5 columnas 

void setup() {
  matriz.setIntensity(7); //Usa un valor entre 0 y 15 para el brillo
  matriz.setPosition(0,0,0); //Para empezar a escribir posicionamos la matriz en la 0,0 * Define cómo se ordenan las pantallas. La primera pantalla (0)
  matriz.setRotation(0,3);
  matriz.setRotation(1,3); 
/* Definir si se rotan las pantallas y cómo. La primera pantalla
* (0) es el más cercano al Arduino. la rotación puede ser:
* 0: sin rotación
* 1:90 grados en el sentido de las agujas del reloj
* 2: 180 grados
* 3:90 grados en sentido antihorario
 */
}

void loop() {
  for (int i =0; i < ancho * mensaje.length()+ matriz.width() - 1- espacio ; i++){
    matriz.fillScreen(LOW); //Apagamos todos los LED. función dedicada para limpiar la pantalla.   
    //LETRA POR LETRA
    int letra = i/ ancho;
    int x = (matriz.width() -1) - i %ancho;
    int y = (matriz.height() -8) / 2; //sirve para centrar el texto verticalmente.
    while (x + ancho - espacio >= 0 && letra >= 0) {
      if(letra <  mensaje.length()){
        matriz.drawChar(x,y,mensaje[letra],HIGH, LOW, 1); //llenamos el búfer de mapa de bits con la imagen, de la letra 
      }
      letra--;
      x -= ancho;
    }
    matriz.write(); // Enviar mapa de bits para mostrar
  /*
    * Una vez que haya terminado de llenar el búfer de mapa de bits con su imagen,
    * enviarlo a la pantalla (s).
    */ 
    delay(tiempo); //espera 100 milisegundos
  }

}
