#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); //Conexiones(rs,enable, d4,d5,d6,d7)

int tempC = 0; //Variable para guardar la temperatura
int direccion = 0x48; //Direccion de nuestro sensor

int activo;

void setup() {
  // put your setup code here, to run once:
  pantalla_inicio();
  respuesta();
  sensor();
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

void sensor(){
  Serial.begin(9660);
  Wire.begin(1);
  Wire.beginTransmission(direccion); //empezamos la transmision con el sensor
  Wire.write(0xAC); //configuracion del sensor
  Wire.write(0x02);
  Wire.beginTransmission(direccion);
  Wire.write(0xEE);
  Wire.endTransmission();//detenemos la transmision del sensor
}

void mostrar(){
  Wire.beginTransmission(direccion); //empezamos la transmision con el sensor
  Wire.write(0xAA);
  Wire.endTransmission();
  Wire.requestFrom(direccion, 1);//recibimos un byte de nuestro sensor
  tempC = Wire.read();//guardamos la temperatura
  lcd.setCursor(0, 0);
  lcd.print("la temperatura es de: ");
  lcd.setCursor(0, 1);
  lcd.print(tempC);
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  mostrar();
}
