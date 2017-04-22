#include <Wire.h>  // pin A4 (SDA), A5 (SCL), SSD1311 PMOLED Controller
#define OLED_Address 0x3C
#define OLED_Command_Mode 0x80  // Control byte indicates next byte will be a command
#define OLED_Data_Mode 0x40     // Control byte indicates next byte will be data

void setup()
{
  Wire.begin();

  SSD1311_init();

  sendCommand(0x80);    // set DDRAM location 00h
  send_string("Line 1 -------------");
  sendCommand(0xA0);    // set DDRAM location 20h [next line]
  send_string("Line 2 -------------");
  sendCommand(0x80);    // set DDRAM location 40h
  send_string("Line 3 -------------");
  sendCommand(0xE0);    // set DDRAM location 60h [next line]
  send_string("Line 4 -------------");
}

void loop()
{
  // insert your code here
  // sendCommand(0x01);    // Clear Display and set DDRAM location 00h
  // ...
}

void sendData(unsigned char data)
{
  Wire.beginTransmission(OLED_Address);
  Wire.write(OLED_Data_Mode);
  Wire.write(data);
  Wire.endTransmission();
}

void sendCommand(unsigned char command)
{
  Wire.beginTransmission(OLED_Address);
  Wire.write(OLED_Command_Mode);
  Wire.write(command);
  Wire.endTransmission();
}

void sendString(const char *OLED_string)
{
  unsigned char i = 0;
  while (OLED_string[i])
  {
    sendData(OLED_string[i]);  // send characters in string to OLED, 1 by 1
    i++;
  }
}

void SSD1311_init()
{
  delay(100);            // let SSD1311 finish internal POR
  sendCommand(0x2A);     // Function Set, set RE=1
  sendCommand(0x09);     // Extended Function Set, 5-dot, disable cursor-invert, 4-line mode
  sendCommand(0x72);     // Function Selection B
  sendData(0x03);        // Set ROM [ROM A 0x03, ROM B 0x07, ROM C 0x0B]
  sendCommand(0x79);     // set SD=1, enable OLED Command Set
  sendCommand(0x81);     // Set Contrast Control
  sendCommand(0xFF);     // default is 0x7F
  sendCommand(0x78);     // set SD=0, disable OLED Command Set
  sendCommand(0x28);     // Function Set, set RE=0
  sendCommand(0x01);     // Clear Display and set DDRAM location 00h
  sendCommand(0x0C);     // turn display ON, cursor OFF, blink OFF
}
