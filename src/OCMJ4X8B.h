#ifndef OCMJ4X8B_H
#define OCMJ4X8B_H

#include <inttypes.h>
#include "Print.h"

class OCMJ_LCD : public Print
{
    public:
        OCMJ_LCD(uint8_t D0, uint8_t D1, uint8_t D2, uint8_t D3, uint8_t D4, uint8_t D5, uint8_t D6, uint8_t D7, uint8_t REQ, uint8_t BUSY, uint8_t RESET);
        
        void init(char char_size[] = "8x8", uint8_t row_space_size = 0);
        
        virtual size_t write(uint8_t);
        void send(uint8_t);
        void command(uint8_t);

        void setCursor(uint8_t row, uint8_t column);
        void rowSpacer(uint8_t space_size);
        void rowSeperator();
        void clear();

        using Print::write;
    private:
        uint8_t _req_pin;
        uint8_t _busy_pin;
        uint8_t _reset_pin;
        uint8_t _data_pins[8];

        void write8bits(uint8_t);
        void busyStatus();

        uint8_t _x_pos = 0x04;
        uint8_t _y_pos = 0x00;

        uint8_t _row_pos[8];
        uint8_t _active_row = 0;

        uint8_t _char_y_size = 8;
        uint8_t _row_space_size = 0;

        uint8_t _write_command = 0xF1;
        uint8_t _busy_status;
};

#endif