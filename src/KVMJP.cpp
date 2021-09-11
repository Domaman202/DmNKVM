#include <KVMJP.hpp>

namespace DmN::KVM::JP {
    char* readString(FILE* file) {
        u2 length = u2Read(file);
        char* bytes = new char[length];
        for (int j = 0; j < length; j++)
            memcpy(&bytes[j], u1Read(file), sizeof(u1));
        return bytes;
    }

    std::tuple<u2, ConstantPool*[], SS*> readConstantPool(FILE* file) {
        u2 cpc = u2Read(file);
        //
        ConstantPool*[cpc] pools;
        ConstantPool* lp = new ConstantPool;
        //
        SS* strings = DmN::KVM::Alloc::allocDSS(nullptr, 0);
        //
        for (u2 i = 0; i < cpc; i++) {
            lp->tag = u1Read(file);

            switch(lp->tag) {
                // Constant Class
                case 7:
                    lp->SID = (SI_t) u2Read(file);
                    break;
                    // Constant FieldRef/MethodRef/InterfaceMethodRef
                case 9:
                case 10:
                case 11:
                    lp->FMI.CID = (CI_t) u2Read(file);
                    lp->FMI.NID = (SI_t) u2Read(file);
                    break;
                    // Constant String
                case 8:
                    lp->SID = (SI_t) u2Read(file);
                    break;
                    // Constant Int
                case 3:
                    std::memcpy(&lp->int32, u4Read(file), sizeof(u4));
                    break;
                    // Constant Float
                case 4:
                    std::memcpy(&lp->float_, u4Read(file), sizeof(u4));
                    break;
                    // Constant Long
                case 5:
                    std::memcpy(&lp->int64, u8Read(file), sizeof(u8));
                    break;
                    // Constant Double
                case 6:
                    std::memcpy(&lp->double_, u8Read(file), sizeof(u8));
                    break;
                    // Constant Name
                case 12:
                    lp->SID = strings->add(strcat(readString(file), readString(file)));
                    break;
                    // Constant String
                case 1:
                    lp->SID = strings->add(readString(file));
                    break;
            }

            pools[i] = lp;
            lp = new ConstantPool;
        }
        //
        return std::make_tuple(cpc, pools, strings);
    }
}