# Smart Tea Timer with Ultrasonic Sensor, LCD, and Buzzer

This Arduino project is a **smart tea timer** that automatically starts when water is poured into a cup. It uses an **ultrasonic sensor** to detect the motion of pouring, displays the elapsed time on an **LCD screen**, and plays a melodic **jingle every 10 seconds** to track your brewing progress. Ideal for steeping the perfect cup of tea!

---

## Components Required

| Component             | Quantity | Notes                          |
|-----------------------|----------|--------------------------------|
| Arduino Uno           | 1        | Or compatible board            |
| HC-SR04 Ultrasonic Sensor | 1    | Detects water being poured     |
| 16x2 LCD (HD44780)    | 1        | Displays timer                 |
| Passive Buzzer        | 1        | Plays a jingle                 |
| Push Button (Reset)   | 1        | Wired to digital pin 2         |
| Push Button (Pause)   | 1        | Wired to digital pin 13        |
| Resistors (10kΩ)      | 2        | Optional if using `INPUT_PULLUP` |
| Breadboard + Wires    | -        | For connections                |

---

## Pin Connections

| **Component**         | **Arduino Pin** |
|-----------------------|------------------|
| Ultrasonic TRIG       | D9               |
| Ultrasonic ECHO       | D10              |
| LCD RS                | D7               |
| LCD EN                | D6               |
| LCD D4                | D5               |
| LCD D5                | D4               |
| LCD D6                | D3               |
| LCD D7                | D8               |
| Reset Button          | D2               |
| Pause Button          | D13              |
| Passive Buzzer        | D12              |

---

## Controls

- **Start**: Pour water into your cup (sensor detects motion under 15 cm).
- **Pause**: Press the **Pause button** (D13) to stop/resume the timer.
- **Reset**: Press the **Reset button** (D2) to clear the timer.

---

## Timer Display

- The LCD shows the current status (`Paused`) and elapsed brew time in the format:
- Timer Paused
- Time: 1m 30s

## Jingle Feature

- Every **10 seconds**, a short **melody** plays on the buzzer to mark the passing of time.
- The jingle plays using **non-blocking** logic so the timer remains accurate.

---

## How It Works

1. The **ultrasonic sensor** detects an object (like a hand or stream of water) within **15 cm**.
2. Once detected, the timer **starts automatically**.
3. Time is tracked using `millis()` without blocking delays.
4. Every 10 seconds, a short **melody** plays using the `tone()` function.
5. The **Pause** and **Reset** buttons give you manual control over the timer.

---

Enjoy perfectly steeped tea every time! 🍃
