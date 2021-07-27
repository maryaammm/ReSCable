/*
 * read 1 analoge sensor
 *    - smooth by taking average
 *    - Vout and resistor calculator
 *    - visualize result on LED strip
 *    - send result to serial port
 * reference: https://www.kobakant.at/DIY/?p=8637
 */
 
#include <FastLED.h>
#define LED_PIN 2
#define NUM_LEDS 60

CRGB leds[NUM_LEDS];

int val0;
static float oldAdcValue = 0;
int avg0;

int samplesize = 8; // avarage sample size

/*
 * voltage divider
 *      --> vin
 *      |
 *     --- 
 *     |||
 *     |||  rFix
 *     |||
 *     ---
 *      |
 *      ---> vout
 *      |
 *     --- 
 *     |||
 *     |||  r sensor
 *     |||
 *     ---
 *      |
 *     ---  GND
 *      -     
 */
 
float rFix = 300000.0; // value of fixed resistor in the circuit (ohm)
float vin = 5.0;

void setup() {
  // start serial communication
  Serial.begin(9600);

  // load avarage with initial value
  avg0 = analogRead(A0);

  // setup led strip
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();
  FastLED.show();
}

// smoothing function
// V -> U
static float smooth(float oldValue, float newValue, float alpha)
{
  return alpha * (newValue - oldValue) + oldValue;
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

void printFunc() {
  // print to serial
  // print max/min value to fix the plotter range
  //Serial.print(500);
  //Serial.print(" ");
  //Serial.print(0);
  //Serial.print("    ");
  // sensor value
  Serial.print(val0);
  Serial.print("    ");
  // smoothed value
  //Serial.print(val0_smooth);
  //Serial.print(" ");
  // print Vout
  //Serial.print("Vout: ");
  Serial.print(voutCal(val0));
  Serial.print("    ");
  // print sensor resistance value
  //Serial.print("sensor R: ");
  Serial.print(resCalculator(val0));
  Serial.print("    ");
  Serial.println();   // end of the message  
  }

void sendTo() {
  Serial.write(val0);
  }

void ledStrip() {
  // Turn lights from blue to magenta from right to left 
    for (int i=NUM_LEDS; i>0; i--){
      leds[i] = CRGB(4*i,0 , 255-4*i);
      FastLED.setBrightness(100-i);
      FastLED.show();
      delay(50);
    }
  }
  
void loop() {

  // read all the sensor pins
  val0 = analogRead(A0);

  //int tmp = (int) smooth(oldAdcValue, (float) val0, 0.6f);
  //oldAdcValue = val0;
  //val0 = tmp;

  // smooth with taking avarage - it worked better
  //avg0 = (avg0*(samplesize-1) + val0)/samplesize;
  //val0 = avg0;

  // print to serial
  printFunc();

  // send over serial port, e.g. processing
  //sendTo();

  // led strip control
  
  // loop delay, reduce the delay to read sensors more frequently
  delay(200);
}
