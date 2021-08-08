
#define LED1 7
#define LED2 6
#define LED3 5
#define LED4 4
#define LED5 3
#define LED6 2
#define RIGHT 0
#define LEFT 1

int btnDirection = 8;


void setup() {
  // put your setup code here, to run once:
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  pinMode(LED6,OUTPUT);
  pinMode(btnDirection, INPUT);
  

}

void apagarLEDs(){
  for (int led = LED1; led >= LED6; led--){
    digitalWrite(led, LOW);
  }
  delay(300);
}

void encenderLR() {
  for (int led = LED1; led >= LED6; led--){
    digitalWrite(led, HIGH);
    delay(300);
  }

  apagarLEDs();
}

void encenderRL() {
  for (int led = LED6; led <= LED1; led++){
    digitalWrite(led, HIGH);
    delay(300);
  }

  apagarLEDs();
}



void loop() {
  // put your main code here, to run repeatedly:

  int direccion = digitalRead(btnDirection);

  if (direccion == RIGHT) {
    encenderRL();
  }

  if (direccion == LEFT) {
    encenderLR();
  }
    
}
