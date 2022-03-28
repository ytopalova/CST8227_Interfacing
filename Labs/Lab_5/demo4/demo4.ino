
const int dataPin = 14;  //data
const int latchPin = 15; // RCLK
const int clockPin = 16; //SRCLK

void setup() {
  
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  

}

void loop() {
  byte sevenSegmentDisplay[10] = {
  B00000011,  //0   common anode not used in this lab
  B10011111,  //1
  B00100101,  //2
  B00001101,  //3
  B10011001,  //4
  B01001001,  //5
  B11000001,  //6
  B00011111,  //7
  B00000001,  //8
  B00011001   //9
};

  byte randomNumber = sevenSegmentDisplay[random(0, 10)];
}
