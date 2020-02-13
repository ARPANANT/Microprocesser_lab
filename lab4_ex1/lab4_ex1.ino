#include<SPI.h>
#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10
#define SS_PIN_2 9
int i,j;
int map7seq[10]={
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

void setup() 
{
  pinMode(DATA_PIN,OUTPUT);
  pinMode(CLOCK_PIN,OUTPUT);
  pinMode(SS_PIN_1,OUTPUT);
  pinMode(SS_PIN_2,OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  
  for(j=0;j<10;j++)
  {
    spi_write_1(map7seq[j]);
    delay(500);
   for(i=0;i<10;i++)
   {
    spi_write_2(map7seq[i]);
    delay(500);
   }
    
  }
  
}
