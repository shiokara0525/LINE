#include <Arduino.h>

int LED = 13;
int FD[24] = {69,22,24,23,25,26,27,28,29,11,12,14,56,57,58,59,60,61,62,63,64,65,66,67};
int com = 2;
int th = 200;

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 24; i++){
    pinMode(FD[i],INPUT);
  }
  pinMode(LED,OUTPUT);
  pinMode(com,OUTPUT);
  analogWrite(com,th);
}


void loop() {
  uint8_t L_bit[24];
  long L_val[24];
  L_bit[0] = PINK & _BV(7);
  L_bit[1] = PINA & _BV(0);
  L_bit[2] = PINA & _BV(1);
  L_bit[3] = PINA & _BV(2);
  L_bit[4] = PINA & _BV(3);
  L_bit[5] = PINA & _BV(4);
  L_bit[6] = PINA & _BV(5);
  L_bit[7] = PINA & _BV(6);
  L_bit[8] = PINA & _BV(7);
  L_bit[9] = PINJ & _BV(6);
  L_bit[10] = PINJ & _BV(5);
  L_bit[11] = PINJ & _BV(4);
  L_bit[12] = PINF & _BV(2);
  L_bit[13] = PINF & _BV(3);
  L_bit[14] = PINF & _BV(4);
  L_bit[15] = PINF & _BV(5);
  L_bit[16] = PINF & _BV(6);
  L_bit[17] = PINF & _BV(7);
  L_bit[18] = PINK & _BV(0);
  L_bit[19] = PINK & _BV(1);
  L_bit[20] = PINK & _BV(2);
  L_bit[21] = PINK & _BV(3);
  L_bit[22] = PINK & _BV(4);
  L_bit[23] = PINK & _BV(5);

  for(int i = 0; i < 24; i++){
    if(L_bit[i] != 0){
      L_val[i] = 1;
    }
    else{
      L_val[i] = 0;
    }
  }

  for(int i = 0; i < 24; i++){
    Serial.print(L_val[i]);
    Serial.print(" ");
  }
  Serial.println();
}