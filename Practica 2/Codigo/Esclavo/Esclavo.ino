#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); //Conexiones(rs,enable, d4,d5,d6,d7)

int activo;

void setup() {
  // put your setup code here, to run once:
  pantalla_inicio();
  respuesta();
}

void respuesta(){
  Wire.begin(1); //Acá decimos que el esclavo se va a identificar con el # 1
  Wire.onReceive(lectura); //Función que se ejecuta cuando el arduino maestro incie la comunicación
}

void lectura(){
  lcd.clear();
  activo= Wire.read();//leemos el valor que viene del maestro
  lcd.setCursor(0,0); //nos posicionamos en la columna 1 y fila 0 
  lcd.print(activo); //escribimos el mensaje 
}

void pantalla_inicio(){
  delay(1050);
  lcd.begin(16, 2);
  lcd.setCursor(0,0); //nos posicionamos en la columna 1 y fila 0 
  lcd.print("APAGADO"); //escribimos el mensaje  
}

void loop() {
  // put your main code here, to run repeatedly:

}
