void setup() {
  pinMode(10, OUTPUT);

}

void loop() {

  for (int i=0; i<=255; i++) {
     analogWrite(10, i);
     delay(50);
  }
  for (int j=0; j<=255; j++) {
     analogWrite(10, 255-j);
     delay(50);
  }

}
