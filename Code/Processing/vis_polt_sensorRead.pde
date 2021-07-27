/*
 * visualize resistive sensor reading
 * detect pressure level
 * draw real time graph
 * Credit: M-Toolbox - https://github.com/maryaammm
 */

import processing.serial.*;

Serial port;  // Create object from Serial class
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

// canvas size
int canvasX = 480;
int canvasY = 680;
// graph varaibles
int offset = 40;
int xPosG = offset; 
int yPosG = canvasY - offset;
int lengthG = 400;
int heightG = 300;
// variables to draw a continuous line
int currentXpose = offset;
int lastxPos = offset;
int lastheight = canvasY-offset;

void setup()
{
  size(480, 680);
  background(200); // Set background
  // set the serial communication
  String portName = Serial.list()[2]; //change the 0 to a 1 or 2 etc. to match your port
  port = new Serial(this, portName, 9600);
}

void draw()
{
  if ( port.available() > 0) 
  { // if data is available
    // read it and store it in val
    val = port.read();      
    // map the value
    valMap = map(val, sensorMin, sensorMax, 1, sliderWidth);
    println((int)valMap); //print it out in the console
    // map to a pressure level
    pressLevel = setPressLevel((int)valMap);
    drawGraph(val);
  }
  // 
  // text
  setPressText(pressLevel);
  // draw rect to clear the window
  // instead of calling background here
  fill(200);
  noStroke();
  rect(120, 100, sliderWidth+40, 170);
  // draw text box
  textSize(36);
  fill(50);
  text(pressText, 120, 150);
  
  // slider
  // background of slider
  stroke(0);
  strokeWeight(2);
  fill(255,255,255);
  rect(120, 200, sliderWidth, 40);
  // bar that changes based on data
  transparency = (int)valMap;
  fill(247,220,5,transparency+10);
  rect(120, 200, (int)valMap, 40);
  
  // plot
  // draw axis
  strokeWeight(2);
  stroke(0);
  line(xPosG, yPosG, xPosG, yPosG-heightG);
  line(xPosG, yPosG, xPosG+lengthG, yPosG);
  // draw text box
  textSize(12);
  fill(0);
  text("225", offset/3, yPosG-heightG);
  text("0", offset/2, yPosG);
  text("t", xPosG+lengthG, yPosG+offset/2);
}

int setPressLevel(int sensorVal) 
{  // these levels are set manually
   // highly depends on the sensor reading range
   // change intervals, offset, range, etc manually to get proper level detection
  int level = 0;
  int interval = (int) sliderWidth/numLevel;
  if (sensorVal > 0 && sensorVal <= interval-20)
    level = 0;
  else if (sensorVal > interval-20 && sensorVal <= 2*interval)
    level = 1;
  else if (sensorVal > 2*interval && sensorVal <= 3*interval-20)
    level = 2;
  else if (sensorVal > 3*interval-20 && sensorVal <= 4*interval)
    level = 3;
    
  return level;
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

void drawGraph(float sensorVal)
{

    // draw a line from Last inByte to the new one
    stroke(127,34,255);     //stroke color
    strokeWeight(1);        //stroke wider
    line(lastxPos, lastheight, currentXpose, canvasY-offset-sensorVal); 
    lastxPos = currentXpose;
    lastheight = int(canvasY-offset-sensorVal);

    // at the edge of the graph window, go back to the beginning:
    if (currentXpose >= offset+lengthG) {
      currentXpose = offset;
      lastxPos= offset;
      background(200);  //Clear the screen.
    } 
    else {
      // increment the horizontal position:
      currentXpose++;
    }
}
 
