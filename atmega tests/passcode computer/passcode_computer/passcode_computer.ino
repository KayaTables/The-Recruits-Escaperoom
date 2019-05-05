
#include <LiquidCrystal.h>

#define CLEAR 91
#define ENTER 92

#define PASSWORD "NERVEGAS"
#define CORRECTWAIT 3600000 //hoe lang staat er PASSWORD CORRECT? 3600000 is een uur 

//#define DEBUG 1


int lid[7] = { 2,3,4,5,6,8,9 };

int groep[4] = {14 ,15, 16, 17};

char input;
char buff[16];
int buffcount;



const int rs = 18, en = 19, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode (18, OUTPUT);
  pinMode (19, OUTPUT);
  lcd.begin(16, 2);
  
  Serial.begin(115200);
  Serial.println("serialset");
  
  pinMode(groep[0], INPUT);
  pinMode(groep[1], INPUT);
  pinMode(groep[2], INPUT);
  pinMode(groep[3], INPUT);

}

void loop() {
  lcd.clear();
  lcd.print("Password");
  lcd.setCursor(0, 1);

  buffcount = 0;

  #ifdef DEBUG
  Serial.println("precheck");
  #endif
  
  if(buttoncheck() == 1) 
  {
    if (passcheck())
    {
      lcd.clear();
      lcd.print("Password");
      lcd.setCursor(0, 1);
      lcd.print("PASSWORD CORRECT");
      delay(CORRECTWAIT);
    } else 
    {
      lcd.clear();
      lcd.print("Password");
      lcd.setCursor(0, 1);
      lcd.print("WRONG PASSWORD");
      delay(2000);
    }
  }

  #ifdef DEBUG
  Serial.println(buff);
  #endif

}

int buttoncheck()
{
  while(1)
  {
    for(int groepcount = 0; groepcount < 4; groepcount++)
    {
      if (groepcount == 0) pinMode(groep[3], INPUT);
      else pinMode(groep[groepcount-1], INPUT); 
      pinMode(groep[groepcount], OUTPUT);
      digitalWrite(groep[groepcount], LOW);

      #ifdef DEBUG
      Serial.print("groep: ");
      Serial.println(groepcount);
      #endif
  
      for(int lidcount = 0; lidcount < 7; lidcount++)
      {
        #ifdef DEBUG
        Serial.print("lid: ");
        Serial.println(lidcount);
        #endif
        
        if (lidcount == 0) {pinMode(lid[7], INPUT);digitalWrite(lid[7], LOW);}
        else {pinMode(lid[lidcount-1], INPUT);digitalWrite(lid[lidcount-1], LOW);}
        pinMode(lid[lidcount], INPUT_PULLUP);
        
        delay(1);
        if(!digitalRead(lid[lidcount])) 
        {
          delay(20);
          if(!digitalRead(lid[lidcount])) 
          {
            input = char(7*groepcount+lidcount+65);

            #ifdef DEBUG
            Serial.println(7*groepcount+lidcount);
            #endif
            
            if (input == CLEAR) 
            {
              buffcount = 0;
              return 0;
            }
            if (input == ENTER) 
            {
              buff[buffcount++] = '\0'; 
              return 1;
            }
            
            
            buff[buffcount++] = input;
            
            lcd.print(input);
            while(!digitalRead(lid[lidcount]));
          }
        }
      }
    }
  }
}

int passcheck()
{
  char password[] = PASSWORD;
  for(int i = 0; i<sizeof(PASSWORD);i++) if (buff[i] != password[i]) return 0;
  return 1;
}
