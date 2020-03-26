#define MOTOR_PIN1  7
#define MOTOR_PIN2  8
#define MOTOR_PWM_PIN 6
int interruptChannelAPin = 2;
int interruptChannelBPin = 3;
int encoderDirection;
volatile int encoderCount = 0;
bool previous_read;

void moveforward(int speed)
{
  digitalWrite(MOTOR_PIN1, HIGH);
  digitalWrite(MOTOR_PIN2, LOW);
  analogWrite(MOTOR_PWM_PIN, speed);
}
void movebackward(int speed)
{
  digitalWrite(MOTOR_PIN2, HIGH);
  digitalWrite(MOTOR_PIN1, LOW);
  analogWrite(MOTOR_PWM_PIN, speed);
}
void setup() 
{
  Serial.begin(9600);
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  pinMode(interruptChannelAPin, INPUT_PULLUP);
  pinMode(interruptChannelBPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptChannelAPin),ChA_callback, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptChannelBPin),ChaB_callback, RISING);
}
void loop()
{
  moveforward(255);
  //movebackward(255);
  Serial.print("Direction:");
  Serial.print(encoderDirection); //Fw = 1, Bw = -1
  Serial.print(",Position:");
  Serial.println(encoderCount);
  delay(100);
}
void ChA_callback() 
{
  bool A = digitalRead(interruptChannelAPin);
  bool B = digitalRead(interruptChannelBPin);
  if ((A==1)&&(B==0))
  {
    encoderCount++;
    encoderDirection = 1;
  }
}
void ChaB_callback()
{
  bool A = digitalRead(interruptChannelAPin);
  bool B = digitalRead(interruptChannelBPin);
  if ((B==1)&&(A==0))
  {
    encoderCount--;
    encoderDirection = -1;
  }
}
