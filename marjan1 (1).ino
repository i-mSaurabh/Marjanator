#include <IBusBM.h>
#define ENA 3
#define IN1 5
#define IN2 4
#define ENB 9
#define IN3 10
#define IN4 11
#define auto_l 8
#define auto_r 9

IBusBM ibus;
int ch1 =0;
int ch2 =0;
int ch3 =0;
int ch4 =0;
bool ch6 =0;
int speed1=0;
int speed2=0;

int dir1 = 1;
int dir2 = 1;
void mControl1(int mspeed,int mdir){
  if(mdir ==0){
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    
  }
  else{
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
  }
  analogWrite(ENA,mspeed); 
}
void mControl2(int mspeed,int mdir){
  if(mdir ==0){
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    
  }
  else{
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
  }
  analogWrite(ENB,mspeed);  
}
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}
void autonomous(){
  int val_r = digitalRead(auto_r);
  int val_l = digitalRead(auto_l);

  if(val_r == 1 && val_l == 1){
    mControl1(255,1);
    mControl2(255,1);    
  }
  else if(val_r == 0 && val_l ==1){
    mControl1(255,0);
    mControl2(255,1);
    
  }
  else if(val_r = 1 && val_r = 0){
    mControl1(255,1);
    mControl2(255,0);
    
  }
  
}

void setup() {
  Serial.begin(9600);
  ibus.begin(Serial1);
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(auto_r,INPUT);
  pinMode(auto_l,INPUT);
  
    
}

void loop() {
  ch1 = readChannel(0,-100,100,0);
  ch2 = readChannel(1,-100,100,0);
  ch3 = readChannel(2,0,155,0);
  ch4 = readChannel(3,-100,100,0);
  ch6 = readSwitch( 5 ,false);

  Serial.print("CH1 = ");
  Serial.print(ch1);
  Serial.print("|");
  
  Serial.print("CH2 = ");
  Serial.print(ch2);
  Serial.print("|");
  Serial.print("CH3 = ");
  Serial.print(ch3);
  Serial.print("|");
  Serial.print("CH4 = ");
  Serial.print(ch4);
  Serial.print("|");
  Serial.print("CH6 = ");
  Serial.print(ch6);
  Serial.print("|");
  Serial.println();

  speed1 = ch3 ;
  speed2 = ch3 ;

  if(ch6){
    mControl1(255,1);
    mControl2(255,0);
//    autonomous();
  }else{
    if(ch2 > 0){
      dir1 = 1; //forward
      dir2 = 1;
    }
    else if(ch2 < 0){
      dir2 = 0; //backward
      dir1 = 0;
    }
    else if(ch4 >0){
      dir1 = 0 ; //right
      dir2 = 1;
    }
    else if(ch4 < 0 ){
      dir1 = 1;
      dir2 = 0;
    }
    speed1 = constrain(speed1,0,255);
    speed2 = constrain(speed2,0,255);
    mControl1(speed1,dir1);
    mControl2(speed2,dir2);   
  }
  

}
