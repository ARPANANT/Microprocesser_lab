#define DATA_PIN 5
#define CLOCK_PIN 6
#define LATCH_PIN 4
bool toggle;
int c,i;

void LED(uint16_t state)
{
  digitalWrite(LATCH_PIN,LOW);
  for(i=0;i<16;i++)
  {
    digitalWrite(DATA_PIN,(state>>(15-i))&0x01);
    digitalWrite(CLOCK_PIN,HIGH);
    digitalWrite(CLOCK_PIN,LOW);
  }
  digitalWrite(LATCH_PIN,HIGH);
}
void setup() 
{
  pinMode(CLOCK_PIN,OUTPUT); 
  pinMode(LATCH_PIN,OUTPUT); 
  pinMode(DATA_PIN,OUTPUT);
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
}

void loop() 
{
    LED(~(0x0001<<c));
    if(c>15)
    {
      c=0;
    }
    if(c<0)
    {
      c=16;
    }
    if(((PINC>>0)&0x01)==0)
    {
      c++;
    }
    else if(((PINC>>1)&0x01)==0)
    {
      c--;
    }
    delay(100);

}
