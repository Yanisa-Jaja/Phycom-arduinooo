const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

const byte rowPins[ROWS] = {2, 3, 4, 5};  // R1, R2, R3, R4
const byte colPins[COLS] = {6, 7, 8, 9};  // C1, C2, C3, C4

char lastKey = 0;

char scanKeypad() {
  for (byte r = 0; r < ROWS; r++) {
    digitalWrite(rowPins[r], LOW);

    for (byte c = 0; c < COLS; c++) {
      if (digitalRead(colPins[c]) == LOW) {
        digitalWrite(rowPins[r], HIGH);
        return keys[r][c];
      }
    }

    digitalWrite(rowPins[r], HIGH);
  }
  return 0;
}

void setup() {
  Serial.begin(9600);

  for (byte r = 0; r < ROWS; r++) {
    pinMode(rowPins[r], OUTPUT);
    digitalWrite(rowPins[r], HIGH);
  }
  for (byte c = 0; c < COLS; c++) {
    pinMode(colPins[c], INPUT_PULLUP);
  }

  Serial.println("Keypad ready. Press any key...");
}

void loop() {
  char key = scanKeypad();

  if (key != 0 && key != lastKey) {
    Serial.print("Key pressed: ");
    Serial.println(key);
    delay(30);
  }

  lastKey = key;
}