#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 
String AA;
void setup() 
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.clearDisplay(); 
}

void loop() 
{
  int VR = analogRead(A0);
  String VRSGU = String(VR);
  Serial.println(VR);
  display.clearDisplay();
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(2);
  display.setCursor(10,0); 
  String KJ = Serial.readString();
  display.print(KJ);
  display.display();
  delay(500);
}
