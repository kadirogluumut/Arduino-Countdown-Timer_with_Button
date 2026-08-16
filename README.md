# Arduino Countdown Timer 🚀

An interactive Arduino countdown timer built with a 7-segment display, buzzer, RGB LED, red LED, and push button.

The project counts down from 9 to 0 and provides visual and audio feedback. 
The push button works as a START / STOP control.

## ✨ Features

- 🔢 7-segment display countdown: 9 → 0
- 🔘 START / STOP push button
- 🔊 Buzzer countdown sound
- 🚨 Alarm when the countdown reaches 0
- 🔴 Red LED indicator
- 🌈 RGB LED color effects
- 🎵 Original electronic dance melody
- ⏸️ Pause and resume from the current number
- 🤖 Arduino UNO based project

## 🧰 Components

- Arduino UNO
- 1 × Common Cathode 7-Segment Display
- 1 × Push Button
- 1 × Buzzer
- 1 × Red LED
- 1 × RGB LED
- 3 × 220Ω resistors for RGB LED
- 1 × 220Ω resistor for Red LED
- Breadboard
- Jumper wires

## 🔌 Pin Connections

### 7-Segment Display

| Segment | Arduino Pin |
|--------|-------------|
| A | D2 |
| B | D3 |
| C | D4 |
| D | D5 |
| E | D6 |
| F | D7 |
| G | D8 |
| DP | D9 |

### Other Components

| Component | Arduino Pin |
|----------|-------------|
| Red LED | D10 |
| Buzzer | D11 |
| RGB Red | D12 |
| RGB Green | A0 |
| RGB Blue | A1 |
| Push Button | D13 |

The push button is connected between **D13 and GND**.

The button uses Arduino's internal pull-up resistor.

## 🎮 How It Works

When the Arduino starts, the display shows **9**.

Press the button once:

**9 → 8 → 7 → 6 → 5 → 4 → 3 → 2 → 1 → 0**

During the countdown:

- The RGB LED shows green.
- The red LED is turned on.
- The buzzer produces a short beep for each number.

When the countdown reaches **0**:

- 🚨 The buzzer produces an alarm.
- 🔴 The red LED stays on.
- 🌈 The RGB LED changes colors.
- 🎵 An original electronic dance melody plays.

### Button Control

**Press once:** Start ▶️

**Press again:** Stop ⏸️

**Press again:** Resume ▶️

The countdown continues from the number where it was stopped.

## 💻 Programming

The project is programmed using the Arduino IDE.

No external libraries are required.

## 📸 Project

Arduino UNO + 7-Segment Display + RGB LED + Buzzer + Push Button

## 🚀 Future Improvements

Possible upgrades:

- Add a 2-digit or 4-digit display
- Add adjustable countdown time
- Add an LCD or OLED display
- Add a potentiometer for speed control
- Add a second button for RESET
- Add a motion sensor
- Create a custom enclosure
- Control the timer using Bluetooth

## 🎓 Educational Use

This project is suitable for learning:

- Arduino programming
- Digital output
- LEDs and RGB LEDs
- 7-segment displays
- Push buttons
- Buzzer control
- Variables and loops
- Functions
- Conditional statements
- Basic embedded systems

## 📜 License

This project is open source and available for educational and personal use.

---

### Dream it. Code it. Build the future. 🚀
