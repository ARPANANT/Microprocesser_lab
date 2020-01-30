#define DATA_PIN 5
#define CLOCK_PIN 6
#define LATCH_PIN 4
int i=0;
int data;
bool toggle;

void setup() 
 {

  pinMode(CLOCK_PIN,OUTPUT); 
  pinMode(LATCH_PIN,OUTPUT); 
  pinMode(DATA_PIN,OUTPUT);
 }
void loop() 
 {

    digitalWrite(LATCH_PIN,LOW);
    data = 0b10000000;
    digitalWrite (LATCH_PIN, LOW);
    for (i=0;i<16;i++){
    digitalWrite(DATA_PIN, data >>(7-i)&0b00000001);
    digitalWrite(CLOCK_PIN, HIGH);
    delay(100);
    digitalWrite(CLOCK_PIN, LOW);
    delay(100);
    digitalWrite(LATCH_PIN, HIGH);
    digitalWrite(LATCH_PIN, LOW);
 }
}
