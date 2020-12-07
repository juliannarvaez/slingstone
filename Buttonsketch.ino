
#include <Mouse.h>
// constants won't change. They're used here to set pin numbers:
int selPin = 5;     // the number of the pushbutton pin
int mouseClickFlag = 0;

void setup() {
  pinMode(selPin, INPUT);  // set button select pin as input
  digitalWrite(selPin, LOW);  // Pull button select pin high
  delay(1000);
  Mouse.begin(); //Init mouse emulation
}

void loop() {
  
  if ((digitalRead(selPin)) && (mouseClickFlag)) {
    mouseClickFlag = 0;
    Mouse.press(MOUSE_LEFT);  
  }
  
  else if ((digitalRead(selPin)==0) && (!mouseClickFlag)) {
    mouseClickFlag = 1;
    Mouse.release(MOUSE_LEFT);  // release the left button
  }

  Serial.println(mouseClickFlag);
  Serial.println(digitalRead(selPin));
  
}
