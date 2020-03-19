#define LED_PIN 13
#define INT_PIN   2
volatile int p = 1;

int CalOCR(double freq, long prescaler) 
{
  const long CLK_FQ = 16000000;
  return (CLK_FQ / (freq * prescaler)) - 1.0;
}

void setup()
{
  pinMode(INT_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = CalOCR(1, 1024);
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
  attachInterrupt(digitalPinToInterrupt(2),Button, RISING);
}
void Button() 
{
  digitalWrite(LED_PIN, HIGH);
  p = p >= 3 ? 1 : p + 1;
  OCR1A = CalOCR(1.0/(double)(p), 1024);
}
ISR(TIMER1_COMPA_vect)
{
  PORTB ^= (1 << 5);
 }
void loop()
{
  delay(1000);
}
