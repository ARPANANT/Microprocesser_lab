#include <Wire.h>
#include <SPI.h>
#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10

int map7seg[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F };
int c = 0 ;
void spi_write_1(unsigned char cData)
{
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, cData);
  digitalWrite (SS_PIN_1, HIGH);
  digitalWrite (SS_PIN_1, LOW);
}
int CalOCR(double freq, long prescaler)
{
  const long CLK_FQ = 16000000;
  return (CLK_FQ / (freq * prescaler)) - 1.0;
}
void setup()
{
  pinMode(SS_PIN_1, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = CalOCR(1,1024);
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

ISR(TIMER1_COMPA_vect)
{
  spi_write_1(map7seg[c-1]);
}

void loop()
{
 if (c>9)
 {c=0;}
 c++;
 delay(1000);
}
