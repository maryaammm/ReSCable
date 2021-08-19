/*
 * Change text and background color based on parameter read from serial
 */

import processing.serial.*;
Serial port;  // Create object from Serial class

int val;
int tapNum = 0;
int stretchNum = 0;
boolean newData = false;

void setup()
{
  size(600, 400); 
  // set background
  background(200);
  // set the serial communication
  String portName = Serial.list()[2]; //change the 0 to a 1 or 2 etc. to match your port
  port = new Serial(this, portName, 9600);
}

void draw()
{
  if ( port.available() > 0 ) 
  { // if data is available
    // read it and store it in val
    val = port.read();
    newData = true;
  }
  
  if(newData)
  {
    if(val == 0)
    {
      tapNum++;
      background(248, 234, 140); // yellow
      fill(50);
      
      textSize(96);
      textAlign(CENTER);
      text("TAP", 300, 200);
      
      textSize(48);
      textAlign(LEFT, TOP);
      text(tapNum, 500, 300);   
    }
    if(val == 1)
    {
      stretchNum++;
      background(164, 232, 224); // blue
      fill(50);
      
      textSize(96);
      textAlign(CENTER);
      text("STRETCH", 300, 200);
      
      textSize(48);
      textAlign(LEFT, TOP);
      text(stretchNum, 500, 300);
    }
  }
}
