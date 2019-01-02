#include <Encoder.h>

#define MINUS 5
#define RAPID 6
#define PLUS 7
#define ACT 16 
Encoder Enc(3, 2);
 
int states[17];

void button_minus() {
  int state = !digitalRead(MINUS);
  if(states[MINUS] != state) {
    states[MINUS] = state;
    Serial.print("Minus:");
    Serial.println(state);
  }
}

void button_rapid() {
  int state = !digitalRead(RAPID);
  if(states[RAPID] != state) {
    states[RAPID] = state;
    Serial.print("Rapid:");
    Serial.println(state);
  }
}

void button_plus() {
  int state = !digitalRead(PLUS);
  if(states[PLUS] != state) {
    states[PLUS] = state;
    Serial.print("Plus:");
    Serial.println(state);
  }
}

void button_act() {
  int state = !digitalRead(ACT);
  if(states[ACT] != state) {
    states[ACT] = state;
    Serial.print("Act:");
    Serial.println(state);
  }
}

void bcdswitch_left() {
  int pos;
  int state = 0;
  int pins[4] = {8, 9, 10, 11};
  for(int i = 0; i < 4; i++) {
    state |= (!digitalRead(pins[i]) << i);
  }
  switch (state) {
    case 0b0000 : pos = 1; break;
    case 0b0001 : pos = 2; break;
    case 0b0011 : pos = 3; break;
    case 0b0010 : pos = 4; break;
    case 0b0110 : pos = 5; break;
    case 0b0111 : pos = 6; break;
    case 0b0101 : pos = 7; break;
    case 0b0100 : pos = 8; break;
    case 0b1100 : pos = 9; break;
    case 0b1101 : pos = 10; break;
    case 0b1111 : pos = 11; break;
    case 0b1110 : pos = 12; break;
  }
  if(states[0] != pos) {
    states[0] = pos;
    Serial.print("Left:");
    Serial.println(pos);
  }
}

void bcdswitch_right() {
  int pos;
  int state = 0;
  int pins[4] = {12, 13, 14, 15};
  for(int i = 0; i < 4; i++) {
    state |= (!digitalRead(pins[i]) << i);
  }
  switch (state) {
    case 0b0000 : pos = 1; break;
    case 0b0001 : pos = 2; break;
    case 0b0011 : pos = 3; break;
    case 0b0010 : pos = 4; break;
    case 0b0110 : pos = 5; break;
    case 0b0111 : pos = 6; break;
    case 0b0101 : pos = 7; break;
    case 0b0100 : pos = 8; break;
    case 0b1100 : pos = 9; break;
    case 0b1101 : pos = 10; break;
    case 0b1111 : pos = 11; break;
    case 0b1110 : pos = 12; break;
  }
  if(states[1] != pos) {
    states[1] = pos;
    Serial.print("Right:");
    Serial.println(pos);
  }
}


long oldPosition  = -999;

void encoder() {
  long newPosition = Enc.read() / 4;
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.print("Encoder:");
    Serial.println(newPosition);
  }
}

void setup() {
  for (int i = 5; i <= 16; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  Serial.begin(115200);
}

void loop() {
  bcdswitch_left();
  bcdswitch_right();
  button_minus();
  button_rapid();
  button_plus();
  button_act();
  encoder();
}
