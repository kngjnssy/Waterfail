#include <RGBmatrixPanel.h>
#include <DHT.h>

#define DHTPIN11 3
#define DHTTYPE11 DHT11

#define CLK 11
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

// need a button to set mosPin() HIGH when reading is low

DHT dht11(DHTPIN11, DHTTYPE11);
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

const int ledPin =  13;
const int fanPin = 12;    
const int mosPin = 7;    
const int buttonPin = 2;    

int buttonState = 0;         // variable for reading the pushbutton status


const int optimalHumidity = 40; 

void setup() {
  Serial.begin(9600);
  dht11.begin();

  pinMode(ledPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(mosPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  digitalWrite(mosPin, 0);
  digitalWrite(buttonPin, 1);

  matrix.begin();

  matrix.setCursor(2,2);    // start at top left, with one pixel of spacing
  matrix.setTextSize(2);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  matrix.setTextColor(matrix.Color333(1, 2, 2));
  matrix.println("HI");
  delay(2000);

  matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
  matrix.setCursor(2,2);
  matrix.setTextSize(1);     
  matrix.setTextWrap(false); 
  matrix.setTextColor(matrix.Color333(1, 5, 5));
  matrix.println("hmdty:");
  delay(1000);

  int humDHT11 = dht11.readHumidity();
  if (isnan(humDHT11)) {
    matrix.setCursor(9, 12);    
    matrix.setTextSize(1);    
    matrix.setTextWrap(false); 
    matrix.setTextColor(matrix.Color333(7, 2, 2));
    matrix.println("IDK!");  
  }
  if ( humDHT11 < optimalHumidity ) {
    // if it's TOO LOW
    digitalWrite(ledPin, HIGH);

    matrix.setCursor(9, 12);    // start at top left, with one pixel of spacing
    matrix.setTextSize(1);     // size 1 == 8 pixels high
    matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
    matrix.setTextColor(matrix.Color333(7, 2, 2));
    matrix.print(humDHT11);
    matrix.println("%");
    delay(800);

    matrix.println("LOW!");  
    delay(2000);
    matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
    matrix.setCursor(2, 2);    // start at top left, with one pixel of spacing
    matrix.setTextSize(1);     // size 1 == 8 pixels high
    matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
    matrix.setTextColor(matrix.Color333(7, 2, 2));
    matrix.println("turn");
    matrix.println(" it");
    matrix.println("on!");  
    delay(2000);
    for (int drop = 0; drop < 31; drop++) {
      matrix.fillRect(0, 0, 32, drop, matrix.Color333(0, 6, 6));
      // delay(100);
      int randomVertical = random(0, 32);
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 3, 3));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 2, 4));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 0, 0));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 1, 4));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 7, 7));
    }
    matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
    // delay(1000);
  } else {
    // if it's good level
    // digitalWrite(mosPin, 1);

    matrix.setCursor(9, 12);    
    matrix.setTextSize(1);     
    matrix.setTextWrap(false); 
    matrix.setTextColor(matrix.Color333(0, 3, 7));
    matrix.print(humDHT11);
    matrix.println("%");
    matrix.println("GOOD!"); 
    delay(2000);

    for (int drop = 0; drop < 31; drop++) {
      matrix.fillRect(0, 0, 32, drop, matrix.Color333(0, 6, 6));
      // delay(100);
      int randomVertical = random(0, 32);
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 3, 3));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 2, 4));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 0, 0));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 1, 4));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 7, 7));
    }
    // Ilde == screen is black
    matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
  }
}

int control = 0;

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH && mosPin == 0) {
    // Serial.println("BUTTON HIGH");
    matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
    matrix.setCursor(2, 2);    // start at top left, with one pixel of spacing
    matrix.setTextSize(1);     // size 1 == 8 pixels high
    matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
    matrix.setTextColor(matrix.Color333(7, 2, 2));
    matrix.println("turn");
    matrix.println(" it");
    matrix.println("on!");  
    delay(1000);
    matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
    // delay(1000);

  } 
  else if (buttonState == LOW){
    Serial.println("BUTTON LOW");
    digitalWrite(mosPin, 1);   
    digitalWrite(fanPin, HIGH);
  }

  int tempDHT11 = dht11.readTemperature();
  int humDHT11 = dht11.readHumidity();
  delay(500);

  // if (isnan(humDHT11))
  // {
  //   Serial.println("Failed to read from DHT 11 sensor!");
  //   return;
  // }

  if ( humDHT11 < optimalHumidity ) {
    control = 0;
    digitalWrite(ledPin, HIGH);

    matrix.setCursor(5, 2);
    matrix.setTextSize(1);
    matrix.setTextWrap(false);
    matrix.setTextColor(matrix.Color333(7, 2, 2));
    matrix.print(humDHT11);
    matrix.println("%");
    matrix.println("still");  
    matrix.println("LOW!");  
    delay(2000);

// ideally, when it's plugged in: 
    for (int drop = 0; drop < 31; drop++) {
      matrix.fillRect(0, 0, 32, drop, matrix.Color333(0, 6, 6));
      // delay(100);
      int randomVertical = random(0, 32);
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 3, 3));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 2, 4));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 0, 0));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 1, 4));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 7, 7));
    }
    // Ilde == screen is black
    matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
  } 
  // else if ( .... it's running....){

  // } 
    // else if ( .... it's getting low ....){

  // } 
  else {
    // it's ok == idle
    if (control < 3) {
      digitalWrite(mosPin, 0);    
      digitalWrite(ledPin, LOW);
      digitalWrite(fanPin, LOW);
      matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 1));
      matrix.setCursor(2, 2); 
      matrix.setTextSize(1); 
      matrix.setTextWrap(false);
      matrix.setTextColor(matrix.Color333(1, 7, 7));
      matrix.println("THX");
      matrix.println(" all");
      matrix.println("good");
      delay(1500);
      control++;
    }
    matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
  }
}
