#include <Arduino.h>

#define Long 5


int LED = 13;
int LED_L = 5;
int FD[24] = {69,22,24,23,25,26,27,28,29,11,12,14,56,57,58,59,60,61,62,63,64,65,66,67};
int com = 2;
int th = 5;  //閾値
float dis_X;
float dis_Y;
uint8_t num;
byte send[6];
uint8_t line_sub = 0;
byte line_byte[4];
int LINE_on;
double ele_X[27]; //ラインセンサのX座標
double ele_Y[27]; //ラインセンサのY座標
void getLine();

void setup() {
  Serial.begin(9600);
  Serial2.begin(57600);
  pinMode(LED_L,OUTPUT);
  for(int i = 0; i < 24; i++){
    ele_Y[i] = sin(radians(15 * i));
    ele_X[i] = cos(radians(15 * i));
    pinMode(FD[i],INPUT);
  }
  pinMode(LED,OUTPUT);
  pinMode(com,OUTPUT);
  analogWrite(com,th);
  digitalWrite(LED_L,HIGH);
}


void loop() {
  digitalWrite(LED_L,HIGH);
  getLine();
  digitalWrite(LED_L,LOW);

  // Serial.print(" | ");
  // Serial.print(vec[0]);
  // Serial.print(" ");
  // Serial.print(vec[1]);
  // Serial.print(" ang : ");
  // Serial.print(degrees(atan2(vec[1],vec[0])));
  // Serial.println();

  send[0] = 38;
  send[1] = line_byte[0];
  send[2] = line_byte[1];
  send[3] = line_byte[2];
  send[4] = line_byte[3];
  send[5] = 37;
  if(num != 0){
    digitalWrite(LED,HIGH);
  }
  else{
    digitalWrite(LED,LOW);
  }

  Serial2.write(send,6);
}


void getLine(){
  byte line_byte_[4] = {0,0,0,0};
  uint8_t hoge[27];
  num = 0;

  int data_on[27];

  uint8_t L_bit[27];
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
  L_bit[24] = PINF & _BV(0);
  L_bit[25] = PINJ & _BV(3);
  L_bit[26] = PINK & _BV(6);

  for(int i = 0; i < 27; i++){
    if(L_bit[i] != 0){
      data_on[i] = 1;
      if(i < 24){
        num++;
      }
    }
    else{
      data_on[i] = 0;
    }
    if(Serial){
      Serial.print(data_on[i]);
      Serial.print(" ");
    }
  }

  line_byte_[0] = data_on[0] | data_on[1] << 1 | data_on[2] << 2 |data_on[3] << 3 | data_on[4] << 4 |data_on[5] << 5 |data_on[6] << 6 | data_on[7] << 7;
  line_byte_[1] = data_on[8] | data_on[9] << 1 | data_on[10] << 2 | data_on[11] << 3 | data_on[12] << 4 | data_on[13] << 5 | data_on[14] << 6 | data_on[15] << 7;
  line_byte_[2] = data_on[16] | data_on[17] << 1 | data_on[18] << 2 |data_on[19] << 3 | data_on[20] << 4 |data_on[21] << 5 |data_on[22] << 6 | data_on[23] << 7;
  line_byte_[3] = data_on[24] | data_on[25] << 1 | data_on[26] << 2 | 0b00000000;

  // Serial.print(" 左 : ");
  // Serial.print(data_on[24]);
  // Serial.print(" 右 : ");
  // Serial.print(data_on[25]);
  // Serial.print(" 後ろ : ");
  // Serial.print(data_on[26]);
  line_byte[0] = line_byte_[0];
  line_byte[1] = line_byte_[1];
  line_byte[2] = line_byte_[2];
  line_byte[3] = line_byte_[3];
  
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 8; j++){
      hoge[i * 8 + j] = line_byte_[i] % 2;
      line_byte_[i] /= 2;
      if(i == 3 && 2 <= j){
        break;
      }
    }
  }

  // for(int i = 0; i < 27; i++){
  //   Serial.print(hoge[i]);
  // }
  Serial.println();
}