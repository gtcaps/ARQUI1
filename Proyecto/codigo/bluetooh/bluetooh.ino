String text;
int velocidad =  map(500, 0, 1023, 0, 255);
long duracion;
long distancia; // float distancia para obtener decimales
int echo=22;
int trig=23;

//Salidas
const int llanta1_der = 9;
const int llanta1_izq = 8;
const int llanta2_der = 7;
const int llanta2_izq = 6;
const int llanta3_der = 5;
const int llanta3_izq = 4;
const int llanta4_der = 3;
const int llanta4_izq = 2;

// LEDS
const int led_izquierdo = 12;
const int led_derecho = 11;
const int led_trasero = 10;

String tipoMovimiento;
String direccionMovimiento;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.setTimeout(10);

  pinMode(llanta1_der, OUTPUT);
  pinMode(llanta1_izq, OUTPUT);
  pinMode(llanta2_der, OUTPUT);
  pinMode(llanta2_izq, OUTPUT);
  pinMode(llanta3_der, OUTPUT);
  pinMode(llanta3_izq, OUTPUT);
  pinMode(llanta4_der, OUTPUT);
  pinMode(llanta4_izq, OUTPUT);

  pinMode(led_izquierdo, OUTPUT);
  pinMode(led_derecho, OUTPUT);
  pinMode(led_trasero, OUTPUT);

  pinMode(trig,OUTPUT); // emisor
  pinMode(echo,INPUT); // Receptor
}


void velocidadAlta() {
  velocidad = 1023;
  velocidad = map(velocidad, 0, 1023, 0, 255);

  if (direccionMovimiento == "up") {
    moverAdelante();
  }

  if (direccionMovimiento == "down") {
    moverAtras();
  }

  if (direccionMovimiento == "left") {
    moverIzquierda();
  }

  if (direccionMovimiento == "right") {
    moverDerecha();
  }
}

void velocidadBaja() {
  velocidad = 500;
  velocidad = map(velocidad, 0, 1023, 0, 255);

  if (direccionMovimiento == "up") {
    moverAdelante();
  }

  if (direccionMovimiento == "down") {
    moverAtras();
  }

  if (direccionMovimiento == "left") {
    moverIzquierda();
  }

  if (direccionMovimiento == "right") {
    moverDerecha();
  }
}

void moverAdelante () {
  analogWrite(llanta1_der, velocidad);
  analogWrite(llanta1_izq, 0);
  analogWrite(llanta2_der, velocidad);
  analogWrite(llanta2_izq, 0);
  analogWrite(llanta3_der, velocidad);
  analogWrite(llanta3_izq, 0);
  analogWrite(llanta4_der, velocidad);
  analogWrite(llanta4_izq, 0);

  digitalWrite(led_izquierdo, LOW);
  digitalWrite(led_derecho, LOW);
  digitalWrite(led_trasero, LOW);
}

void moverAtras() {
  analogWrite(llanta1_der, 0);
  analogWrite(llanta1_izq, velocidad);
  analogWrite(llanta2_der, 0);
  analogWrite(llanta2_izq, velocidad);
  analogWrite(llanta3_der, 0);
  analogWrite(llanta3_izq, velocidad);
  analogWrite(llanta4_der, 0);
  analogWrite(llanta4_izq, velocidad);

  digitalWrite(led_izquierdo, LOW);
  digitalWrite(led_derecho, LOW);
  digitalWrite(led_trasero, LOW);
}

void moverDerecha() {
  analogWrite(llanta1_der, 0);
  analogWrite(llanta1_izq, 0);
  analogWrite(llanta2_der, velocidad);
  analogWrite(llanta2_izq, 0);
  analogWrite(llanta3_der, velocidad);
  analogWrite(llanta3_izq, 0);
  analogWrite(llanta4_der, velocidad);
  analogWrite(llanta4_izq, 0);

  digitalWrite(led_izquierdo, LOW);
  digitalWrite(led_derecho, HIGH);
  digitalWrite(led_trasero, LOW);
}

void moverIzquierda() {
  analogWrite(llanta1_der, velocidad);
  analogWrite(llanta1_izq, 0);
  analogWrite(llanta2_der, 0);
  analogWrite(llanta2_izq, 0);
  analogWrite(llanta3_der, velocidad);
  analogWrite(llanta3_izq, 0);
  analogWrite(llanta4_der, velocidad);
  analogWrite(llanta4_izq, 0);

  digitalWrite(led_izquierdo, HIGH);
  digitalWrite(led_derecho, LOW);
  digitalWrite(led_trasero, LOW);
}

void detenerMovimiento() {
  analogWrite(llanta1_der, 0);
  analogWrite(llanta1_izq, 0);
  analogWrite(llanta2_der, 0);
  analogWrite(llanta2_izq, 0);
  analogWrite(llanta3_der, 0);
  analogWrite(llanta3_izq, 0);
  analogWrite(llanta4_der, 0);
  analogWrite(llanta4_izq, 0);
}

  void sensor(){
  //Para estabilizar nuestro módulo ultrasónico
  digitalWrite(trig,LOW);
  delayMicroseconds(4);
  //disparo de un pulso en el trigger de longitud 10us
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  //Lectura de la duración del pulso HIGH generado hasta recibir el Echo
  //pulseIn (high) espera a que el pin esté en HIGH, se inicia el tiempo, espera a que el pin pase a nivel LOW y para el cronómetro. 
  duracion=pulseIn(echo,HIGH);

  //Calculo distancia
  distancia=duracion/58.4;// (cm)
  Serial1.print("Distancia: ");
  Serial1.print(distancia);
  Serial1.println(" cm");
  delay(100);
}

void loop() {
  sensor();
  if(distancia <= 20){
    detenerMovimiento();
    digitalWrite(led_izquierdo, LOW);
    digitalWrite(led_derecho, LOW);
    digitalWrite(led_trasero, HIGH);

    Serial.write("El carro llego a la meta");
  }else{
    // CUANDO SE RECIBE SENAL DEL MODULO BLUETOOTH
    if (Serial.available() > 0) {
      tipoMovimiento = Serial.readString();
    }

    // VELOCIDAD ALTA
    if (tipoMovimiento == "fast") {
      digitalWrite(13, HIGH);
      velocidadAlta();
    }

    // VELOCIDAD BAJA
    if (tipoMovimiento == "slow") {
      digitalWrite(13, LOW);
      velocidadBaja();
    }

    // MOV ADELANTE
    if (tipoMovimiento == "up") {
      moverAdelante();
      direccionMovimiento = tipoMovimiento;
    }

    // MOV ATRAS
    if (tipoMovimiento == "down") {
      moverAtras();
      direccionMovimiento = tipoMovimiento;
    }

    // MOV DERECHA
    if (tipoMovimiento == "right") {
      moverDerecha();
      direccionMovimiento = tipoMovimiento;
    }

    // MOV IZQUIERDA
    if (tipoMovimiento == "left") {
      moverIzquierda();
      direccionMovimiento = tipoMovimiento;
    }

    if (tipoMovimiento == "stop") {
      detenerMovimiento();
    } 
  }
}
