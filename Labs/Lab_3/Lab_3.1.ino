
#define MY_DELAY 800

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
  //DEMO #1 - CYCLE RGB (Digital)
  digitalWrite(redLED, HIGH);
  delay(MY_DELAY);
  digitalWrite(redLED, LOW);

  digitalWrite(greenLED, true);
  delay(MY_DELAY);
  digitalWrite(greenLED, false);

  digitalWrite(blueLED, 1);
  delay(MY_DELAY);
  digitalWrite(blueLED, 0);
} 
