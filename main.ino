#include <SoftPWM.h>
#include <SoftPWM_timer.h>

int interval = 50000;
long int time = 0;

int i = 0;
int i2 = 0;
int dataPin = 12;
int bitlenght = -1;
char data[43];
String Wind_Direction;
int catchN = 0;
int catchO = 0;
int catchZ = 0;
int catchW = 0;
int catchNO = 0;
int catchZO = 0;
int catchZW = 0;
int catchNW = 0; 
int catchIncr = 8;

uint8_t lightbulbs[8] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup() {
  //digitalWrite(10, HIGH); //We need to set it HIGH immediately on boot
  //pinMode(10,OUTPUT);     //We can declare it an output ONLY AFTER it's HIGH

  Serial.begin(9600);
  Serial.print("\n\nInitializing...\n");
  Serial.print("Data Pin: ");
  Serial.println(digitalRead(dataPin));
  pinMode(dataPin, INPUT);
  
  // Initialize  
  SoftPWMBegin();  
  
  Serial.print("\n\nSetting fade time for all outputs...\n");
  SoftPWMSetFadeTime(ALL, 100, 250);
  
  Serial.print("\n\nTesting in all outputs...\n");
  SoftPWMSet(ALL, 0);
  
  for (int i2 = 0; i2 < 4; i2++) {
    for (int i = 0; i < 8; i++) {
      SoftPWMSet(lightbulbs[i], 0);
      delay(150);
      SoftPWMSet(lightbulbs[i], 255);
      delay(150);
    }
  }
  
}

void delay2(unsigned long ms){
    unsigned long start = micros();
    while (micros() - start <= ms);
}

void loop() {
  
  time = millis();

  if(time > interval){
    collectdata();
    time = 0;
  }
  
  showdatasimple();
  
}


int collectdata(void){
   if (bitlenght <0){
      bitlenght = 1230;//getbitlenght2() 1230;
   }
  
  pinMode(dataPin, OUTPUT);
  digitalWrite(dataPin, HIGH);
  delay(100);
  
  digitalWrite(dataPin, LOW );
  delay(500);
  
  pinMode(dataPin, INPUT);

  while(digitalRead(dataPin) == LOW){
  }  
  while(digitalRead(dataPin) == HIGH){
  }
  while(digitalRead(dataPin) == LOW){
  }

  for (int i=0 ; i<42 ; i++){

    data[i] = (digitalRead(dataPin) == LOW)? 48 : 49 ;
    delay2(bitlenght);
  }
  
}

