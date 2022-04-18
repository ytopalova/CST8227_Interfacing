/**
 ** Name: Yuliia Topalova
 ** Email: topa0005@algonquinlive.com
 ** Expected Grade: A+
 ** Known Issues: None
**/

#include <Bounce2.h>

int SER = 14; //DATA PIN
int LATCH = 15; // RCLK
int CLOCK = 16; //SRLCK
int PBS = 17; //PBS

int numRound = 1;
int firstNumber = 0; 
int secondNumber = 0; 

int buttonPressCounter = 0; 
int buttonState = LOW;
int randomDigit = 0;

byte randomNumber = 0;
byte digits[10] = {
  B00000011, B10011111, B00100101, B00001101, B10011001, B01001001, B11000001, B00011111, B00000001, B00011001
};

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long currentMillis;
unsigned long randomMillis;

void setup() {
  
  pinMode(SER, OUTPUT); 
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(PBS, INPUT);

  Serial.begin(9600);
}

void randomNumberGenerator() {
  randomDigit = random(0, 10);
  randomNumber = digits[randomDigit];

  digitalWrite(LATCH, LOW);
  shiftOut(SER, CLOCK, LSBFIRST, randomNumber);
  digitalWrite(LATCH, HIGH);
}

void loop() {
  
  Serial.print("Round #");
  Serial.print(numRound);
  Serial.println("...");

  randomMillis = millis();
  do {
    buttonState = digitalRead(PBS);

    if ( (millis() - randomMillis) > 500) {
      randomNumberGenerator();
      randomMillis = millis();
    }
    if ( (millis() - lastDebounceTime) > debounceDelay) {
      if ( (buttonState == HIGH) ) {
        buttonPressCounter++;
        Serial.print("PBS Press #");
        Serial.print(buttonPressCounter);
        Serial.print(" ==> ");
        Serial.println(randomDigit);
        
        if (buttonPressCounter == 1) {
          firstNumber = randomDigit;
        } else if (buttonPressCounter == 2) {
          secondNumber = randomDigit;
        }
        delay(500);
        lastDebounceTime = millis();
      }
    }

    if (buttonPressCounter == 2) {
      
      if (firstNumber == secondNumber) {
        Serial.println("=> **MATCH** ");
        Serial.println(" ");
        
        currentMillis = millis();

        while (true) {
          digitalWrite(LATCH, LOW);
          shiftOut(SER, CLOCK, LSBFIRST, digits[firstNumber]);
          digitalWrite(LATCH, HIGH);
          delay(200);
          digitalWrite(LATCH, LOW);
          shiftOut(SER, CLOCK, LSBFIRST, B11111111);
          digitalWrite(LATCH, HIGH);
          delay(200);

          if ((millis() - currentMillis) > 2000) {
            break;
          }
        }
      } else {
        Serial.println("=> NO Match... period.");
        Serial.println(" ");
        
        currentMillis = millis();
        
        while (true) {
          digitalWrite(LATCH, LOW);
          shiftOut(SER, CLOCK, LSBFIRST, B11111110);
          digitalWrite(LATCH, HIGH);
          
          if ((millis() - currentMillis) > 2000) {
            break;
          }
        }
      }
    }
  } while (buttonPressCounter < 2);

  numRound++;
  firstNumber = 0;
  secondNumber = 0;
  buttonPressCounter = 0;
}
