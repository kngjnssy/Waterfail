#include <RGBmatrixPanel.h>
#include <DHT.h>

#define CLK 11
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

#define DHTPIN11 3
#define DHTTYPE11 DHT11

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
DHT dht11(DHTPIN11, DHTTYPE11);

const int fanPin = 12;
const int mosPin = 7;
const int buttonPin = 2;

int buttonState = 0;

const int optimalHumidity = 50;
const int bufferHumidity = optimalHumidity + 10;

void setup() {
  // Serial.begin(9600);
  dht11.begin();
  matrix.begin();

  pinMode(fanPin, OUTPUT);
  pinMode(mosPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  digitalWrite(mosPin, 0);
  digitalWrite(buttonPin, 1);

  matrix.setCursor(2, 2);   // start at top left, with one pixel of spacing
  matrix.setTextSize(2);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  matrix.setTextColor(matrix.Color333(1, 2, 2));
  matrix.println("HI");
  delay(2000);

  matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
  matrix.setCursor(2, 2);
  matrix.setTextSize(1);
  matrix.setTextWrap(false);
  matrix.setTextColor(matrix.Color333(1, 5, 5));
  matrix.println("hmdty:");
  delay(1000);

  int humDHT11 = dht11.readHumidity();

  if (isnan(humDHT11)) {
    matrix.setCursor(9, 9);
    matrix.setTextSize(1);
    matrix.setTextWrap(false);
    matrix.setTextColor(matrix.Color333(7, 2, 2));
    matrix.println("no");
    matrix.println("data");
  }

  if ( humDHT11 < optimalHumidity ) {
    // if it's TOO LOW
    matrix.setCursor(9, 12);    
    matrix.setTextSize(1);     
    matrix.setTextWrap(false); 
    matrix.setTextColor(matrix.Color333(7, 2, 2));
    matrix.print(humDHT11);
    matrix.println("%");
    delay(800);
    matrix.println(" LOW!");
    delay(2000);

    matrix.setCursor(2, 2);
    matrix.setTextSize(1);
    matrix.setTextWrap(false);
    matrix.setTextColor(matrix.Color333(7, 2, 2));
    matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
    delay(1000);
    matrix.println(" pls");
    matrix.println("turn");
    matrix.println("it on!");
    matrix.println("<");
    delay(2000);

    for (int drop = 0; drop < 31; drop++) {
      matrix.fillRect(0, 0, 32, drop, matrix.Color333(0, 6, 6));
      int randomVertical = random(0, 32);
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 3, 3));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 2, 4));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 0, 0));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 1, 4));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 7, 7));
    }
    matrix.setCursor(2, 6);
    matrix.setTextSize(1);
    matrix.setTextWrap(false);
    matrix.setTextColor(matrix.Color333(7, 2, 2));
    matrix.println("WATER");
    matrix.println(" FAIL");
    delay(1000);
    matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));

  } else {
    matrix.setCursor(9, 12);
    matrix.setTextSize(1);
    matrix.setTextWrap(false);
    matrix.setTextColor(matrix.Color333(0, 3, 7));
    matrix.print(humDHT11);
    matrix.println("%");
    delay(1000);
    matrix.println("GOOD!");
    delay(3000);
    // todo: create a function (loop) that handles case when humidity is between optimal and buffer at starting up 

    for (int drop = 0; drop < 31; drop++) {
      matrix.fillRect(0, 0, 32, drop, matrix.Color333(0, 6, 6));
      int randomVertical = random(0, 32);
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 3, 3));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 2, 4));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 0, 0));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 1, 4));
      matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 7, 7));
    }
    matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
  }
}

int control = 0;
int operating = 0;

