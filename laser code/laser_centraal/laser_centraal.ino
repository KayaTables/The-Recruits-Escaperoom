#define ACTIVEMASK 0b00000010
#define ALARMMASK  0b00000001

#define INGANGBUTTON A4
#define STOPBUTTON A3
#define INGANGLED A2
#define INDRINGERLED A1
#define LASERIN 7
#define INGANGSIG 3


byte state = 0b00000010;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(INGANGBUTTON, INPUT_PULLUP);         
  pinMode(STOPBUTTON, INPUT_PULLUP);         
  pinMode(A2, OUTPUT);         
  digitalWrite(A2, LOW);     
  pinMode(A1, OUTPUT);         
  digitalWrite(A1, LOW);     
  pinMode(A0, OUTPUT);         
  digitalWrite(A0, LOW);
  pinMode(INGANGSIG, OUTPUT);         
  digitalWrite(INGANGSIG, LOW);      

  
}

void loop() 
{
  lasercheck();
  buttoncheck();
  ledcontrol();
  if (state & ALARMMASK) digitalWrite(INGANGSIG, HIGH); else digitalWrite(INGANGSIG, LOW);
}

void buttoncheck()
{
  if (!digitalRead(INGANGBUTTON)) state = state | ACTIVEMASK;
  if (!digitalRead(STOPBUTTON)) state = state & ~ACTIVEMASK;

}

void lasercheck()
{
  if(!digitalRead(LASERIN) & (state && ACTIVEMASK)) state = state | ALARMMASK;
}

void ledcontrol() 
{
  if (state & ACTIVEMASK)digitalWrite(INGANGLED, HIGH);     
  if (millis()%1000 < 500 && state & ALARMMASK ) digitalWrite(INDRINGERLED, HIGH);     
  //digitalWrite(A0, HIGH); 
  delayMicroseconds(1);
  digitalWrite(INGANGLED, LOW);     
  digitalWrite(INDRINGERLED, LOW);     
  //digitalWrite(A0, LOW); 
  delayMicroseconds(100);
}
