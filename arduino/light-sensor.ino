/*------- Hardware configuration -------*/
int leds[4] = {5,4,3,2};

const int sensorPin = A6;
const byte debugPin = 13;        // pin that we put debug output on (set to 255 to disable)
                                 // (most Arduino's have a built in LED on pin 13...)
int minimum = 100;
int maximum = 900;
int sensor_span = maximum - minimum;

int num_leds = 4;
int led_span = 3;

/*-------------------------------------------*/
/* Initializization code (run once via call from Arduino framework) */
void setup() {
  // establish direction of pins we are using to drive LEDs 
  for(int i=0; i< num_leds ; i++){
    pinMode(leds[i], OUTPUT);
  }
  
  //Serial.begin(9600);
}

// http://stackoverflow.com/questions/1969240/mapping-a-range-of-values-to-another
/* Main routine (called repeated by from the Arduino framework) */

void loop() {
  
  float sensor_scaled = (sensorValue() - minimum) / (float) sensor_span ;
  // Serial.println( (int)(sensor_scaled * 100 ) );
  
  int level = (int) (sensor_scaled * 4) - 1;
  
  for( int i = 0 ; i < num_leds ; i++){
    if( i <= level ){
      digitalWrite(leds[i], HIGH);
    } else {
      digitalWrite(leds[i], LOW);
    } 
  }
  
  //Serial.println(level);
}  // end loop()

void flash_delay(int pin, int ms_delay){
  digitalWrite(pin, HIGH);
  delay(ms_delay);
  digitalWrite(pin, LOW);
}

int sensorValue(){
  //Serial.println(analogRead(sensorPin));
  return analogRead(sensorPin) + 50; 
}
