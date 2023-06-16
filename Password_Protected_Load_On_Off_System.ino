#include <Keypad.h>
#include<Wire.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(1, 0, 5, 4, 3, 2);

#define passwordsize 5

char Masterpass[passwordsize]="2043";
char Data[passwordsize];
byte data_count=0;
char customKey;

#define led A0
bool state;


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13,12,11,10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9,8,7,6}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  lcd.begin(16, 2);
  pinMode(led,OUTPUT);
}
  
void loop(){


  lcd.setCursor(0,0);
  lcd.print("Enter Password:");
  customKey = customKeypad.getKey();
  
  if(customKey)
  {
    lcd.setCursor(data_count,1);
    lcd.print(customKey);
    Data[data_count] = customKey;    
    data_count++;    
  }
  if(data_count == passwordsize-1)
  {
    lcd.clear();
    if(!strcmp(Data,Masterpass))
    {
      lcd.setCursor(0,0);
      lcd.print("Password Matched");
      state = !state;
      digitalWrite(led,state);      
    }
    else
    {
      lcd.setCursor(0,0);
      lcd.print("Wrong Password");
    }
    delay(1000);
    data_count = 0;
  }
}
