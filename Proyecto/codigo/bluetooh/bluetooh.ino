String text;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(10);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    String str = Serial.readString();

    if (str == "fast") {
      digitalWrite(13, HIGH);
    }

    if (str == "slow") {
      digitalWrite(13, LOW);
    }
    
  }
  
}