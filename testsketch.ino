#include <Wire.h>//for BNO055
#include <Mouse.h>
#include <Adafruit_Sensor.h>//for BNO055
#include <Adafruit_BNO055.h>//for BNO055
#include <utility/imumaths.h>//for BNO055

Adafruit_BNO055 bno = Adafruit_BNO055(55);//for BNO055

int selPin = 8;
int scrollupPin = 10;
int scrolldownPin = 16;
int mouseClickFlag = 0;

void setup()  {
  
  Serial.begin(115200);
  pinMode(selPin, INPUT_PULLUP);
  pinMode(scrollupPin, INPUT_PULLUP);
  pinMode(scrolldownPin, INPUT_PULLUP);
  delay(2000);
  if(!bno.begin())  {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  bno.setExtCrystalUse(true);
  Mouse.begin(); //Init mouse emulation

}

void loop() {
  
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER); 

  Serial.println(digitalRead(selPin));
  
  if ((digitalRead(selPin)==0) && (mouseClickFlag)) {
    mouseClickFlag = 0;
    Mouse.press(MOUSE_LEFT);  
    
  }
  else if ((digitalRead(selPin)==1) && (!mouseClickFlag)) {
    mouseClickFlag = 1;
    Mouse.release(MOUSE_LEFT);  // release the left button
  }
  if(!mouseClickFlag) {
    Mouse.move(0, euler.y()/15, 0); // move mouse on y axis
    Mouse.move(-euler.z()/15, 0, 0); // move mouse on x axis
  }
  
  if (digitalRead(scrollupPin)==0) {
    Mouse.move(0,0,1); 
    delay(50); 
  }  
  else if (digitalRead(scrolldownPin)==0) {
    Mouse.move(0,0,-1); 
    delay(50); 
  }

}
