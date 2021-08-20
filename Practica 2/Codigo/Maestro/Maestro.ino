#include <Wire.h>
#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);//direccion, columnas, filas


const String originalPassword = "202102";
const String enter = "*";
String currentPassword = "";

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
//  lcd.setCursor(0, 0);
//  lcd.print("CASA ACYE1");
//  lcd.setCursor(0, 1);
//  lcd.print("B-G02-S2");
//  delay(3000);
//  lcd.clear();
//  lcd.setCursor(0, 0);
//  lcd.print("INGRESE CONTRASEÑA");
//  lcd.setCursor(0, 1);
  pantallaLED();

  
}

void loop() {
  enterPassword();
}




void enterPassword() {
  char key = keypad.getKey();

  if(key) {
    if (String(key) == enter) {
      clearLCD();
      imprimirLCD("Verificando", 0, 0);
      delay(500);
      
      if (verificarPass()) {
        clearLCD();
        imprimirLCD("Bienvenido Perro", 0, 1);
      } else {
        reiniciarPass();
        clearLCD();
        imprimirLCD("Error al verificar", 0, 0);
        delay(500);
        pantallaLED();  
      }
    } else {
      
      currentPassword.concat(String(key));
      clearLCD();
      imprimirLCD("Ingresando:", 0, 0);
      imprimirLCD(currentPassword, 0, 1);
    }
  }
}

void imprimirLCD(String texto, int col, int fil) {
  lcd.setCursor(col,fil);
  lcd.print(texto);
}

void clearLCD() {
  lcd.clear();
}

boolean verificarPass() {
  return originalPassword.equalsIgnoreCase(currentPassword);
}

void reiniciarPass() {
  currentPassword = "";
}

void pantallaLED() {
  clearLCD();
  imprimirLCD("CASA ACYE1", 0, 0);
  imprimirLCD("B-G02-S2", 0, 1);
}
