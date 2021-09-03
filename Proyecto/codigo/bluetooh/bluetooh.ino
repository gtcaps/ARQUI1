String text;
int velocidad =  map(800, 0, 1023, 0, 255);

//Salidas
const int pin9 = 9;
const int pin8 = 8;
const int pin7 = 7;
const int pin6 = 6;
const int pin5 = 5;
const int pin4 = 4;
const int pin3 = 3;
const int pin2 = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(10);

  pinMode(pin9, OUTPUT);
  pinMode(pin8, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin2, OUTPUT);
}


void velocidadAlta() {
  velocidad = 1023;
  velocidad = map(velocidad, 0, 1023, 0, 255);
}

void velocidadBaja() {
  velocidad = 500;
  velocidad = map(velocidad, 0, 1023, 0, 255);
}

void moverAdelante () {
    analogWrite(pin9, velocidad);
    analogWrite(pin8, 0);
    analogWrite(pin7, velocidad);
    analogWrite(pin6, 0);
    analogWrite(pin5, velocidad);
    analogWrite(pin4, 0);
    analogWrite(pin3, velocidad);
    analogWrite(pin2, 0);
}

void moverAtras() {
    /*digitalWrite(pin9, LOW);
    digitalWrite(pin8, HIGH);
    digitalWrite(pin7, LOW);
    digitalWrite(pin6, HIGH);
    digitalWrite(pin5, LOW);
    digitalWrite(pin4, HIGH);
    digitalWrite(pin3, LOW);
    digitalWrite(pin2, HIGH);*/

    analogWrite(pin9, 0);
    analogWrite(pin8, velocidad);
    analogWrite(pin7, 0);
    analogWrite(pin6, velocidad);
    analogWrite(pin5, 0);
    analogWrite(pin4, velocidad);
    analogWrite(pin3, 0);
    analogWrite(pin2, velocidad);
}

void moverDerecha() {
    /*digitalWrite(pin9, LOW);
    digitalWrite(pin8, LOW);
    digitalWrite(pin7, HIGH);
    digitalWrite(pin6, LOW);
    digitalWrite(pin5, HIGH);
    digitalWrite(pin4, LOW);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin2, LOW);*/

    analogWrite(pin9, 0);
    analogWrite(pin8, 0);
    analogWrite(pin7, velocidad);
    analogWrite(pin6, 0);
    analogWrite(pin5, velocidad);
    analogWrite(pin4, 0);
    analogWrite(pin3, velocidad);
    analogWrite(pin2, 0);
}

void moverIzquierda() {
    /*digitalWrite(pin9, HIGH);
    digitalWrite(pin8, LOW);
    digitalWrite(pin7, LOW);
    digitalWrite(pin6, LOW);
    digitalWrite(pin5, HIGH);
    digitalWrite(pin4, LOW);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin2, LOW);*/

    analogWrite(pin9, velocidad);
    analogWrite(pin8, 0);
    analogWrite(pin7, 0);
    analogWrite(pin6, 0);
    analogWrite(pin5, velocidad);
    analogWrite(pin4, 0);
    analogWrite(pin3, velocidad);
    analogWrite(pin2, 0);
}

void detenerMovimiento(){
    /*digitalWrite(pin9, LOW);
    digitalWrite(pin8, LOW);
    digitalWrite(pin7, LOW);
    digitalWrite(pin6, LOW);
    digitalWrite(pin5, LOW);
    digitalWrite(pin4, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin2, LOW);*/

    analogWrite(pin9, 0);
    analogWrite(pin8, 0);
    analogWrite(pin7, 0);
    analogWrite(pin6, 0);
    analogWrite(pin5, 0);
    analogWrite(pin4, 0);
    analogWrite(pin3, 0);
    analogWrite(pin2, 0);
}

void loop() {
  
  // CUANDO SE RECIBE SENAL DEL MODULO BLUETOOTH
  if (Serial.available() > 0) {
    String str = Serial.readString();

    // VELOCIDAD ALTA
    if (str == "fast") {
        digitalWrite(13, HIGH);
        velocidadAlta();
    }

    // VELOCIDAD BAJA
    if (str == "slow") {
        digitalWrite(13, LOW);
        velocidadBaja();
    }

    // MOV ADELANTE
    if (str == "up") {
      moverAdelante();
    }

    // MOV ATRAS
    if (str == "down") {
      moverAtras();
    }

    // MOV DERECHA
    if (str == "right") {
      moverDerecha();
    }

    // MOV IZQUIERDA
    if (str == "left") {
      moverIzquierda();
    }

    if (str == "stop") {
      detenerMovimiento();
    }
  }

}