void showdatasimple(){
  Serial.println("");
  
  String Wind_Dir_PatternStr = "b";
  String Wind_Dir_DescStr = "";
  for (int i =8 ; i> 4 ; i--){
    Wind_Dir_PatternStr += ((data[i] == 48)? 0 : 1);
  }

  Serial.print(Wind_Dir_PatternStr);
  Serial.print(" = ");
  
  // 51 zijn 5 stappen
  
  //catchN = 0; catchO = 0; catchZ = 0; catchW = 0; catchNO = 0; catchZO = 0; catchZW = 0; catchNW = 0; 
  
  if (Wind_Dir_PatternStr == "b0000") { Wind_Dir_DescStr="N"; 
  catchN=catchN+catchIncr; catchO=catchO-catchIncr; catchZ=catchZ-catchIncr; catchW=catchW-catchIncr; catchNO=catchNO-catchIncr; catchZO=catchZO-catchIncr; catchZW=catchZW-catchIncr; catchNW=catchNW-catchIncr; }
  if (Wind_Dir_PatternStr == "b0001") { Wind_Dir_DescStr="NNO"; 
  catchN=catchN+catchIncr; catchO=catchO-catchIncr; catchZ=catchZ-catchIncr; catchW=catchW-catchIncr; catchNO=catchNO+catchIncr; catchZO=catchZO-catchIncr; catchZW=catchZW-catchIncr; catchNW=catchNW-catchIncr; }
  if (Wind_Dir_PatternStr == "b0010") { Wind_Dir_DescStr="NO"; 
  catchN=catchN-catchIncr; catchO=catchO-catchIncr; catchZ=catchZ-catchIncr; catchW=catchW-catchIncr; catchNO=catchNO+catchIncr; catchZO=catchZO-catchIncr; catchZW=catchZW-catchIncr; catchNW=catchNW-catchIncr; }
  if (Wind_Dir_PatternStr == "b0011") { Wind_Dir_DescStr="ONO"; 
  catchN=catchN-catchIncr; catchO=catchO+catchIncr; catchZ=catchZ-catchIncr; catchW=catchW-catchIncr; catchNO=catchNO+catchIncr; catchZO=catchZO-catchIncr; catchZW=catchZW-catchIncr; catchNW=catchNW-catchIncr; }
  if (Wind_Dir_PatternStr == "b0100") { Wind_Dir_DescStr="O"; 
  catchN=catchN-catchIncr; catchO=catchO+catchIncr; catchZ=catchZ-catchIncr; catchW=catchW-catchIncr; catchNO=catchNO-catchIncr; catchZO=catchZO-catchIncr; catchZW=catchZW-catchIncr; catchNW=catchNW-catchIncr; }
  if (Wind_Dir_PatternStr == "b0101") { Wind_Dir_DescStr="OZO"; 
  catchN=catchN-catchIncr; catchO=catchO+catchIncr; catchZ=catchZ-catchIncr; catchW=catchW-catchIncr; catchNO=catchNO-catchIncr; catchZO=catchZO+catchIncr; catchZW=catchZW-catchIncr; catchNW=catchNW-catchIncr; }
  if (Wind_Dir_PatternStr == "b0110") { Wind_Dir_DescStr="ZO"; 
  catchN=catchN-catchIncr; catchO=catchO-catchIncr; catchZ=catchZ-catchIncr; catchW=catchW-catchIncr; catchNO=catchNO-catchIncr; catchZO=catchZO+catchIncr; catchZW=catchZW-catchIncr; catchNW=catchNW-catchIncr; }
  if (Wind_Dir_PatternStr == "b0111") { Wind_Dir_DescStr="ZZO"; 
  catchN=catchN-catchIncr; catchO=catchO+catchIncr; catchZ=catchZ+catchIncr; catchW=catchW-catchIncr; catchNO=catchNO-catchIncr; catchZO=catchZO+catchIncr; catchZW=catchZW-catchIncr; catchNW=catchNW-catchIncr; }
  if (Wind_Dir_PatternStr == "b1000") { Wind_Dir_DescStr="Z"; 
  catchN=catchN-catchIncr; catchO=catchO-catchIncr; catchZ=catchZ+catchIncr; catchW=catchW-catchIncr; catchNO=catchNO-catchIncr; catchZO=catchZO-catchIncr; catchZW=catchZW-catchIncr; catchNW=catchNW-catchIncr; }
  if (Wind_Dir_PatternStr == "b1001") { Wind_Dir_DescStr="ZZW"; 
  catchN=catchN-catchIncr; catchO=catchO-catchIncr; catchZ=catchZ+catchIncr; catchW=catchW-catchIncr; catchNO=catchNO-catchIncr; catchZO=catchZO-catchIncr; catchZW=catchZW+catchIncr; catchNW=catchNW-catchIncr; }
  if (Wind_Dir_PatternStr == "b1010") { Wind_Dir_DescStr="ZW"; 
  catchN=catchN-catchIncr; catchO=catchO-catchIncr; catchZ=catchZ-catchIncr; catchW=catchW-catchIncr; catchNO=catchNO-catchIncr; catchZO=catchZO-catchIncr; catchZW=catchZW+catchIncr; catchNW=catchNW-catchIncr; }
  if (Wind_Dir_PatternStr == "b1011") { Wind_Dir_DescStr="WZW"; 
  catchN=catchN-catchIncr; catchO=catchO-catchIncr; catchZ=catchZ-catchIncr; catchW=catchW+catchIncr; catchNO=catchNO-catchIncr; catchZO=catchZO-catchIncr; catchZW=catchZW+catchIncr; catchNW=catchNW-catchIncr; }
  if (Wind_Dir_PatternStr == "b1100") { Wind_Dir_DescStr="W"; 
  catchN=catchN-catchIncr; catchO=catchO-catchIncr; catchZ=catchZ-catchIncr; catchW=catchW+catchIncr; catchNO=catchNO-catchIncr; catchZO=catchZO-catchIncr; catchZW=catchZW-catchIncr; catchNW=catchNW-catchIncr; }
  if (Wind_Dir_PatternStr == "b1101") { Wind_Dir_DescStr="WNW"; 
  catchN=catchN-catchIncr; catchO=catchO-catchIncr; catchZ=catchZ-catchIncr; catchW=catchW+catchIncr; catchNO=catchNO+catchIncr; catchZO=catchZO-catchIncr; catchZW=catchZW-catchIncr; catchNW=catchNW+catchIncr; }
  if (Wind_Dir_PatternStr == "b1110") { Wind_Dir_DescStr="NW"; 
  catchN=catchN-catchIncr; catchO=catchO-catchIncr; catchZ=catchZ-catchIncr; catchW=catchW-catchIncr; catchNO=catchNO-catchIncr; catchZO=catchZO-catchIncr; catchZW=catchZW-catchIncr; catchNW=catchNW+catchIncr; }
  if (Wind_Dir_PatternStr == "b1111") { Wind_Dir_DescStr="NNW"; 
  catchN=catchN+catchIncr; catchO=catchO-catchIncr; catchZ=catchZ-catchIncr; catchW=catchW-catchIncr; catchNO=catchNO-catchIncr; catchZO=catchZO-catchIncr; catchZW=catchZW-catchIncr; catchNW=catchNW+catchIncr; }

  if (catchN < 0) {catchN = 0;}
  if (catchO < 0) {catchO = 0;}
  if (catchZ < 0) {catchZ = 0;}
  if (catchW < 0) {catchW = 0;} 
  if (catchNO < 0) {catchNO = 0;}
  if (catchZO < 0) {catchZO = 0;} 
  if (catchZW < 0) {catchZW = 0;}
  if (catchNW < 0) {catchNW = 0;}
 
  if (catchN > 255) {catchN = 255;}
  if (catchO > 255) {catchO = 255;}
  if (catchZ > 255) {catchZ = 255;}
  if (catchW > 255) {catchW = 255;} 
  if (catchNO > 255) {catchNO = 255;}
  if (catchZO > 255) {catchZO = 255;} 
  if (catchZW > 255) {catchZW = 255;}
  if (catchNW > 255) {catchNW = 255;} 

  Serial.print(Wind_Dir_DescStr); 
  /*
  Serial.print("  N: "+catchN);
  Serial.print(" NO: "+catchNO);
  Serial.print("  O: "+catchO);
  Serial.print(" ZO: "+catchZO);
  Serial.print("  Z: "+catchZ);
  Serial.print(" ZW: "+catchZW);
  Serial.print("  W: "+catchW);
  Serial.println(" NW: "+catchNW);
  */
  
  SoftPWMSet(ALL, 0);
  SoftPWMSet(lightbulbs[0], catchN);
  SoftPWMSet(lightbulbs[1], catchNO);
  SoftPWMSet(lightbulbs[2], catchO);
  SoftPWMSet(lightbulbs[3], catchZO);
  SoftPWMSet(lightbulbs[4], catchZ);
  SoftPWMSet(lightbulbs[5], catchZW);
  SoftPWMSet(lightbulbs[6], catchW);
  SoftPWMSet(lightbulbs[7], catchNW);
  
}

