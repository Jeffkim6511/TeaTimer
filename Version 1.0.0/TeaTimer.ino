// --Dependencies--
#include "SR04.h"
#include "IRremote.h"
#include <LiquidCrystal.h>

// --Set-up--
#define TRIG_PIN 9
#define ECHO_PIN 10

// --Variables--
long dist;
int reciver = 2; 
bool power_on = false;
int counter = 0;
unsigned long previousMillis = 0;
bool counting = false;
bool pause = false;

SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
IRrecv irrecv(reciver);
LiquidCrystal lcd(7, 6, 5, 4, 3, 8);
uint32_t last_decodedRawData = 0;

// --Functions--
void translateIR() {
  if (irrecv.decodedIRData.flags) {
    irrecv.decodedIRData.decodedRawData = last_decodedRawData;
  }

  switch (irrecv.decodedIRData.decodedRawData) {
    case 0xBA45FF00: // POWER
      Serial.println("POWER");
      power_on = !power_on;
      pause = false;
      counting = false;
      break;

    case 0xB847FF00: // FUNC/STOP
      if (power_on) {
        Serial.println("RESET");
      previousMillis = millis();
      counter = 0;
      counting = false;
      pause = false;
      }
      break;

    case 0xBF40FF00: // PAUSE
    if (power_on) {
      Serial.println("PAUSE");
      pause = !pause;
      if (!pause) {
        previousMillis = millis();  // Resume timing cleanly
      }
      break;
    }
    // (Other IR cases can go here if needed...)

    default:
      break;
  }

  last_decodedRawData = irrecv.decodedIRData.decodedRawData;
}

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  lcd.begin(16, 2);
  lcd.clear();
  delay(1000);
}

void loop() {
  // Poll IR very frequently
  if (irrecv.decode()) {
    translateIR();
    irrecv.resume();
  }

  if (power_on) {
    dist = sr04.Distance();
    Serial.println(dist);

    lcd.setCursor(0, 0);
    lcd.print("Timer: ");
    lcd.print(pause ? "paused" : "      ");

    if (!pause) {
      if (!counting)  {
        if (dist < 5) {
          counting = true;
          previousMillis = millis();
          }
      } else {
        if (millis() - previousMillis >= 1000) {
        previousMillis += 1000;
        counter++;
      }
    }
    }

    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    int min = counter / 60;
    int sec = counter % 60;

    if (min > 0) {
      lcd.print(min);
      lcd.print("m ");
    }
    lcd.print(sec);
    lcd.print("s ");
  } else {
    lcd.clear();
    counter = 0;
    counting = false;
    pause = false;
  }

  // Very short delay to avoid flooding LCD or IR buffer
  delay(10);
}
