int button1;
int button2;
int button3;
int button4;

void setup() {

   pinMode(13, INPUT_PULLUP);
   pinMode(12, INPUT_PULLUP);
   pinMode(11, INPUT_PULLUP);
   pinMode(10, INPUT_PULLUP);
   pinMode(2, OUTPUT);
   pinMode(3, OUTPUT);

}

void loop() {

  button1 = digitalRead(13);
  button2 = digitalRead(12);
  button3 = digitalRead(11);
  button4 = digitalRead(10);

  int arr[4] = {button1, button2, button3, button4};

  if (arr[0]==0 && arr[1]==1 && arr[2]==1 && arr[3]==1) {
     digitalWrite(2, HIGH);
     digitalWrite(3, LOW);
  }
  else if (arr[0]==1 && arr[1]==0 && arr[2]==1 && arr[3]==1) {
     digitalWrite(2, LOW);
     digitalWrite(3, HIGH);
  }
  else if (arr[0]==1 && arr[1]==1 && arr[2]==0 && arr[3]==1) {
     digitalWrite(2, HIGH);
     digitalWrite(3, HIGH);
  }
  else {
     digitalWrite(2, LOW);
     digitalWrite(3, LOW);  
  }

}
