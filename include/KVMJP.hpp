//#ifndef DMN_KVM_NO_USE_PRAGMA
//#pragma once
//#endif /* DMN_KVM_NO_USE_PRAGMA */
//#ifndef DMN_KVM_JP_HPP
//#define DMN_KVM_JP_HPP
//
//#include "KVMNameble.hpp"
//#include "KVMAlloc.hpp"
//#include "SDmNL.hpp"
//#include <cstring>
//#include <tuple>
//
//using namespace DmN::SDL::Byte;
//using namespace DmN::SDL::Pairs;
//
//namespace DmN::KVM::JP {
//    /// Пул констант
//    DMN_KVM_E struct ConstantPool {
//        u1 tag = 0;
//        union {
//            SI_t SID; // String ID (Строка, Enum/Структура/Класс, Дескриптор, Имя)
//            CI_t CID; // Class ID (ID класса)
//            struct {
//                SI_t NID = 0; // Name ID (Имя)
//                CI_t CID = 0; // Class ID (ID класса)
//            } FMI; // Field, MethodRef, InterfaceMethodRef
//            // Циферки xD
//            int8_t int8;
//            uint8_t uint8;
//            int16_t int16;
//            uint16_t uint16;
//            int32_t int32 = 0; /* Default Value */
//            uint32_t uint32;
//            int64_t int64;
//            uint64_t uint64;
//            float float_;
//            double double_;
//        };
//    };
//
//    /*!
//     * Читает весь файл в одну строку
//     * @param file файл который нужно считать
//     * @return Итоговая строка
//     */
//    char *readString(FILE *file);
//
//    Triple<u2, ConstantPool **, SS *> readConstantPool(FILE *file);
//}
//    char *readString(FILE *file) {
//        u2 length = u2Read(file);
//        char *bytes = new char[length];
//        for (int j = 0; j < length; j++)
//            std::memcpy(&bytes[j], reinterpret_cast<void *>(u1Read(file)), sizeof(u1));
//        return bytes;
//    }
//
//    Triple<u2, ConstantPool **, SS *> readConstantPool(FILE *file) {
//        u2 cpc = u2Read(file);
//        //
//        ConstantPool *pools[cpc];
//        auto *lp = new ConstantPool{};
//        //
//        SS *strings = DmN::KVM::Alloc::allocDSS(nullptr, 0);
//        //
//        for (u2 i = 0; i < cpc; i++) {
//            lp->tag = u1Read(file);
//
//            switch (lp->tag) {
//                // Constant Class
//                case 7:
//                    lp->SID = (SI_t) u2Read(file);
//                    break;
//                    // Constant FieldRef/MethodRef/InterfaceMethodRef
//                case 9:
//                case 10:
//                case 11:
//                    lp->FMI.CID = (CI_t) u2Read(file);
//                    lp->FMI.NID = (SI_t) u2Read(file);
//                    break;
//                    // Constant String
//                case 8:
//                    lp->SID = (SI_t) u2Read(file);
//                    break;
//                    // Constant Int
//                case 3:
//                    std::memcpy(&lp->int32, reinterpret_cast<void *>(u4Read(file)), sizeof(u4));
//                    break;
//                    // Constant Float
//                case 4:
//                    std::memcpy(&lp->float_, reinterpret_cast<void *>(u4Read(file)), sizeof(u4));
//                    break;
//                    // Constant Long
//                case 5:
//                    std::memcpy(&lp->int64, reinterpret_cast<void *>(u8Read(file)), sizeof(u8));
//                    break;
//                    // Constant Double
//                case 6:
//                    std::memcpy(&lp->double_, reinterpret_cast<void *>(u8Read(file)), sizeof(u8));
//                    break;
//                    // Constant Name
//                case 12:
//                    lp->SID = strings->add(strcat(readString(file), readString(file)));
//                    break;
//                    // Constant String
//                case 1:
//                    lp->SID = strings->add(readString(file));
//                    break;
//            }
//
//            pools[i] = lp;
//            lp = new ConstantPool{};
//        }
//        //
//        return {cpc, pools, strings};
//    }
//
//#endif /* DMN_KVM_JP_HPP */