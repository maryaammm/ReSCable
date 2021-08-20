/*
 * gesture detection by duration measurement
 */

int avg = 0;
int resValue = 0;
int samplesize = 4;
float rFix = 10000.0;
float vin = 5.0;
float vout;

boolean tapFlag = false;
boolean pressFlag = false;
boolean stretchFlag = false;
boolean active = false;
boolean startFlag = true;

// set duration of each gesture 
//unsigned long tapD = 4294966490;
unsigned long pressD = 4294965684;
//unsigned long stretchD = 4294965684;

unsigned long tapD =     4294966500; //+- 300
unsigned long stretchD = 4294965000; //+- 1000

unsigned long startTime;
unsigned long duration;

// 
//float threshold = 4.79;
float threshold = 970;

void setup() {
  // No pins to setup, pins can still be used regularly, although it will affect readings
  Serial.begin(9600);
}

void loop() {
  
    resValue = dualAnalogRead(A0, A1, 3); //sample resistance

    // filter   
    avg = (avg*(samplesize-1) + resValue)/samplesize;
    resValue = avg;

    vout = voutCal(resValue);
    //Serial.println(resValue);
    // detect what is happening
    if (resValue < threshold && startFlag)
    {
      startTime = millis();
      startFlag = false;
      active = true; 
      
      }
    /*
     * tap Duration: 4294966490
     * stretch Duration: 4294965684

     */
    if (resValue > threshold && active)
    {
      duration = startTime - millis();
      if (duration >= tapD-300 && duration <= tapD+300)
      {
        //Serial.println("Tap");
        Serial.write(0);
        tapFlag = true;
      }
      else if (!tapFlag && duration >= stretchD-1000 && duration <= stretchD+1000)
      {
        //Serial.println("Stretch");
        Serial.write(1);
      }
      //Serial.print("Duration: ");
      //Serial.println(duration);
      duration = 0; 
      tapFlag = false;
      startFlag = true;
      active = false;  
    }
    
    //print to serial port
    //printTo();

    // send to serial port
    //sendTo();
     
    delay(100);
}

int dualAnalogRead(int pin0, int pin1, int number) 
{
  int res0 = 0;
  int res1 = 0;
  int resistance = 0;

  for (int i = 0; i < number; i++) {
    pinMode(pin0, OUTPUT);
    digitalWrite(pin0, LOW);
    pinMode(pin1, INPUT_PULLUP);
    res1 = analogRead(pin1);

    pinMode(pin1, OUTPUT);
    digitalWrite(pin1, LOW);
    pinMode(pin0, INPUT_PULLUP);
    res0 = analogRead(pin0);

    resistance = resistance + (res0 + res1) / 2;

  }
  return resistance / number;
}

void sendTo() {
    Serial.write((int)mapTo(resValue));
  }

void printTo() {
    Serial.print(5); 
    Serial.print("    ");
    Serial.print(0); 
    //Serial.print("    ");
    //Serial.print(resValue);
    Serial.print("    ");
    Serial.print(voutCal(resValue));
    //Serial.print(mapTo(resValue));
    Serial.print("    ");
    //Serial.print(resCalculator(resValue));
    Serial.println();
  }

// Vout calculator
float voutCal(float sensorVal)
{
  return sensorVal * (vin/1023.0);
}

// resistor calculator
float resCalculator(float sensorVal)
{
  float vout = voutCal(sensorVal);
  return rFix * (1/( vin/vout - 1));
}

float mapTo(float sensorVal)
{
  int sensorMin = 300;
  int sensorMax = 1100;
  int mapMin = 0;
  int mapMax = 225;
  // reverse and map to another range
  return map(sensorVal, sensorMin, sensorMax, mapMax, mapMin);
}
