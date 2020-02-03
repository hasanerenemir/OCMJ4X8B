#ifndef OCMJ4X8B_H
#define OCMJ4X8B_H

#include <inttypes.h>

class OCMJ_LCD
{
    public:
        OCMJ_LCD(uint8_t D0, uint8_t D1, uint8_t D2, uint8_t D3, uint8_t D4, uint8_t D5, uint8_t D6, uint8_t D7, uint8_t REQ, uint8_t BUSY, uint8_t RESET);
        
        void init(char char_size[] = "8x8", uint8_t row_space_size = 0);
        
        void command(uint8_t command);
        void write(uint8_t data);
        void print(char stringValue[]);

        void cursor(uint8_t row, uint8_t column);
        void addSpaceRows(uint8_t space_size);
        void rowSeperator();
        void clear();

    private:
        uint8_t _req_pin;
        uint8_t _busy_pin;
        uint8_t _reset_pin;
        uint8_t _data_pins[8];

        void write8bits(uint8_t);
        void strtoHex(char);

        uint8_t _x_pos = 0x04;
        uint8_t _y_pos = 0x00;

        uint8_t _char_y_size= 8;
        uint8_t _row_space_size = 0;

        uint8_t _write_command = 0xF1;
};

#endif