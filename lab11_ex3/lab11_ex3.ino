#define MOTOR_PIN1 7
#define MOTOR_PIN2 8
#define MOTOR_PWM_PIN 6
#define INT_PIN0 13
#define INT_PIN1 12
#define INT_PIN2 11
#define LED_PIN 10 
int led_1_state = LOW; 
unsigned long previous_millis_led_1 = 0; 
const long led_1_interval = 500;  
int interruptChannel1APin = 2;
int interruptChannel1BPin = 3;
int delay_count = 0;
int setpoint=0;
int fb_speed = 0;
int set1=0;
int set2=0;
int set3=0;
int LED=1;

volatile int encoderCount = 0;
volatile int encoderDir = 0;
void moveforward (int speed) 
{
  digitalWrite(MOTOR_PIN1,HIGH);
  digitalWrite(MOTOR_PIN2,LOW);
  analogWrite(MOTOR_PWM_PIN,speed);
}
void movebackward (int speed) 
{
  digitalWrite(MOTOR_PIN1,LOW);
  digitalWrite(MOTOR_PIN2,HIGH);
  analogWrite(MOTOR_PWM_PIN,speed);
}
void setSpeed (int speed)
{
  if (speed>0)
  {
    if(speed>100)
    {speed=100;}
    moveforward(speed);
  }
 else if (speed<0)
 {
   speed=speed*(-1);
   if (speed>100)
   {speed=100;}
   movebackward(speed);
 }
 else
 {moveforward(1);}
}
void Timer1_initialize (int period)
{
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A  = (16000000.0/(256.0*1000.0))*period - 1;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}
void setup()
{
  pinMode(MOTOR_PIN1,OUTPUT);
  pinMode(MOTOR_PIN2,OUTPUT);
  pinMode(MOTOR_PWM_PIN,OUTPUT);
  pinMode(INT_PIN0, INPUT_PULLUP);
  pinMode(INT_PIN1, INPUT_PULLUP);
  pinMode(INT_PIN2, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(interruptChannel1APin,INPUT_PULLUP);
  pinMode(interruptChannel1BPin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptChannel1APin),Channel1A_callback, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptChannel1BPin),Channel1B_callback, RISING);
  Serial.begin(9600);
  Timer1_initialize(300);
}

int errori = 0;
float kp = 1.0;
float ki = 0.3;

void loop()
{
  unsigned long current_millis = millis(); 
  int error = setpoint - fb_speed;
  int pid = kp*(float)(error)+ ki*(float)(errori);
  errori += error;
  setSpeed(pid);
  Serial.print(setpoint);
  Serial.print(",");
  Serial.println(fb_speed);
  delay(100);
  set1= digitalRead(INT_PIN0);
  set2= digitalRead(INT_PIN1);
  set3= digitalRead(INT_PIN2);
  if(set1==0)
  {
    if(setpoint>0){setpoint=setpoint;}
    if(setpoint<0){setpoint=setpoint*-1;}
  }
  if(set2==0)
  {setpoint=0;}
  if(set1==0)
  {
    if(setpoint<0){setpoint=setpoint;}
    if(setpoint>0){setpoint=setpoint*-1;}
  }
  if (LED>0)
  {
    digitalWrite(10,HIGH);
    LED=-1;
  }
  else
  {
    digitalWrite(10,LOW);
    LED=1;
  }
  if(current_millis - previous_millis_led_1 >= led_1_interval) 
  { 
    previous_millis_led_1 = current_millis;    
    digitalWrite(LED_PIN, led_1_state);          
    led_1_state = !led_1_state;   
  }   
}
void Channel1A_callback()
{
  if (digitalRead(interruptChannel1APin)==1 && digitalRead(interruptChannel1BPin)==0)
    {encoderCount++;}
}
void Channel1B_callback()
{
  if (digitalRead(interruptChannel1APin)==0 && digitalRead(interruptChannel1BPin)==1)
    {encoderCount--;}
}
ISR(TIMER1_COMPA_vect)
{
  fb_speed = encoderCount;
  encoderCount = 0;
}
void serialEvent() 
{
  if(Serial.read() != 's') 
  {return;}
  float val = Serial.parseFloat();
  if(Serial.read() != 'n') 
  {return;}
  if(Serial.available()) 
  {
      Serial.read();
  }
  setpoint = constrain(val, -100.0, 100.0);
  Serial.println(setpoint);
}
