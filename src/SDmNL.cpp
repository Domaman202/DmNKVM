#include <SDmNL.hpp>

namespace DmN::SDL::Byte {
        inline u1 u1Read(FILE* file) {
            return getc(file);
        }

        inline u2 u2Read(FILE* file) {
            return (u1Read(file) << 4) | u1Read(file);
        }

        inline u4 u4Read(FILE* file) {
            return (u2Read(file) << 8 | u2Read(file));
        }

        inline u8 u8Read(FILE* file) {
            return (u4Read(file) << 16 | u4Read(file));
        }
    }