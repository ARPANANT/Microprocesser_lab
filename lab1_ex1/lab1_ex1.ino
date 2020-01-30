int a,b;

void setup()

{

  DDRD = 0b11111100;

  DDRB = 0b000011;

}



void loop()

{

  PORTD = 0b00000100;

  PORTB = 0x00;

  for(a=0;a<6;a++)

  {

      delay(1000);

      PORTD=PORTD<<1;

  }

  PORTB = 0b000001;

  for(b=0;b<2;b++)

  {

    delay(1000);

    PORTB = PORTB <<1;

  }

}
