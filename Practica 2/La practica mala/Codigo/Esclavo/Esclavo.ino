#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); //Conexiones(rs,enable, d4,d5,d6,d7)
#define DS 0x48

int motor1 = 7;
int motor2 = 6;

int tempC = 0; //Variable para guardar la temperatura
int direccion = 0x48; //Direccion de nuestro sensor

int activo;
int nivel = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);

  configDS();
  pantalla_inicio();
  respuesta();
  sensor();
}

//Codigo obtenido de https://simple-circuit.com/arduino-ds1621-digital-temperature-sensor/
void configDS(){
  Wire.begin();
  Wire.beginTransmission(DS);
  Wire.write(0xAC);
  Wire.write(0);
  Wire.beginTransmission(DS);
  Wire.write(0xEE);
  Wire.endTransmission();
}
//Codigo obtenido de https://simple-circuit.com/arduino-ds1621-digital-temperature-sensor/
int16_t getTemperatura() {
  Wire.beginTransmission(DS);
  Wire.write(0xAA);
  Wire.endTransmission(false);
  Wire.requestFrom(DS, 2);
  uint8_t t_msb = Wire.read();
  uint8_t t_lsb = Wire.read();
  int16_t raw_t = (int8_t)t_msb << 1 | t_lsb >> 7;
  raw_t = raw_t * 10/2;
  return raw_t;
}

void respuesta(){
  Wire.begin(1); //Acá decimos que el esclavo se va a identificar con el # 1
  Wire.onReceive(lectura); //Función que se ejecuta cuando el arduino maestro incie la comunicación
}

void lectura(){
  lcd.clear();
  activo= Wire.read();//leemos el valor que viene del maestro
  Serial.println(activo);
  lcd.setCursor(0,0); //nos posicionamos en la columna 1 y fila 0 
  lcd.print("Iniciando..."); //escribimos el mensaje 
}

void pantalla_inicio(){
  delay(1050);
  lcd.begin(16, 2);
  lcd.setCursor(0,0); //nos posicionamos en la columna 1 y fila 0 
  lcd.print("APAGADO"); //escribimos el mensaje  
}

void moverMotor(){
  if(nivel==1){
    analogWrite(motor1,0);
    analogWrite(motor2,0);
  }else if(nivel==2){
    analogWrite(motor1,255);
    analogWrite(motor2,0);
  }else if(nivel==3){
    analogWrite(motor1,255);
    analogWrite(motor2,255);
  }
}

void setNivel(int16_t temp){
  if(temp <= 180){
    nivel = 1;
  }else if(temp<=250){
    nivel = 2;
  }else{
    nivel = 3;
  }
}

void actualizarPantalla(int16_t temp){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TEMP : ");
  lcd.print(temp/10);
  lcd.setCursor(0,1);
  lcd.print("NIVEL : ");
  lcd.print(nivel);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(activo==1){
    delay(500);
    int16_t temp = getTemperatura();
    setNivel(temp);
    actualizarPantalla(temp);
    moverMotor();
  }
}
