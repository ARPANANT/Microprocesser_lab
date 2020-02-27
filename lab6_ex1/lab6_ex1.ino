#include <SPI.h> 
#include <Wire.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 
#define SCREEN_WIDTH 128 // OLED display width, in pixels 
#define SCREEN_HEIGHT 64 // OLED display height, in pixels 
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins) 
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin) 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 

void setup() 
{ 
  Serial.begin(9600);
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //initialize I2C addr 0x3c 
  display.clearDisplay(); // clears the screen and buffer 
  display.drawPixel(127, 63, WHITE); 
  display.drawCircle(64, 20, 10, WHITE); 
  display.drawCircle(64, 32, 10, WHITE);  
  display.setTextSize(1); 
  display.setTextColor(WHITE); 
  display.setCursor(0,0); 
  display.setTextColor(WHITE, BLACK); 
  display.display(); 
} 
 
void loop() 
{ 
  Serial.println(digitalRead(A0));
  if((digitalRead(A0)==LOW)&(digitalRead(A1)==LOW))
  {
    display.clearDisplay();
    display.fillCircle(32, 32, 10, WHITE);
    display.fillCircle(98, 32, 10, WHITE);
    display.display();
  }

  if((digitalRead(A0)==HIGH)&(digitalRead(A1)==LOW))
  {
    display.clearDisplay();
    display.fillCircle(32, 32, 10, WHITE);
    display.drawCircle(98, 32, 10, WHITE);
    display.display();
   }

   if((digitalRead(A0)==LOW)&(digitalRead(A1)==HIGH))
   {
    display.clearDisplay();
    display.drawCircle(32, 32, 10, WHITE);
    display.fillCircle(98, 32, 10, WHITE);
    display.display();
   }

   if((digitalRead(A0)==HIGH)&(digitalRead(A1)==HIGH))
   {
    display.clearDisplay();
    display.drawCircle(32, 32, 10, WHITE);
    display.drawCircle(98, 32, 10, WHITE);
    display.display();
   }
}
