#include "OCMJ4X8B.h"

OCMJ_LCD LCD(3,4,5,6,7,8,9,10,11,12,13);

void setup(){
    LCD.init("8x8",1);
    // LCD.print("__CH1__  __CH2__");
    // LCD.print("V:15.1V  V:10.0V");
    // LCD.print("I:1.2A   I:2.4A ");
    // LCD.print("P:8.3W   P:24.0W");
    LCD.rowSeperator();
    // LCD.print("T:25.1C  CH1:!SC");
    // LCD.print("F:ACTIVE CH2: OK");

    //LCD.write(0x80);
}

void loop(){

}
