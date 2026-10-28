// C++ code
//
const int led1 = 3;
const int led2 = 5;
const int led3 = 6;
const int led4 = 9;
//store time for comtrol non-blocking
unsigned long previous = 0;
const long interval = 20;

int fadeValue = 0;

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop()
{
  unsigned long current = millis();

  if(current - previous >= interval) {
    previous = current;

    int bright1 = fadeValue;
    int bright2;
    if (fadeValue < 128) {
      bright2 = fadeValue * 2;
    } else {
      bright2 = (fadeValue - 128) * 2;
    }
    int bright3 = 255 - fadeValue;
    int bright4 = 128 + (fadeValue / 2);

    analogWrite(led1, bright1);
    analogWrite(led2, bright2);
    analogWrite(led3, bright3);
    analogWrite(led4, bright4);

    fadeValue++;
    if (fadeValue > 255) {
      fadeValue = 0;
    }
  }
}


