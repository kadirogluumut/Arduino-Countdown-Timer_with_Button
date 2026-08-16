// ==========================================
// ARDUINO COUNTDOWN - START / STOP
// 7-Segment Display + Buzzer + LED + RGB + Button
// ==========================================

// 7-Segment Display pins
const int A = 2;
const int B = 3;
const int C = 4;
const int D = 5;
const int E = 6;
const int F = 7;
const int G = 8;
const int DP = 9;

// Red LED and buzzer
const int redLED = 10;
const int buzzer = 11;

// RGB LED - Common Cathode
const int rgbR = 12;
const int rgbG = A0;
const int rgbB = A1;

// Push button
const int buttonPin = 13;

// Program state
bool running = false;
int currentNumber = 9;


// ==========================================
// NOTES
// ==========================================

#define N_C4 262
#define N_D4 294
#define N_E4 330
#define N_F4 349
#define N_G4 392
#define N_A4 440
#define N_B4 494
#define N_C5 523
#define N_D5 587
#define N_E5 659
#define N_F5 698
#define N_G5 784


// ==========================================
// SETUP
// ==========================================

void setup() {

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DP, OUTPUT);

  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(rgbR, OUTPUT);
  pinMode(rgbG, OUTPUT);
  pinMode(rgbB, OUTPUT);

  // Use the Arduino's internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

  digitalWrite(DP, LOW);
  digitalWrite(redLED, LOW);

  rgbOff();
  noTone(buzzer);

  // Show 9 when the Arduino starts
  showNumber(9);
}


// ==========================================
// RGB LED FUNCTIONS
// ==========================================

void rgbOff() {
  digitalWrite(rgbR, LOW);
  digitalWrite(rgbG, LOW);
  digitalWrite(rgbB, LOW);
}

void rgbRed() {
  digitalWrite(rgbR, HIGH);
  digitalWrite(rgbG, LOW);
  digitalWrite(rgbB, LOW);
}

void rgbGreen() {
  digitalWrite(rgbR, LOW);
  digitalWrite(rgbG, HIGH);
  digitalWrite(rgbB, LOW);
}

void rgbBlue() {
  digitalWrite(rgbR, LOW);
  digitalWrite(rgbG, LOW);
  digitalWrite(rgbB, HIGH);
}

void rgbYellow() {
  digitalWrite(rgbR, HIGH);
  digitalWrite(rgbG, HIGH);
  digitalWrite(rgbB, LOW);
}


// ==========================================
// 7-SEGMENT DISPLAY
// ==========================================

void showNumber(int n) {

  // Turn off all segments first
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);

  switch (n) {

    // Number 0
    case 0:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      break;

    // Number 1
    case 1:
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      break;

    // Number 2
    case 2:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(G, HIGH);
      break;

    // Number 3
    case 3:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(G, HIGH);
      break;

    // Number 4
    case 4:
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;

    // Number 5
    case 5:
      digitalWrite(A, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;

    // Number 6
    case 6:
      digitalWrite(A, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;

    // Number 7
    case 7:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      break;

    // Number 8
    case 8:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;

    // Number 9
    case 9:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
  }
}


// ==========================================
// BUTTON CONTROL
// ==========================================

void checkButton() {

  // Check if the button is pressed
  if (digitalRead(buttonPin) == LOW) {

    delay(30);

    if (digitalRead(buttonPin) == LOW) {

      // Toggle between RUN and STOP
      running = !running;

      // Wait until the button is released
      while (digitalRead(buttonPin) == LOW) {
        // Waiting for button release
      }

      delay(30);
    }
  }
}


// ==========================================
// NON-BLOCKING WAIT WITH BUTTON CHECK
// ==========================================

bool waitWithButton(unsigned long duration) {

  unsigned long startTime = millis();

  while (millis() - startTime < duration) {

    // Check the button while waiting
    if (digitalRead(buttonPin) == LOW) {

      delay(30);

      if (digitalRead(buttonPin) == LOW) {

        // Toggle RUN / STOP
        running = !running;

        // Wait until the button is released
        while (digitalRead(buttonPin) == LOW) {
          // Waiting
        }

        delay(30);

        if (!running) {
          return false;
        }
      }
    }
  }

  return true;
}


// ==========================================
// COUNTDOWN BEEP
// ==========================================

void beep() {

  tone(buzzer, 1000);

  if (!waitWithButton(120)) {
    noTone(buzzer);
    return;
  }

  noTone(buzzer);
}


// ==========================================
// COUNTDOWN
// ==========================================

void countdown() {

  while (currentNumber >= 0) {

    // If stopped, wait for the button
    if (!running) {

      noTone(buzzer);
      rgbBlue();
      digitalWrite(redLED, LOW);

      checkButton();
      continue;
    }

    // Display the current number
    showNumber(currentNumber);

    // Turn on the red LED
    digitalWrite(redLED, HIGH);

    // Green RGB during countdown
    rgbGreen();

    // Play a short beep
    beep();

    if (!running) {
      continue;
    }

    // Wait before showing the next number
    if (!waitWithButton(880)) {
      continue;
    }

    currentNumber--;
  }

  // Countdown finished
  alarm();

  // Reset countdown
  currentNumber = 9;
}


// ==========================================
// ALARM
// ==========================================

void alarm() {

  for (int i = 0; i < 6; i++) {

    // Allow the user to stop the alarm
    if (!running) {
      noTone(buzzer);
      return;
    }

    // Red RGB + red LED
    rgbRed();
    digitalWrite(redLED, HIGH);

    // Alarm sound
    tone(buzzer, 1500);

    if (!waitWithButton(180)) {
      noTone(buzzer);
      return;
    }

    noTone(buzzer);

    rgbOff();

    if (!waitWithButton(100)) {
      return;
    }
  }
}


// ==========================================
// ORIGINAL DANCE MELODY
// ==========================================

int melody[] = {

  N_E4, N_E4, N_G4, N_A4,
  N_G4, N_E4, N_D4, N_E4,

  N_G4, N_A4, N_C5, N_A4,
  N_G4, N_E4, N_D4, N_E4,

  N_G4, N_G4, N_A4, N_C5
};

int noteDuration[] = {

  150, 150, 180, 180,
  150, 150, 180, 180,

  150, 150, 180, 180,
  150, 150, 180, 180,

  150, 150, 180, 300
};


// ==========================================
// PLAY MELODY
// ==========================================

void playMelody() {

  int totalNotes = sizeof(melody) / sizeof(melody[0]);

  digitalWrite(redLED, HIGH);

  for (int i = 0; i < totalNotes; i++) {

    // Stop the melody if the button is pressed
    if (!running) {
      noTone(buzzer);
      return;
    }

    // Change RGB colors
    if (i % 4 == 0) {
      rgbRed();
    }
    else if (i % 4 == 1) {
      rgbBlue();
    }
    else if (i % 4 == 2) {
      rgbGreen();
    }
    else {
      rgbYellow();
    }

    // Play the note
    tone(buzzer, melody[i]);

    if (!waitWithButton(noteDuration[i])) {
      noTone(buzzer);
      return;
    }

    noTone(buzzer);

    if (!waitWithButton(30)) {
      return;
    }
  }

  rgbOff();
  digitalWrite(redLED, LOW);
}


// ==========================================
// MAIN PROGRAM
// ==========================================

void loop() {

  // Check the button
  checkButton();

  if (running) {

    // Start or continue the countdown
    countdown();

  } 
  else {

    // Waiting mode
    showNumber(currentNumber);
    rgbBlue();
    digitalWrite(redLED, LOW);
    noTone(buzzer);
  }
}