# 🍵 Tea Timer – IR & Ultrasonic Sensor Based Timer with LCD Display

This is a simple Arduino-based tea timer that uses an **ultrasonic sensor** to detect when a cup is placed in position and an **IR remote** to control power, pause, and reset functions. The elapsed time is displayed on a 16x2 LCD, making it perfect for timing tea brewing or similar tasks.

---

## 🧰 Features

- **Hands-free start:** Timer begins when a cup is placed close to the ultrasonic sensor.
- **IR Remote Control:**
  - `POWER` button toggles the device on/off.
  - `FUNC/STOP` resets the timer.
  - `PAUSE` toggles pause/resume.
- **LCD Display:**
  - Shows timer status and elapsed time in minutes and seconds.
- **Simple logic:** Easy to expand or customize for other timing needs.

---

## 🔌 Dependencies

Make sure the following libraries are installed in your Arduino IDE:

- `SR04` (Ultrasonic distance sensor)
- `IRremote` (IR receiver handling)
- `LiquidCrystal` (HD44780 LCD support)

---

## 🧪 Hardware Required

| Component              | Arduino Pin Connections         |
|------------------------|----------------------------------|
| **Ultrasonic Sensor**  | `TRIG` = 9, `ECHO` = 10          |
| **IR Receiver**        | Signal = 2                       |
| **16x2 LCD (HD44780)** | RS = 7, E = 6, D4 = 5, D5 = 4, D6 = 3, D7 = 8 |

---

## ⚙️ Setup & Operation

1. **Upload** the code to your Arduino board.
2. **Wire** the components as shown in the table above.
3. Use the **IR remote** for control:
   - Press `POWER` to toggle the timer on/off.
   - Place a cup (or hand) within 5 cm of the sensor to start timing.
   - Press `PAUSE` to pause or resume the timer.
   - Press `FUNC/STOP` to reset the timer.
   - Press `POWER` again to turn the system off and clear the LCD.

---

## 🧠 Notes

- The timer only counts while the object is detected and not paused.
- Timer uses a 5 cm threshold to detect a cup or hand.
- You can customize the IR remote codes to match your own remote.

---

## 🔧 Future Improvements

- Add a buzzer to notify when time is up.
- Add EEPROM support to save the last timer state.
- Allow setting countdown times via remote input.

---

Enjoy perfectly steeped tea every time! ☕
