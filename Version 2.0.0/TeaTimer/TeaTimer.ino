#include "SR04.h"
#include <LiquidCrystal.h>
#include "pitches.h"

// --Set-up--
#define TRIG_PIN 9
#define ECHO_PIN 10

// --Variables--
long dist;
int buttonApin = 2;
int buttonBpin = 13;
bool power_on = false;
int counter = 0;
unsigned long previousMillis = 0;
bool counting = false;
bool pause = false;

bool lastPauseButtonState = HIGH;
bool lastResetButtonState = HIGH;
int lastJingleSecond = -1;

int melody[] = {
  NOTE_C6, NOTE_C6, NOTE_C6, NOTE_C6,
  NOTE_GS5, NOTE_AS5, NOTE_C6, 0, NOTE_AS5, NOTE_C6,
};

int noteDurations[] = {
  4, 4, 4, 12,
  12, 12, 4, 4, 4,
  12
};

int note_length = 20;

bool jinglePlaying = false;
int jingleNoteIndex = 0;
unsigned long jinglePreviousMillis = 0;
int jingleNoteDuration = 0;

SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
LiquidCrystal lcd(7, 6, 5, 4, 3, 8);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
  delay(100);
}

void loop() {
  // --Read Buttons--
  bool currentResetState = digitalRead(buttonApin);
  bool currentPauseState = digitalRead(buttonBpin);

  // --Handle Reset Button (A)--
  if (lastResetButtonState == HIGH && currentResetState == LOW) {
    Serial.println("Reset");
    lcd.clear();
    lcd.print("Reseting...");
    previousMillis = millis();
    counter = 0;
    counting = false;
    pause = false;
    jinglePlaying = false;
    delay(1000);
    lcd.clear();
  }
  lastResetButtonState = currentResetState;

  // --Handle Pause Button (B)--
  if (lastPauseButtonState == HIGH && currentPauseState == LOW) {
    Serial.println("Pause");
    pause = !pause;
    if (!pause) {
      previousMillis = millis();
    }
  }
  lastPauseButtonState = currentPauseState;

  // --Distance & Timing--
  if (!counting && !pause) {
    dist = sr04.Distance();
    Serial.println(dist);
  }

  lcd.setCursor(0, 0);
  lcd.print("Timer       ");
  lcd.setCursor(6, 0);
  lcd.print(pause ? "Paused" : "      ");

  if (!pause) {
    if (!counting) {
      if (dist < 15) {
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

  // --Display Time--
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

  // --Trigger Jingle Every 10 Seconds--
  if (counter % 10 == 0 && counter != 0 && counter != lastJingleSecond) {
    lastJingleSecond = counter;
    jinglePlaying = true;
    jingleNoteIndex = 0;
    jinglePreviousMillis = millis();
    jingleNoteDuration = 0;
  }

  // --Non-blocking Jingle Playback--
  if (jinglePlaying) {
    if (millis() - jinglePreviousMillis >= jingleNoteDuration) {
      if (jingleNoteIndex < sizeof(melody) / sizeof(int)) {
        int note = melody[jingleNoteIndex];
        int duration = noteDurations[jingleNoteIndex] * note_length;

        if (note > 0) {
          tone(12, note, duration);
        } else {
          noTone(12);  // Rest
        }

        jingleNoteDuration = duration * 1.3;
        jinglePreviousMillis = millis();
        jingleNoteIndex++;
      } else {
        noTone(12);
        jinglePlaying = false;
      }
    }
  }

  delay(50);
}
