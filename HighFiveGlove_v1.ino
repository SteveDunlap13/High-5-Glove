
#include <SimpleTimer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <CapTouch.h>

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

// CapTouch(sendPin, receivePin) - recieve pin is the sensor to touch
CapTouch touchPin = CapTouch(9, 10); 

long highFiveTotal = 0;
SimpleTimer sensorTimer;





static const uint8_t PROGMEM
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 };
static const uint8_t PROGMEM
  heart1_bmp[] =
  { B00000000,
    B01101100,
    B10010010,
    B10000010,
    B10000010,
    B01000100,
    B00101000,
    B00010000 };
static const uint8_t PROGMEM
  heart2_bmp[] =
  { B01010000,
    B11111000,
    B01110000,
    B00100000,
    B00001010,
    B00011111,
    B00001110,
    B00000100 };
static const uint8_t PROGMEM
  diamonds_bmp[] =
  { B01000010,
    B11100111,
    B01000010,
    B00011000,
    B00011000,
    B01000010,
    B11100111,
    B01000010 };
static const uint8_t PROGMEM
  tara_bmp[] =
  { B11111111,
    B11111111,
    B11011011,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000 };






void setup() {
  
  Serial.begin(9600);  
  matrix.begin(0x70);  // pass in the address
  matrix.setBrightness(0);
  
  displayShape(true);

  highFiveTotal = 0;
  
  sensorTimer.setInterval(500, readSensor);
}


void loop() {

  sensorTimer.run();
}



void displayShape(bool show) {

  if(show) {
    matrix.clear();

    if(highFiveTotal <= 20) {
      matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON); // 0-20
    }
    else if(highFiveTotal >20 && highFiveTotal <=50) {
      matrix.drawBitmap(0, 0, heart1_bmp, 8, 8, LED_ON); //20-50
    }
    else if(highFiveTotal >50 && highFiveTotal <=80) {
      matrix.drawBitmap(0, 0, heart2_bmp, 8, 8, LED_ON); // 50-80
    }
    else if(highFiveTotal >80 && highFiveTotal <=100) {
      matrix.drawBitmap(0, 0, diamonds_bmp, 8, 8, LED_ON); // 80-100
    }
    else {
      matrix.drawBitmap(0, 0, tara_bmp, 8, 8, LED_ON);  // > 100
    }
    
    matrix.writeDisplay();
  } else {
    matrix.clear();
  }
}

void readSensor() {
  
  long sensorValue =  touchPin.readTouch(15);    //  read the sensor

    Serial.print(".........................");
    Serial.println(sensorValue);

  if(sensorValue > 4000) {

    Serial.println(sensorValue);

    highFiveTotal++;
    displayHighFives();
  }
}

void displayHighFives() {

  displayShape(false);
  
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);

  if(highFiveTotal > 9) {

    for (int8_t x=0; x>=-11; x--) {
    
      matrix.clear();
      matrix.setCursor(x,0);
      matrix.print(highFiveTotal);
      matrix.writeDisplay();

      if(x > -8){
        delay(125);
      }
    }
    delay(100);
    
  } else {

    matrix.clear();
    matrix.setCursor(2,0);
    matrix.print(highFiveTotal);
    matrix.writeDisplay();
    delay(1000);
  }
  
  displayShape(true);
}

