#include "OCMJ4X8B.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"

uint8_t row_index = 0;

// Set builder
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

// Initialize OCMJ4X8B LCD
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

    for (uint8_t i=0; i<8; i++)
    {
        _row_pos[i] = (_char_y_size + _row_space_size) * i;
    }

    _y_pos = _row_pos[0];
}


// Write function
inline size_t OCMJ_LCD::write(uint8_t stringValue)
{
    send(stringValue);
    return 1;
}

// Send data
void OCMJ_LCD::send(uint8_t data)
{
    if (_x_pos>19)
    {
        row_index++;
        _y_pos = _row_pos[row_index];
        //_y_pos += _char_y_size + _row_space_size;
        _x_pos = 0x04;
    }

    command(_write_command);      // Write 8x8/8x16 ASCII character initialize code
    command(_x_pos);              // X position
    command(_y_pos);              // Y position

    command(data);                // Writing data

    // Check status for next writing process
    busyStatus();

    _x_pos++;                      // Set next digit position
}

// Send command
void OCMJ_LCD::command(uint8_t command)
{
    write8bits(command);

    digitalWrite(_req_pin,HIGH);
    delayMicroseconds(10);
    digitalWrite(_req_pin,LOW);
}

// Write data as bits
void OCMJ_LCD::write8bits(uint8_t value)
{
    for (uint8_t i=0; i<8; i++) {
        digitalWrite(_data_pins[i], (value >> i) & 0x01);
    }
}


// Set cursor position
void OCMJ_LCD::setCursor(uint8_t row, uint8_t column)
{
    _x_pos = 3 + column;

    switch (row)
    {
        case 1:
            row_index = 0;
            break;
        case 2:
            row_index = 1;
            break;
        case 3:
            row_index = 2;
            break;
        case 4:
            row_index = 3;
            break;
        case 5:
            row_index = 4;
            break;
        case 6:
            row_index = 5;
            break;
        case 7:
            row_index = 6;
            break;
        case 8:
            row_index = 7;
            break;
    }

    _y_pos = _row_pos[row_index];
}


// Add space between rows
void OCMJ_LCD::rowSpacer(uint8_t space_size)
{
    if(_x_pos != 0x04)
    {
        row_index++;
        _row_pos[row_index] = _y_pos + _char_y_size + space_size;

    }
    else
    {
        _row_pos[row_index] = _y_pos + space_size;
    }
    
    for(uint8_t i=row_index+1; i<8; i++)
    {
        _row_pos[i] = _row_pos[i-1] + _char_y_size + _row_space_size;
    }

    _y_pos = _row_pos[row_index];
    _x_pos = 0x04;
}

// Add seperator between rows
void OCMJ_LCD::rowSeperator()
{
    if(_x_pos == 20) {row_index++;}

    if(_x_pos != 0x04)
    {
        row_index++;
        _y_pos += _char_y_size + _row_space_size + 1;
        _x_pos = 0x04;
        for (uint8_t i = 0x20; i < 0xA0; i++)
        {
            command(0xF2);
            command(i);
            command(_y_pos);

            // Check status for next writing process
            busyStatus();
        }
    } 
    else
    {
        _y_pos += _row_space_size + 1;
        for (uint8_t i = 0x20; i < 0xA0; i++)
        {
            command(0xF2);
            command(i);
            command(_y_pos);

            // Check status for next writing process
            busyStatus();
        }
    }

    _row_pos[row_index] = _y_pos + _row_space_size + 2;

    for(uint8_t i=row_index+1; i<8; i++)
    {
        _row_pos[i] = _row_pos[i-1] + _char_y_size + _row_space_size;
    }

    _y_pos = _row_pos[row_index];
}

// Check status for next writing process
void OCMJ_LCD::busyStatus()
{
    _busy_status = digitalRead(_busy_pin);

    while(_busy_status)
    {
        _busy_status = digitalRead(_busy_pin);
    }
}


// Clear all screen
void OCMJ_LCD::clear()
{
    command(0xF4);

    // Check status for next writing process
    uint8_t busyStatus = digitalRead(_busy_pin);

    while(busyStatus)
    {
        busyStatus = digitalRead(_busy_pin);
    }

    _x_pos = 0x04;
    _y_pos = 0x00;
}