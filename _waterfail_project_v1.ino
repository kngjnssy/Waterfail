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

void setup() {
  Serial.begin(9600);
  dht11.begin();

  pinMode(ledPin, OUTPUT);

  matrix.begin();
  matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 1, 1));
  //  matrix.drawPixel(0, 0, matrix.Color333(7, 7, 7));
  //  matrix.fillRect(0, 0, 5, 5, matrix.Color333(7, 7, 7));

  delay(100);


};

//  matrix.drawLine(X0,  Y0, X1, Y1, matrix.Color333(0, 5, 5));


void loop() {

  delay(500);

  float tempDHT11 = dht11.readTemperature();
  float humDHT11 = dht11.readHumidity();

  // Check if readings have failed
  if (isnan(tempDHT11))
  {
    Serial.println("Failed to read from DHT 11 sensor!");
    return;
  }

  if ( humDHT11 < 45 ) {
    digitalWrite(ledPin, HIGH);
    Serial.print("DHT11 Temperature: ");
    Serial.print(tempDHT11);
    Serial.print(" \xC2\xB0");
    Serial.print("C | ");
    Serial.print("Humidity: ");
    Serial.print(humDHT11);
    Serial.println(" % - TOO LOW hey!");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.print("DHT11 Temperature: ");
    Serial.print(tempDHT11);
    Serial.print(" \xC2\xB0");
    Serial.print("C | ");
    Serial.print("Humidity: ");
    Serial.print(humDHT11);
    Serial.println(" % - optimal");
  }

  for (int drop = 0; drop < 31; drop++) {

    matrix.fillRect(0, 0, 32, drop, matrix.Color333(0, 1, 1));
    //    delay(100);
    int randomVertical = random(0, 32);
    matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 3, 3));
    matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 2, 4));
    matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 0, 0));
    matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 1, 4));
    matrix.drawLine(randomVertical, random(0, 32) + drop, randomVertical, random(0, 32), matrix.Color333(0, 0, 0));

  }


  // draw some text!
  //   matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));

  matrix.setCursor(2, 5);    // start at top left, with one pixel of spacing
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves

  matrix.setTextColor(matrix.Color333(7, 7, 7));
  matrix.println("WATER");
  matrix.println(" rrrr");
  delay(1500);
}
