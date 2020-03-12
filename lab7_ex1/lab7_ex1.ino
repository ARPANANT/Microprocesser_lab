float brightness = 0;
String buff;
int state;
int port = 0;

void setup() 
{
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  if (Serial.available() > 0) 
  {
    char inByte = Serial.read();
    if(inByte == 'L')
    {
      state = 0;
      buff = ' ';
    }
    if((inByte == '1') && (state == 0))
    {
      port = 9;
    }
    if((inByte == '2') && (state == 0))
    {
      port = 10;
    }
    if(inByte == 'B')
    {
      state = 1;
      buff = ' ';
    } 
    if(('0'<= inByte) && (inByte <= '9') && (state == 1))
    {
      buff += inByte;
    }

      brightness = buff.toInt();
      Serial.println(brightness);
      analogWrite(port,int(brightness*2.54)); 
  }
}
