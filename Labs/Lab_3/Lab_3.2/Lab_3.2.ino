#define MY_DELAY 800

//These Teensy pins are PWM
int greenLED = 20;
int blueLED = 21;
int redLED = 23;

void setup() {
  Serial.begin(9600);

  pinMode(blueLED,  OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED,   OUTPUT);

  pinMode(A0, INPUT);
  randomSeed(analogRead(A0));
}

void loop() {
  // DEMO #2 - RANDOMLY SET EACH OF: R,G,B (PWM)
  analogWrite(redLED, random(256));
  analogWrite(greenLED, random(256));
  analogWrite(blueLED, random(256));
  delay(MY_DELAY);
  
} 
