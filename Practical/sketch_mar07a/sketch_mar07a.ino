/**
 ** Name: Yuliia Topalova
 ** Email: topa0005@algonquinlive.com
 ** Expected Grade: A+
 ** Known Issues: None
**/

#include <Bounce2.h>

Bounce bounce = Bounce();

int SER = 14; //data
int LATCH = 15; //RCLK
int CLOCK = 16; //SRCLK
int PBS = 17;//PBS

int buttonCounter = 0;
int number1;
int number2;
int roundNumber = 1;
int digits [10] = {B11000000, B11111001, B10100100, B10110000, B10011001, B10010010, B10000010, B11111000, B10000000, B10011000};
int stateCheck;

void setup() {
  Serial.begin(38400);
  
  bounce.attach(PBS, INPUT_PULLUP);
  bounce.interval(5);
  
  pinMode(SER, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(PBS, INPUT_PULLUP);
  digitalWrite(SER, LOW);
  digitalWrite(CLOCK, LOW);
  digitalWrite(LATCH, LOW);
  delay(1000);
}

void loop() {
  bounce.update();

  int randomNumber = random(0, 10);
  digitalWrite(LATCH, LOW);
  shiftOut(SER, CLOCK, MSBFIRST, digits[randomNumber]); //Set on each bit one at a time
  digitalWrite(LATCH, HIGH);
  delay(500);
  
  if ( bounce.rose()) {
    digitalWrite(LATCH, LOW);
    shiftOut(SER, CLOCK, MSBFIRST, digits[randomNumber]);
    digitalWrite(LATCH, HIGH);
    buttonCounter++;

    if (buttonCounter == 1) {
      number1 = randomNumber;

      Serial.print("Round #");
      Serial.print(roundNumber);
      Serial.println("...");
      Serial.print("PBS press #1 => ");
      Serial.println(number1);
      
    }
    else {
      number2 = randomNumber;
      Serial.print("PBS press #2 => ");
      Serial.println(number2);

      if (number1 == number2) {
        Serial.println("=> **MATCH**");
        Serial.println("");

        for (int n = 0; n < 7; n++) {
        digitalWrite(LATCH, LOW);
        shiftOut(SER, CLOCK, MSBFIRST, digits[number1]);
        digitalWrite(LATCH, HIGH);
        digitalWrite(LATCH, LOW);
        shiftOut(SER, CLOCK, MSBFIRST, B11111111);
        digitalWrite(LATCH, HIGH);
        }
      }
      else {
        Serial.println("=> NO Match... period.");
        Serial.println("");
        delay(500);
        digitalWrite(LATCH, LOW);
          for (int n = 0; n < 3; n++) {
          digitalWrite(LATCH, LOW);
          shiftOut(SER, CLOCK, MSBFIRST, B01111111);
          digitalWrite(LATCH, HIGH);
          digitalWrite(LATCH, LOW);
          shiftOut(SER, CLOCK, MSBFIRST, B11111111); 
          digitalWrite(LATCH, HIGH); 
        }     
      }
      roundNumber++;
      buttonCounter = 0;
    }
    delay(500);
  }
}
