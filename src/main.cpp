#include <Arduino.h>

#define Long 5


int LED = 13;
int FD[24] = {69,22,24,23,25,26,27,28,29,11,12,14,56,57,58,59,60,61,62,63,64,65,66,67};
int com = 2;
int th = 175;

float dis_X;
float dis_Y;
uint8_t num;
byte send[7];
int LINE_on;
double ele_X[27]; //ラインセンサのX座標
double ele_Y[27]; //ラインセンサのY座標
void getLine();

void setup() {
  Serial.begin(9600);
  Serial2.begin(57600);
  for(int i = 0; i < 24; i++){
    ele_Y[i] = sin(radians(15 * i));
    ele_X[i] = cos(radians(15 * i));
    pinMode(FD[i],INPUT);
  }
  pinMode(LED,OUTPUT);
  pinMode(com,OUTPUT);
  analogWrite(com,th);
}


void loop() {
  getLine();

  int vec[2] = {int(dis_X * 100),int(dis_Y * 100)};

  // Serial.print(vec[0]);
  // Serial.print(" ");
  // Serial.print(vec[1]);
  // Serial.print(" ang : ");
  // Serial.print(degrees(atan2(vec[1],vec[0])));

  // Serial.println();

  send[0] = 38;
  send[1] = byte(vec[0] >> 8);
  send[2] = byte(vec[0] & 0xFF);
  send[3] = byte(vec[1] >> 8);
  send[4] = byte(vec[1] & 0xFF);
  send[5] = num;
  send[6] = 37;

  Serial2.write(send,7);
}


void getLine(){
  float X = 0;
  float Y = 0;

  int data_on[26];
  int flag = 0;
  int block_first[Long];
  int block_last[Long];
  int block_num = -1;
  float block_X[Long];
  float block_Y[Long];

  uint8_t L_bit[26];
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

  for(int i = 0; i < 26; i++){
    if(L_bit[i] != 0){
      data_on[i] = 1;
    }
    else{
      data_on[i] = 0;
    }
    // Serial.print(data_on[i]);
    // Serial.print(" ");
  }
  for(int i = 0; i < 24; i++){
    if(i == 7 || i == 8 | i == 19 | i == 22){
      continue;
    }
    if(flag == 0){
      if(data_on[i] == 1){
        block_num++;
        block_first[block_num] = i;
        flag = 1;
      }
    }
    else{
      if(data_on[i] == 0){
        block_last[block_num] = i - 1;
        flag = 0;
      }
    }

    if(i == 23){
      if(data_on[23] == 1 && data_on[0] == 1){
        block_first[0] = block_first[block_num];
        block_first[block_num] = 0;
        block_num--;
      }

      if(data_on[23] == 1 && data_on[0] == 0){
        block_last[block_num] = 23;
      }
    }
  }

  for(int i = 0; i <= block_num; i++){
    block_X[i] = ele_X[block_first[i]] + ele_X[block_last[i]];
    block_Y[i] = ele_Y[block_first[i]] + ele_Y[block_last[i]];
    X += block_X[i];
    Y += block_Y[i];
  }
  block_num++;

  X /= block_num;
  Y /= block_num;
  dis_X = X;
  dis_Y = Y;
  num = block_num;

  if(block_num == 0){
    LINE_on = 0;
  }
  else{
    LINE_on = 1;
  }
}