void loop() {
  buttonState = digitalRead(buttonPin);

  // if button is pressed, humidifier and fan turns on..
  if (buttonState == LOW) {
    digitalWrite(mosPin, 1);
    digitalWrite(fanPin, HIGH);
    operating = 1;
  }

  int tempDHT11 = dht11.readTemperature();
  int humDHT11 = dht11.readHumidity();
  delay(500);

  // if humidity is below optimal 
  if ( humDHT11 < optimalHumidity ) {
    control = 0;

    // when it is not running
    if (operating == 0) {
        matrix.setCursor(10, 2);
        matrix.setTextSize(1);
        matrix.setTextWrap(false);
        matrix.setTextColor(matrix.Color333(7, 2, 2));
        matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
        matrix.print(humDHT11);
        matrix.println("%");
        matrix.fillRect(0, 10, 32, 32, matrix.Color333(0, 0, 0));
        delay(1000);
        matrix.println("turn");
        matrix.println("it on!");
        matrix.println("<");
        delay(1000);

    // when it is running
    } else if (operating == 1) {
        matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
        matrix.setCursor(5, 2);
        matrix.setTextSize(1);
        matrix.setTextWrap(false);
        matrix.setTextColor(matrix.Color333(7, 2, 2));
        matrix.print(humDHT11);
        matrix.println("%");
        delay(500);
        matrix.setTextColor(matrix.Color333(2, 1, 3));
        matrix.println("working");
        matrix.println("on it");
        delay(1000);

        for (int drop = 0; drop < 31; drop++) {     // run waterfail animation while on - TODO: make function
          matrix.fillRect(0, 0, 32, drop, matrix.Color333(0, 1, 1));
          int randomVertical = random(0, 32);
          matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 3, 3));
          matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 2, 4));
          matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 0, 0));
          matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 1, 4));
          matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 7, 7));
        }
        delay(1000);
    }
  }

  // if humidity is above optimal but below buffer > keep showing current humidity
  else if (bufferHumidity > humDHT11 && humDHT11 > optimalHumidity) {
    matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
    delay(3000);
    matrix.setCursor(5, 2);
    matrix.setTextSize(1);
    matrix.setTextWrap(false);
    matrix.setTextColor(matrix.Color333(0, 1, 1));
    matrix.print(humDHT11);
    matrix.println("%");
    matrix.print(tempDHT11);
    matrix.print("\370");
    matrix.print("C");
    delay(2000);
  }

  // humdidity is above buffer, aka very optimal
  else if (humDHT11 > bufferHumidity) {
    if (control < 1) {
      digitalWrite(mosPin, 0);
      operating = 0;

      matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 1));
      matrix.setCursor(5, 2);
      matrix.setTextSize(1);
      matrix.setTextWrap(false);
      matrix.setTextColor(matrix.Color333(1, 7, 7));
      matrix.print(humDHT11);
      matrix.println("%");

      delay(1000);

      matrix.setCursor(2, 15);
      matrix.println("GOOD!");
      delay(3000);

      for (int drop = 0; drop < 31; drop++) {
        matrix.fillRect(0, 0, 32, drop, matrix.Color333(0, 1, 1));
        int randomVertical = random(0, 32);
        matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 3, 3));
        matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 2, 4));
        matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 0, 0));
        matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 1, 4));
        matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 7, 7));
      }
      delay(2000);
      digitalWrite(fanPin, LOW);
      control++;

    // goodbye screen
      matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
      delay(1000);
      matrix.setCursor(2, 6);
      matrix.setTextSize(1);
      matrix.setTextWrap(false);
      matrix.setTextColor(matrix.Color333(0, 2, 5));
      matrix.println(" till");
      matrix.println("later!");
      delay(4000);
    }
    matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
    delay(8000);
    matrix.setCursor(5, 2);
    matrix.setTextSize(1);
    matrix.setTextWrap(false);
    matrix.setTextColor(matrix.Color333(0, 1, 1));
    matrix.print(humDHT11);
    matrix.println("%");
    matrix.print(tempDHT11);
    matrix.print("\370");
    matrix.print("C");
    delay(2000);
  }
}
