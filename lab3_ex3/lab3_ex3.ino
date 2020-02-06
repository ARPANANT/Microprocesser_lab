#define DATA_PIN 11
#define CLOCK_PIN 13
#define LATCH_PIN 10
int i,c;
bool toggle;
int map7seq[16]={
  0x3F,//0
  0x06,//1
  0x5B,//2
  0x4F,//3
  0x66,//4
  0x6D,//5
  0x7D,//6
  0x07,//7
  0x7F,//8
  0x6F,//9
  0x77,//A
  0x7C,//b
  0x39,//c
  0x5E,//d
  0x79,//E
  0x71//F
};
void setup() 
{
  pinMode(DATA_PIN,OUTPUT);
  pinMode(CLOCK_PIN,OUTPUT);
  pinMode(LATCH_PIN,OUTPUT);
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);

}

void loop() 
{
  if(c>9)
   c=0;
  if(c<0)
   c=9;
  if(((PINC>>0)&0x01)==0)
  {
    c++;
  }
  else if(((PINC>>1)&0x01)==0)
  {
    c--;
  }
  delay(100);
  for(i=0;i<8;i++)
  {
    digitalWrite(DATA_PIN,(map7seq[c]>>(7-i))&0x01);
    digitalWrite(CLOCK_PIN,HIGH);
    digitalWrite(CLOCK_PIN,LOW);
  }
  digitalWrite(LATCH_PIN,HIGH);
  delay(100);
  digitalWrite(LATCH_PIN,LOW);
 
}
