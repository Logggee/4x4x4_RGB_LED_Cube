#include <TimerOne.h>
#include <EEPROM.h>

#define ADDRESS_SUB_MENU 0
#define ADDRESS_MENU 1

// RCLK, SRCLK, SER, SRCLR, OE
const byte RCLK_B = 9, CLOCK = 10, DATA_B = 8, SRCLR_B = 3, OE_B = 2;
const byte RCLK_G = 4, DATA_G = 5, SRCLR_G = 6, OE_G = 7;
const byte RCLK_R = 11, DATA_R = 12, SRCLR_R = 13, OE_R = A0;
const byte LAYER1 = A1, LAYER2 = A2, LAYER3 = A3, LAYER4 = A4;
const byte ANALOG_PIN = A5;

volatile int interrupt_status = 0;

// Variables for diffrent menu states
byte menu = 1, subMenu = 1;

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(RCLK_B,OUTPUT);        //PIN definitionen
  pinMode(CLOCK,OUTPUT);
  pinMode(DATA_B,OUTPUT);
  pinMode(SRCLR_B,OUTPUT);         //SERCLK
  pinMode(OE_B,OUTPUT);            //OE

  pinMode(RCLK_G,OUTPUT);
  pinMode(DATA_G,OUTPUT);
  pinMode(SRCLR_G,OUTPUT);
  pinMode(OE_G,OUTPUT);

  pinMode(RCLK_R,OUTPUT);
  pinMode(DATA_R,OUTPUT);
  pinMode(SRCLR_R,OUTPUT);
  pinMode(OE_R,OUTPUT);

  pinMode(LAYER1,OUTPUT);
  pinMode(LAYER2,OUTPUT);
  pinMode(LAYER3,OUTPUT);
  pinMode(LAYER4,OUTPUT);

  digitalWrite(OE_R, LOW);
  digitalWrite(OE_G, LOW);
  digitalWrite(OE_B, LOW);

  digitalWrite(SRCLR_R, HIGH);
  digitalWrite(SRCLR_G, HIGH);
  digitalWrite(SRCLR_B, HIGH);

  digitalWrite(RCLK_R, LOW);
  digitalWrite(RCLK_G, LOW);
  digitalWrite(RCLK_B, LOW);

  
  menu = EEPROM.read(ADDRESS_MENU);
  subMenu = EEPROM.read(ADDRESS_SUB_MENU);

  Timer1.initialize(100000);
  Timer1.attachInterrupt(switchMenu); //Trigger every 100 ms the Taster_Funktion
}

void DisplayStatic(int *layerSelection, byte *data[3][2], int displayTime);
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void loop(){
  interrupts();

  //Serial.println("Menu: " + String(menu));
  //Serial.println("Sub Menu: " + String(subMenu));

  switch (menu){
    case 0: menu = 2; break;

    case 1:
      switch (subMenu){
        case 1: fullRed(); break;

        case 2: fullGreen(); break;

        case 3: fullBlue(); break;

        case 4: fullYellow(); break;

        case 5: fullPurple(); break;

        case 6: fullLigthBlue(); break;

        case 7: fullWhite(); break;

        case 8:
          digitalWrite(OE_R, HIGH);
          digitalWrite(OE_G, HIGH);
          digitalWrite(OE_B, HIGH);
          shiftOut(DATA_R, CLOCK, MSBFIRST, 0XFF);
          shiftOut(DATA_R, CLOCK, MSBFIRST, 0XFF);
          digitalWrite(RCLK_R, HIGH);
          digitalWrite(RCLK_R, LOW);

          shiftOut(DATA_G, CLOCK, MSBFIRST, 0XFF);
          shiftOut(DATA_G, CLOCK, MSBFIRST, 0XFF);
          digitalWrite(RCLK_G, HIGH);
          digitalWrite(RCLK_G, LOW);

          digitalWrite(A1, HIGH);
          digitalWrite(A2, HIGH);
          digitalWrite(A3, HIGH);
          digitalWrite(A4, HIGH);
          /*
          for(int i=0; i<1000; i++){
            digitalWrite(OE_R, LOW);
            digitalWrite(OE_G, LOW);
            delayMicroseconds(200);
            digitalWrite(OE_R, HIGH);
            delayMicroseconds(800);
            digitalWrite(OE_G, HIGH);
          }*/
          for(int i = 0; i < 1000; i++) {
            digitalWrite(OE_R, LOW);
            digitalWrite(OE_G, LOW);
            delayMicroseconds(1);
            digitalWrite(OE_R, HIGH);
            delayMicroseconds(1);
            digitalWrite(OE_G, HIGH);

          }
          
          digitalWrite(A1, LOW);
          digitalWrite(A2, LOW);
          digitalWrite(A3, LOW);
          digitalWrite(A4, LOW);
          digitalWrite(OE_R, LOW);
          digitalWrite(OE_G, LOW);
          digitalWrite(OE_B, LOW);
          break;

        case 9: subMenu = 1; break;
      }
    break;
    
    case 2:
      switch (subMenu){
        case 1: levelShiftsRed(); break;

        case 2: levelShiftGreen(); break;

        case 3: levelShiftBlue(); break;

        case 4: subMenu = 1; break;
      }
    break;

    case 3: menu = 1; break;
  }
}

/*
void  DisplayMultiplexed(byte *dataR, byte *dataG, byte *dataB){
  for(int i=0; i<2; i++){
    shiftOut(DATA_R, CLOCK, MSBFIRST, dataR[0][i]);
    shiftOut(DATA_R, CLOCK, MSBFIRST, dataG[0][i]);
    shiftOut(DATA_R, CLOCK, MSBFIRST, dataB[0][i]);
  }
  digitalWrite(RCLK_R, HIGH);
  digitalWrite(RCLK_R, LOW);
  for(int i=0; i<2; i++){
    shiftOut(DATA_R, CLOCK, MSBFIRST, dataR[1][i]);
    shiftOut(DATA_R, CLOCK, MSBFIRST, dataG[1][i]);
    shiftOut(DATA_R, CLOCK, MSBFIRST, dataB[1][i]);
  }

  digitalWrite(A1, HIGH);
  delay(1);
  digitalWrite(A1, LOW);

  digitalWrite(RCLK_R, HIGH);
  digitalWrite(RCLK_R, LOW);
  digitalWrite(A2, HIGH);
  delay(1);
  for(int i=0; i<2; i++){
    shiftOut(DATA_R, CLOCK, MSBFIRST, dataR[3][i]);
    shiftOut(DATA_R, CLOCK, MSBFIRST, dataG[3][i]);
    shiftOut(DATA_R, CLOCK, MSBFIRST, dataB[3][i]);
  }
  digitalWrite(A2, LOW);

  digitalWrite(RCLK_R, HIGH);
  digitalWrite(RCLK_R, LOW);
  digitalWrite(A3, HIGH);
  delay(1);
  for(int i=0; i<2; i++){
    shiftOut(DATA_R, CLOCK, MSBFIRST, dataR[4][i]);
    shiftOut(DATA_R, CLOCK, MSBFIRST, dataG[4][i]);
    shiftOut(DATA_R, CLOCK, MSBFIRST, dataB[4][i]);
  }
  digitalWrite(A3, LOW);

  digitalWrite(RCLK_R, HIGH);
  digitalWrite(RCLK_R, LOW);
  digitalWrite(A4, HIGH);
  delay(1);
  digitalWrite(A4, LOW);
}*/