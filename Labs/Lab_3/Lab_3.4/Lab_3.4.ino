#define MY_DELAY 800

int greenLED = 20;
int blueLED = 21;
int redLED = 23;
int pushButton = 10;
int counter = 0;
boolean state = LOW;

void setup() {
  Serial.begin(9600);

  pinMode(blueLED,  OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED,   OUTPUT);
  pinMode(pushButton, INPUT);

  pinMode(A0, INPUT);
  randomSeed(analogRead(A0));

  attachInterrupt(pushButton, pressedButton, LOW);
}

void randomLights() {
  analogWrite(redLED, random(256));
  analogWrite(greenLED, random(256));
  analogWrite(blueLED, random(256));
  delay(MY_DELAY);
}

void loop() {
  randomLights();
} 

void pressedButton(){
  if(digitalRead(pushButton)== LOW){
    if(counter == 10){
      counter = 0; 
    }
    counter++;
    delay(MY_DELAY);
  } 

  while(counter > 0 && counter < 10){
    if(digitalRead(pushButton) == LOW) {
      counter++;
      randomLights();
    }
  }
}
