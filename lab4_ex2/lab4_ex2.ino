#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10
#define SS_PIN_2 9
#define buzzer 3
#define DBOT_PIN A0
#define IBOT_PIN A1
#define SBOT_PIN A2

int n=0;
int map7seg[10] = {
    0x3F, //0
    0x06, //1
    0x5B, //2
    0x4F, //3
    0x66, //4
    0x6D, //5
    0x7D, //6
    0x07, //7
    0x7F, //8
    0x6F  //9
};

void spi_write_1(unsigned char cData)
{
  shiftOut(DATA_PIN,CLOCK_PIN,MSBFIRST,cData);
  digitalWrite(SS_PIN_1,HIGH);
  digitalWrite(SS_PIN_1,LOW);
}

void spi_write_2(unsigned char cData)
{
  shiftOut(DATA_PIN,CLOCK_PIN,MSBFIRST,cData);
  digitalWrite(SS_PIN_2,HIGH);
  digitalWrite(SS_PIN_2,LOW);
}
void dis_num(int x)
{
      int x1=0,x2=0;
      x1 = x % 10;
      x2 = x/10;
      spi_write_2(map7seg[x1]);
      spi_write_1(map7seg[x2]);
}

void setup()
{
  Serial.begin(9600);
  pinMode(SS_PIN_1, OUTPUT);
  pinMode(SS_PIN_2, OUTPUT);
  pinMode(DATA_PIN,OUTPUT);
  pinMode(CLOCK_PIN,OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
 
}

void loop()
{
  
  Serial.print(digitalRead(DBOT_PIN));
  Serial.print(digitalRead(IBOT_PIN));
  Serial.println(digitalRead(SBOT_PIN));
 
  if(digitalRead(DBOT_PIN) == 0 )
  {
    n--;
    noTone(buzzer);
  }
  if( digitalRead(IBOT_PIN) == 0 )
  {
    n++;
    noTone(buzzer);
  }
  if(digitalRead(SBOT_PIN) == 0)
  {
    delay(200);
    for(int i=n; i>=0;i--)
    {
      int counter = digitalRead(A2);
      dis_num(i);
      if(counter == 0)
      {
        n = i;
        i=-1;
      }
      delay(200);
      if(i == 0)
        n=0;
    }
  }
  if(n < 0)
    n = 99;
  if(n > 99)
    n = 0;
  if(n== 0)
    tone(buzzer, 5000);
  dis_num(n);
  delay(200);  
}
