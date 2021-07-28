#include <DmNSTD.hpp>

namespace DmN::std {
    inline unsigned int trans_two_byte(const unsigned char* bytes) {
        return ((bytes[0] & 0x1f) << 6) + (bytes[1] & 0x3f);
    }

    inline unsigned int trans_three_byte(const unsigned char* bytes){
        return ((bytes[0] & 0xf) << 12) + ((bytes[1] & 0x3f) << 6 ) + (bytes[2] & 0x3f);
    }

    inline unsigned int trans_six_bytes(const unsigned char* bytes){
        return 0x10000 + (((bytes[1] & 0x0f << 16) + ((bytes[2] & 0x3f) << 10) + (bytes[4] & 0x0f)) << 6) + (bytes[5] & 0x3f);
    }

    inline wchar_t trans_two_bytes_wchar(uint8_t byte1, uint8_t byte2){
        return ((byte1 & 0x1f) << 6) + (byte2 & 0x3f);
    }

    inline wchar_t trans_three_bytes_wchar(uint8_t byte1, uint8_t byte2, uint8_t byte3) {
        return ((byte1 & 0xf) << 12) + ((byte2 & 0x3f) << 6 ) + (byte3 & 0x3f);
    }

    inline wchar_t trans_six_bytes_wchar(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4, uint8_t byte5, uint8_t byte6){
        return 0x10000 + (((byte2 & 0x0f << 16) + ((byte3 & 0x3f) << 10) + (byte5 & 0x0f)) << 6) + (byte6 & 0x3f);
    }

    inline int byte_position_bit(unsigned char byte,int position) {
        int oc=1;
        oc<<=position;
        return (oc&byte)!=0?1:0;
    }

    inline int get_utf_8_width(unsigned char byte) {
        int bit_val = -1;
        // 0开头的则位1个字节宽的的UTF8
        bit_val = byte_position_bit(byte, 7);
        if (0 == bit_val) {
            return 1;
        }
        bit_val = byte_position_bit(byte, 6);
        if (1 != bit_val) {
            // 格式异常
            return -1;
        }
        // 110开头的则位2个字节宽度的UTF8
        bit_val = byte_position_bit(byte, 5);
        if (0 == bit_val) {
            // 2个字节
            return 2;
        }

        // 11101101格式的则位6个字节的补充字符
        if (0xED == byte) {
            return 6;
        }

        // 1110开头的则为3个字节宽度的UTF8
        if (0 == byte_position_bit(byte, 4)) {
            return 3;
        }

        return 0;
    }
}