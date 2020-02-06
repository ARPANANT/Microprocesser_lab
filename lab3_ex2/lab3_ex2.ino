#define DATA_PIN 11
#define CLOCK_PIN 13
#define LATCH_PIN 10
int i;
bool toggle;
int map7seg[10]= {0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};

void Led(uint8_t state)
{
  for( i=0;i<8;i++)
  {
    digitalWrite(DATA_PIN,(state>>(7-i))&0x01);
    digitalWrite(CLOCK_PIN,HIGH);
    digitalWrite(CLOCK_PIN,LOW);
  }
  digitalWrite(LATCH_PIN,HIGH);
  digitalWrite(LATCH_PIN,LOW);
  delay(1000);
}

void setup()
{
  Serial.begin(9600);
  while(!Serial)
  {}
  Serial.println("\n\nString toInt():");
  Serial.println();
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN,OUTPUT);
}

void loop()
{
  String inString;
  if(Serial.available()!=0)
  {
    while(Serial.available()>0)
    {
      int inChar=Serial.read();
      inString = (char)inChar;
      Serial.print("Value:");
      Serial.println(inString.toInt());
    }
    Led(map7seg[inString.toInt()]);
  }
}
