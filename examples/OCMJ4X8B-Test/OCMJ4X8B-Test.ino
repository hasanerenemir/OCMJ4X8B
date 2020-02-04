/*
  OCMJ4X8B Library - Test

 The library works with only OCMJ4X8B LCD display.

 This sketch prints some examples to the LCD
 and shows the time.

  The circuit:
 * LCD RESET pin to digital pin 13
 * LCD BUSY pin to digital pin 12
 * LCD REQ pin to digital pin 11
 * LCD D7 pin to digital pin 10
 * LCD D6 pin to digital pin 9
 * LCD D5 pin to digital pin 8
 * LCD D4 pin to digital pin 7
 * LCD D3 pin to digital pin 6
 * LCD D2 pin to digital pin 5
 * LCD D1 pin to digital pin 4
 * LCD D0 pin to digital pin 3
 * LCD 1 (BACKLIGHT -) pin to ground
 * LCD 2 (BACKLIGHT +) pin to +5V
 * LCD 3 (VSS) pin to ground
 * LCD 4 (VCC) pin to +5V
  
   After this optional for character contrast
 * Pot-1 pin to LCD 17 (RT)
 * Pot-2 pin to LCD 18 (RT)
 * Pot-3 pin to ground

 The library created at 4 Feb 2020
 by Hasan Eren Emir.

 The library and this example code is in the
 public domain.

 https://github.com/hasanerenemir/OCMJ4X8B

*/

#include <OCMJ4X8B.h>

// Set pins
const int D0 = 3;
const int D1 = 4;
const int D2 = 5;
const int D3 = 6;
const int D4 = 7;
const int D5 = 8;
const int D6 = 9;
const int D7 = 10;
const int REQ = 11;
const int BUSY = 12;
const int RESET = 13;

// OCMJ_LCD anyName(D0,D1,D2,D3,D4,D5,D6,D7,REQ,BUSY,RESET); -> Set an object for lcd module
OCMJ_LCD LCD(D0,D1,D2,D3,D4,D5,D6,D7,REQ,BUSY,RESET);

void setup(){
    // LCD.init(character_size, row_offset_size); -> Initialize lcd module 
    LCD.init("8x8",2);

    // LCD.print("type whatever you want"); -> Print someting that whatever you want
    LCD.print("Hello World!");

    // LCD.rowSeperator(); -> Add seperator between rows
    LCD.rowSeperator();

    // LCD.rowSpacer(space_size); -> Add space between rows
    LCD.rowSpacer(2);

    LCD.print("Initialize..........");
    
    // LCD.rowSpacer(space_size); -> Add space between rows
    LCD.rowSpacer(2);
    
    // LCD.rowSeperator(); -> Add seperator between rows
    LCD.rowSeperator();

    LCD.setCursor(5,1);
    LCD.print("By: H.Eren Emir");

    delay(3000);
}

void loop(){
    // LCD.setCursor(row_number(min=1 max=16), column_number(min=1 max=8))
    LCD.setCursor(1,1);
    LCD.print("OCMJ4X8B LCD");

    LCD.setCursor(2,1);
    LCD.print("This is OCMJ4X8Blcd code.");

    LCD.setCursor(5,1);
    LCD.print("Thanks!         ");
}