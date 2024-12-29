#include <Keypad.h>
#include <TM1637Display.h>

#define CLK 4
#define DIO 5
int vibrateAnalogPin = A0;
int vibrateAnalogValue = 0;
int buzzerPin = 7;
int YOURPASS = 1234;
int Alarm = 0;
int num;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};
char customKey[10];


Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
TM1637Display display(CLK, DIO);

void setup() {
  pinMode(vibrateAnalogPin,INPUT);
  Serial.begin(9600);
  display.setBrightness(0x0f, true);
}

void loop() {
  long int Pass = 0;
  num=0;
  display.showNumberDec(Pass, true, 4, 0);
  vibrateAnalogValue = analogRead(vibrateAnalogPin);
  delay(100);
  if (vibrateAnalogValue < 950) {
     Alarm +=1;
     digitalWrite(buzzerPin,HIGH);
     delay(2000);
     digitalWrite(buzzerPin,LOW);
  }
  
  while (Alarm == 2) {
    int customKey = customKeypad.getKey();
    if (Pass != YOURPASS)  digitalWrite(buzzerPin,HIGH);
    if (Pass == YOURPASS)  {
      digitalWrite(buzzerPin,LOW);
      Alarm = 0;
      }
    if (customKey){
      num++;
      if (num<5) Pass = Pass*10 + (customKey-48);
      if (customKey == 65) {
        Pass=0;
        num=0;
      }
      display.showNumberDec(Pass, false, 4, 0);
      }
  }
}