// DS1302 CLK/SCLK --> 5 
// DS1302 DAT/IO --> 4 
// DS1302 RST/CE --> 2 
// DS1302 VCC --> 3.3v - 5v 
// DS1302 GND --> GND 

#include <ThreeWire.h>
#include <RtcDS1302.h>
#define LED 7

ThreeWire myWire(4,5,2); // IO, SCLK, CE 
RtcDS1302<ThreeWire> Rtc(myWire); 

void printDateTime(const RtcDateTime& dt)
{ 
 Serial.print(dt.Year(), DEC); 
 Serial.print('/'); 
 Serial.print(dt.Month(), DEC); 
 Serial.print('/'); 
 Serial.print(dt.Day(), DEC); 
 Serial.print(' '); 
 Serial.print(dt.Hour(), DEC); 
 Serial.print(':'); 
 Serial.print(dt.Minute(), DEC); 
 Serial.print(':'); 
 Serial.print(dt.Second(), DEC); 
 Serial.println(); 
 Serial.print("Total Seconds since 1/1/2000 : "); 
 Serial.print(dt.TotalSeconds()); 
 Serial.println();
}


RtcDateTime start_instant; 

void setup() 
{ 
  pinMode(7, HIGH);
  digitalWrite(7, LOW);
  
  Serial.begin(9600); 
   Serial.println("start");
  Rtc.Begin(); 
  RtcDateTime setting_time(2020,2,2,23,31,10); 
  // year, month, dayofMonth, hour, minute, second 
  printDateTime(setting_time); 
  //Try to comment This line 
  Rtc.SetDateTime(setting_time); 
  start_instant = Rtc.GetDateTime().TotalSeconds();
} 

void loop() 
{ 
  
  RtcDateTime now = Rtc.GetDateTime(); 
  auto current = now.TotalSeconds();
 
  if(current - start_instant <= (60*2)) 
  {
    printDateTime(now);
    digitalWrite(7, current % 2);
  }
  else 
  {
   Serial.println("stop");
  }
  delay(1000); 
}
