#include <Arduino.h>

int LED = 13;
int FD[24] = {69,22,24,23,25,26,27,28,29,58,57,56,71,72,73,74,75,76,77,78,79,80,81,82};
int com = 2;
int th = 20;

void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  for(int i = 0; i < 24; i++){
    pinMode(FD[i],INPUT);
  }
  pinMode(com,OUTPUT);
  analogWrite(com,th);
}

void loop() {
  int Lval[24];
  for(int i = 0; i < 24; i++){
    Lval[i] = digitalRead(FD[i]);
  }

  for(int i = 0; i < 24; i++){
    Serial.print(Lval[i]);
    Serial.print(" ");
  }
  Serial.println();
}