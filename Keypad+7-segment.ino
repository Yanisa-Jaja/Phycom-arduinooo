// C++ code
// Keypad and 7-segment display example for Arduino
const int A = 10; 
const int B = 11;
const int C = 12;
const int D = 13;
const int E = A0;
const int F = A1;
const int G = A2;

const int row[4] = {9,8,7,6};
const int col[4] = {5,4,3,2};

void setup()
{
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(row[i], OUTPUT);
    digitalWrite(row[i], HIGH);

    pinMode(col[i], INPUT_PULLUP);
  }
}

void displayDigit(int a, int b, int c, int d, int e, int f, int g) {
  digitalWrite(A, a);
  digitalWrite(B, b);
  digitalWrite(C, c);
  digitalWrite(D, d);
  digitalWrite(E, e);
  digitalWrite(F, f);
  digitalWrite(G, g);
}

void loop()
{
  for (int r = 0; r < 4; r++) {
    digitalWrite(row[r], LOW);

    for (int c = 0; c < 4; c++) {
      if (digitalRead(col[c]) == LOW) {
        if (r == 0 && c == 0) {
          displayDigit(0, 1, 1, 0, 0, 0, 0);//1
        }
        if (r == 0 && c == 1) {
          displayDigit(1, 1, 0, 1, 1, 0, 1);//2
        }
        if (r == 0 && c == 2) {
          displayDigit(1, 1, 1, 1, 0, 0, 1);//3
        }
        if (r == 1 && c == 0) {
          displayDigit(0, 1, 1, 0, 0, 1, 1);//4
        }
        if (r == 1 && c == 1) {
          displayDigit(1, 0, 1, 1, 0, 1, 1);//5
        }
        if (r == 1 && c == 2) {
          displayDigit(1, 0, 1, 1, 1, 1, 1);//6
        }
        if (r == 2 && c == 0) {
          displayDigit(1, 1, 1, 0, 0, 0, 0);//7
        }
        if (r == 2 && c == 1) {
          displayDigit(1, 1, 1, 1, 1, 1, 1);//8
        }
        if (r == 2 && c == 2) {
          displayDigit(1, 1, 1, 1, 0, 1, 1);//9
        }
        if (r == 3 && c == 1) {
          displayDigit(1, 1, 1, 1, 1, 1, 0);//0
        }
        delay(200);
      }
    }
    digitalWrite(row[r], HIGH);
  }
}