int SER = 14; //data
int LATCH = 15; //RCLK
int CLOCK = 16; //SRCLK

void setup() {
  pinMode(SER, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);

  digitalWrite(SER, 0);
  digitalWrite(CLOCK, 0);
  digitalWrite(LATCH, 0);

 // delay(1000);
}

void loop() {

int bitArray[] = {1, 2, 4, 8, 16, 32, 64, 128};

    for(int i = 0; i < 8; i++) {
      digitalWrite(LATCH, HIGH);
      //shift first 8 bits; ends up in the second SR
      shiftOut(SER, CLOCK, MSBFIRST, 0);
      //shift second 8-bits; ends up in the first SR
      shiftOut(SER, CLOCK, MSBFIRST, bitArray[i]);
      digitalWrite(LATCH, LOW);
      delay(150);
    }
}
