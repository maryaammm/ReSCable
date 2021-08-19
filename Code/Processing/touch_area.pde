/* 
 * visualize touch area
 */

import processing.serial.*;

Serial port;  // Create object from Serial class

int areaLabel = 0;
int w = 150;
int h = 100;
int x = 40;
int y = 165;

float val;
float valMap;
float transparency;
int sliderWidth = 220;
// set the sensor range
// ToDo: read it as input from user as a calibration step
int sensorMin = 0;
int sensorMax = 225;
// no push -> 0, gentle push -> 1
// push -> 2, strong push -> 3
int pressLevel = 0;
int numLevel = 4;

String pressText;

void setup()
{
  size(680, 480);
  background(255); // Set background
  // set the serial communication
  String portName = Serial.list()[2]; //change the 0 to a 1 or 2 etc. to match your port
  port = new Serial(this, portName, 9600);
}

void draw()
{
  if ( port.available() > 0) 
  { // if data is available
    // read it and store it in area
    areaLabel = port.read();      

    // map to pressed area
    pressArea(areaLabel);
  }
  
  // area 1
  fill(210, 251, 164);
  strokeWeight(2);
  rect(x, y, w, h);
  textSize(14);
  fill(50);
  text("Area 1", x+10, y-10);
  // area 2
  fill(210, 251, 164);
  rect(x+w, y, w, h); 
  textSize(14);
  fill(50);
  text("Area 2", x+w+10, y-10);
  // area 3
  fill(210, 251, 164);
  rect(x+2*w, y, w, h);
  textSize(14);
  fill(50);
  text("Area 3", x+2*w+10, y-10);
  // area 4
  fill(210, 251, 164);
  rect(x+3*w, y, w, h);
  textSize(14);
  fill(50);
  text("Area 4", x+3*w+10, y-10);
  
  pressArea(2);
}

void pressArea(int label) 
{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
  if (label == 1)
  {
    fill(102, 210, 214); // cyan
    strokeWeight(4);
    rect(x, y, w, h);
  }
  if (label == 2)
  {
    fill(251, 199, 64); // gold
    strokeWeight(4);
    rect(x+w, y, w, h);
  }
  if (label == 3)
  {
    fill(189, 151, 203); // lilac
    strokeWeight(4);
    rect(x+2*w, y, w, h);
  }
  if (label == 4)
  {
    fill(229, 105, 151); // hot pink
    strokeWeight(4);
    rect(x+3*w, y, w, h);
  }
}

void setPressText(int level)
{
  if (level == 0)
    pressText = "No Push";
  else if (level == 1)
    pressText = "Gentle Push";
  else if (level == 2)
    pressText = "Push";
  else if (level == 3)
    pressText = "Strong Push";
}
