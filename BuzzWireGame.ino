////////////////////////////////////
// Name: Hand Stability Game      //
// Written by: Isaac J. Newton   //
// Date: 30th March, 2021 19:06 //
/////////////////////////////////
int seg[7] = {2, 3, 4, 5, 6, 7, 8}; //seven segment display pins
byte segVal[10]; // array of seven segment display values
boolean reset = false; //reset flag variable
int err_count = 0; //stores the number of wire touches 
int button = 9, ledPin = 10, buzzerPin = 11, wire = 12; //pins for start/stop button, led, buzzer and wire
void setup() {
  segVal[0] = B11111100;
  segVal[1] = B01100000;
  segVal[2] = B11011010;
  segVal[3] = B11110010;
  segVal[4] = B01100110;
  segVal[5] = B10110110;
  segVal[6] = B10111110;
  segVal[7] = B11100100;
  segVal[8] = B11111110;
  segVal[9] = B11100110;
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(wire, INPUT_PULLUP);
  for(int i = 0; i < 7; i++)
  {
    pinMode(seg[i], OUTPUT);
  }
  dispNum(err_count); // display 0
}

void loop() {
  while(digitalRead(button)); //wait till the user press start
  buzz(); //make a beep
  reset = false; //flag reset false
  while(!reset) { 
    // game starts
    if(!digitalRead(wire) && err_count < 10)
  {
    warn(); //warn with a beep and a red flash when the user touches the wire
    err_count += 1; //increment the count
    dispNum(err_count); // update the value on the display
  }
  else if(err_count >= 10) // check if count has reached 10
  {
    break; //game ends
  }
  else if(!digitalRead(button)) //check and reset when the user wants to start the game again
  {
    err_count = 0;
    dispNum(err_count);
    reset = true; //clear all counts and start a new session
  }
  }
  while(!reset)
  {
    gameOver(); // when the game ends, run the display in a circular manner
    if(!digitalRead(button)) //press and hold start button to restart the game
    {
      break; // play the game again
    }
  }
  digitalWrite(ledPin, 0);
  digitalWrite(buzzerPin, 0);
  err_count = 0;
  dispNum(err_count);
}



 void dispNum(byte val)
 {
  for(int i = 0; i < 7; i++)
  {
    digitalWrite(seg[i], bitRead(segVal[val], i+1));
  }
 }
 void buzz()
 {
  digitalWrite(buzzerPin, 1);
  delay(200);
  digitalWrite(buzzerPin, 0);
 }
 void warn()
 {
  digitalWrite(buzzerPin, 1);
  digitalWrite(ledPin, 1);
  delay(200);
  digitalWrite(buzzerPin, 0);
  delay(100);
  digitalWrite(ledPin, 0);
 }
 void gameOver()
 {
  
  digitalWrite(ledPin, 1);
  digitalWrite(buzzerPin, 1);
  blank();
  for(int i = 0; i < 6; i++)
  {
    digitalWrite(seg[6-i], 1);
    delay(50);
    digitalWrite(seg[6-i], 0);
  }
 }
 void blank(){
  for(int j = 0; j < 7; j++)
  {
    digitalWrite(seg[j], 0);
  }
 }
