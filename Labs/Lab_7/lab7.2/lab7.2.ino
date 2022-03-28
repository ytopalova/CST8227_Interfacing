const int sensorPin = 16;    
const int ledPin = 9;        
const int buzzPin = 10;      

int sensVal = 0;         
int sensorMin = 1023;        
int sensorMax = 0;           


void setup() {
  pinMode(13, OUTPUT);   
  digitalWrite(13, LOW);

  while (millis() < 5000) {
    sensVal = analogRead(sensorPin);

    if (sensVal > sensorMax) {
      sensorMax = sensVal;
    }

    if (sensVal < sensorMin) {
      sensorMin = sensVal;
    }
  }

  digitalWrite(13, HIGH);
}

void loop() {
  sensVal = analogRead(sensorPin);
  sensVal = map(sensVal, sensorMin, sensorMax, 0, 255);
  sensVal = constrain(sensVal, 0, 255);

  analogWrite(ledPin, sensVal);

  Serial.println(touchRead(16));  
   
  tone(buzzPin, sensVal);
  
  delay(400);
}
