#include <Wire.h>
#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);//direccion, columnas, filas

const byte ROWS = 4; //4 filas
const byte COLS = 3; //3 columnas 
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'} 
};

byte rowPins[ROWS] = {4, 3, 2, 1};
byte colPins[COLS] = {7, 6, 5};
char password[25];
int dir = 0;
bool bandera = false;

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


void setup() {
  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("CASA ACYE1");
  lcd.setCursor(0, 1);
  lcd.print("B-G02-S2");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("INGRESE CONTRASEÑA");
  lcd.setCursor(0, 1);
  
}

void loop() {
  
  char key = keypad.getKey();
  if(key){
    password[dir] = key;
    lcd.print(key);
    dir = dir + 1;

    if(key == '*'){
      if(password[0] == '2' && password[1] == '0' && password[2] == '2' && password[3] == '1' && password[4] == '0' && password[5] == '2'){
        lcd.setCursor(0, 0);
        lcd.print("BIENVENIDO A CASA"); 
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("INGRESE CONTRASEÑA");
        dir = 0;
      }else{
        lcd.setCursor(0, 0);
        lcd.print("ERROR EN CONTRASEÑA"); 
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("INGRESE CONTRASEÑA");
        dir = 0;
      }
      lcd.setCursor(0, 1);
    }
  }
  
}
