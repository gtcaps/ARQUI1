String text;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(10);
}


void velocidadAlta() {
  
}

void velocidadBaja() {
  
}

void moverAdelante () {
  
}

void moverAtras() {
  
}

void moverDerecha() {
  
}

void moverIzquierda() {
  
}

void detenerMovimiento(){
  
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
