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

DHT dht11(DHTPIN11, DHTTYPE11);
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

const int ledPin =  13;
const int fanPin = 12;     

void setup() {
  Serial.begin(9600);
  dht11.begin();

  pinMode(ledPin, OUTPUT);
  pinMode(fanPin, OUTPUT);

  matrix.begin();

  // matrix.setCursor(2,2);    // start at top left, with one pixel of spacing
  // matrix.setTextSize(2);     // size 1 == 8 pixels high
  // matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  // matrix.setTextColor(matrix.Color333(1, 2, 2));
  // matrix.println("HI");
  // delay(1000);

  matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
  matrix.setCursor(2,2);    // start at top left, with one pixel of spacing
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); 
  matrix.setTextColor(matrix.Color333(1, 5, 5));
  matrix.println("hmdty:");
  delay(1000);

  int humDHT11 = dht11.readHumidity();
  if (isnan(humDHT11)) {
    matrix.setCursor(2, 12);    // start at top left, with one pixel of spacing
    matrix.setTextSize(1);     // size 1 == 8 pixels high
    matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
    matrix.setTextColor(matrix.Color333(7, 2, 2));
    matrix.println("NO");
    matrix.println("DATA");  
  }

  if ( humDHT11 < 15 ) {
    matrix.setCursor(9, 12);    // start at top left, with one pixel of spacing
    matrix.setTextSize(1);     // size 1 == 8 pixels high
    matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
    matrix.setTextColor(matrix.Color333(7, 2, 2));
    matrix.print(humDHT11);
    matrix.println("%");
    matrix.println("LOW!");  
  } else {
    matrix.setCursor(9, 12);    // start at top left, with one pixel of spacing
    matrix.setTextSize(1);     // size 1 == 8 pixels high
    matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
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
    matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
  }
};

void loop() {
  // float tempDHT11 = dht11.readTemperature();
  // float humDHT11 = dht11.readHumidity();
  // delay(500);

  // if (isnan(tempDHT11))
  // {
  //   Serial.println("Failed to read from DHT 11 sensor!");
  //   return;
  // }

  // if ( humDHT11 < 45 ) {
  //   digitalWrite(ledPin, HIGH);
  //   digitalWrite(fanPin, HIGH);
  //   Serial.print("DHT11 Temperature: ");
  //   Serial.print(tempDHT11);
  //   Serial.print(" \xC2\xB0");
  //   Serial.print("C | ");
  //   Serial.print("Humidity: ");
  //   Serial.print(humDHT11);
  //   Serial.println(" % - TOO LOW!");

  //   matrix.setCursor(2, 5);    // start at top left, with one pixel of spacing
  //   matrix.setTextSize(1);     // size 1 == 8 pixels high
  //   matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  //   matrix.setTextColor(matrix.Color333(7, 2, 2));
  //   matrix.println("%");
  //   matrix.println("OK");
  //   delay(3000);

  //   matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));


  // } else {
  //   digitalWrite(ledPin, LOW);
  //   digitalWrite(fanPin, LOW);
  //   Serial.print("DHT11 Temperature: ");
  //   Serial.print(tempDHT11);
  //   Serial.print(" \xC2\xB0");
  //   Serial.print("C | ");
  //   Serial.print("Humidity: ");
  //   Serial.print(humDHT11);
  //   Serial.println(" % - optimal");
  //   matrix.setCursor(2, 5);    // start at top left, with one pixel of spacing
  //   matrix.setTextSize(1);     // size 1 == 8 pixels high
  //   matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves

  //   matrix.setTextColor(matrix.Color333(7, 2, 2));
  //   matrix.println("%");
  //   matrix.println("LOW");
  
  //   delay(3000);
  //     matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));

  // }


  // for (int drop = 0; drop < 31; drop++) {
  //   matrix.fillRect(0, 0, 32, drop, matrix.Color333(0, 6, 6));
  //   //    delay(100);
  //   int randomVertical = random(0, 32);
  //   matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 3, 3));
  //   matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 2, 4));
  //   matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 0, 0));
  //   matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 1, 4));
  //   matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 7, 7));
  // }

  // // draw some text!
  // // matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
  // matrix.setCursor(2, 5);    // start at top left, with one pixel of spacing
  // matrix.setTextSize(1);     // size 1 == 8 pixels high
  // matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves

  // matrix.setTextColor(matrix.Color333(7, 2, 2));
  // matrix.println("WATER");
  // matrix.println("FAIL");
  // // matrix.println("cables");
  // delay(1000);
  // // matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));

  // // matrix.setCursor(2, 5);    // start at top left, with one pixel of spacing
  // // matrix.println("turn");
  // // matrix.println("on the");
  // // matrix.println("thing");
  // delay(1000);
}
