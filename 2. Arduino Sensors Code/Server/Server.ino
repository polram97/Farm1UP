/*---------------------
Server Section
-----------------------*/
//LORA libraries and display
#include <SPI.h>
#include <RH_RF95.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMonoBold12pt7b.h>

RH_RF95 rf95;
int led = 13; //display pin
unsigned long int millisBefore; 
int turn = 0;
int h, t; //humidity and temperature variables
#define SCREEN_WIDTH 128 // Display width in pixels
#define SCREEN_HEIGHT 32 // Long display in pixels
//Statement for SSD1306 display connected to I2C (pines SDA, SCL)
#define OLED_RESET     -1 // Reset pin o -1 if pin share
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  while (!Serial) ; //Wait for the port to be available
  if (!rf95.init())
    Serial.println("Inicio fallido");
  rf95.setFrequency(433.0);
  // SSD1306_SWITCHCAPVCC = generates screen voltage=3.3v internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    //Address 0x3D of 128x64
    Serial.println(F("SSD1306 Asignación fallida"));
    for (;;); //Does not process, infinite loop
  }
  //Clear the buffer
  display.clearDisplay();
  printText();
  delay(1500);
}
void loop()
{
  //Wait for answer
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  if (rf95.waitAvailableTimeout(500)) //wait 500 ms
  {
    if (rf95.recv(buf, &len))//Receive data in buffer
    {
      Serial.print("Recibe del server: ");
      Serial.println((char*)buf);
      String dataTotal = (char*)buf;
      Serial.println(dataTotal);
      explode(dataTotal);
    }
    else
    {
      Serial.println("Fallo en recepción");
    }
  }
  //Print and clear the display
  printText();
  display.display();
  delay(300);
  display.clearDisplay();
}

void explode(String req) {
  char str[20];
  req.toCharArray(str, 20);
  char * pch;
  pch = strtok (str, "-");
  while (pch != NULL)
  {
    String sementara = pch;
    turn++;
    if (turn == 1) {
      Serial.print("Humedad : ");
      Serial.println(pch);
      h = sementara.toFloat();
    }
    if (turn == 2) {
      Serial.print("Temperatura : ");
      Serial.println(pch);
      t = sementara.toFloat();
    }
    pch = strtok (NULL, "-");
    delay(100);
  }
  turn = 0;
}
void printText() {
  //Print on display
  display.setFont(&FreeMonoBold12pt7b);
  display.setTextColor(WHITE);     //Draw white text
  display.setCursor(0, 28);     //Starts in the upper left corner
  display.print(t);
  display.drawCircle(34, 8, 3, WHITE);
  display.setCursor(40, 27);
  display.print("C");
  display.setCursor(80, 28);
  display.print(h);
  display.print("%");
}
