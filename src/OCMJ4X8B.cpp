#include "OCMJ4X8B.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"


OCMJ_LCD::OCMJ_LCD(uint8_t D0, uint8_t D1, uint8_t D2, uint8_t D3, uint8_t D4, uint8_t D5, uint8_t D6, uint8_t D7, uint8_t REQ, uint8_t BUSY, uint8_t RESET)
{
    _req_pin = REQ;
    _busy_pin = BUSY;
    _reset_pin = RESET;

    _data_pins[0] = D0;
    _data_pins[1] = D1;
    _data_pins[2] = D2;
    _data_pins[3] = D3;
    _data_pins[4] = D4;
    _data_pins[5] = D5;
    _data_pins[6] = D6;
    _data_pins[7] = D7;
}

//Initialize OCMJ4X8B LCD
void OCMJ_LCD::init(char char_size[] = "8x8", uint8_t row_space_size = 0)
{
    // Set Data Pins Mode
    for (uint8_t i=0; i<8; i++)
    {
        pinMode(_data_pins[i],OUTPUT);
    }

    //Set Function Pins Mode
    pinMode(_req_pin,OUTPUT);         // Request  -> H:Data input, L:Waiting for BUSY signal
    pinMode(_busy_pin,INPUT);         // Response -> H:Busy, L:Ready for data input
    pinMode(_reset_pin,OUTPUT);       // For RESET send 0 (active low)

    digitalWrite(_reset_pin,LOW);
    delay(100);
    digitalWrite(_reset_pin,HIGH);

    digitalWrite(_req_pin,LOW);       // Set L for first data request
    delay(100);

    // Set character properties
    if(char_size == "8x8")
    {
        _char_y_size = 8;
        _write_command = 0xF1;
    }
    else if (char_size =="8x16")
    {
        _char_y_size = 16;
        _write_command = 0xF9;
    }

    _row_space_size = row_space_size;
}

void OCMJ_LCD::print(char stringValue[])
{
    for (uint16_t i=0; i<strlen(stringValue); i++)
    {
        write(stringValue[i]);
    }
}

void OCMJ_LCD::write(uint8_t data)
{
    if (_x_pos>19)
    {
        _y_pos += _char_y_size + _row_space_size;
        _x_pos = 0x04;
    }

    command(_write_command);      // Write 8x8/8x16 ASCII character initialize code
    command(_x_pos);              // X position
    command(_y_pos);              // Y position

    command(data);      // Writing data

    // Check status for next writing process
    uint8_t busyStatus = digitalRead(_busy_pin);

    while(busyStatus)
    {
        busyStatus = digitalRead(_busy_pin);
    }

    _x_pos++;
}


void OCMJ_LCD::command(uint8_t command)
{
    write8bits(command);

    digitalWrite(_req_pin,HIGH);
    delayMicroseconds(10);
    digitalWrite(_req_pin,LOW);
    delayMicroseconds(10);
}

void OCMJ_LCD::write8bits(uint8_t value)
{
    for (uint8_t i=0; i<8; i++) {
        digitalWrite(_data_pins[i], (value >> i) & 0x01);
    }
}


// Set cursor position
void OCMJ_LCD::cursor(uint8_t row, uint8_t column)
{
    _x_pos = 3 + column;

    if (row == 1)
    {
        _y_pos = 0;
    }
    else
    {
        _y_pos = (_char_y_size + _row_space_size) * row;
    }
}


// Add space for rows
void OCMJ_LCD::addSpaceRows(uint8_t space_size)
{
    _y_pos += space_size;
}

/*TODO*/
void OCMJ_LCD::rowSeperator()
{
    for (uint8_t i = 0x20; i < 0xA0; i++)
    {
        command(0xF2);
        command(i);
        command(0x00);

        // Check status for next writing process
        uint8_t busyStatus = digitalRead(_busy_pin);

        while(busyStatus)
        {
            busyStatus = digitalRead(_busy_pin);
        }
    }
}



void OCMJ_LCD::clear()
{
    command(0xF4);

    // Check status for next writing process
    uint8_t busyStatus = digitalRead(_busy_pin);

    while(busyStatus)
    {
        busyStatus = digitalRead(_busy_pin);
    }
}
