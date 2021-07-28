#include <JavaParser.hpp>

using namespace DmN::KVM::JP;

int main(int argc, char *argv[]) {
    CLASSFILE* cf = class_open("hello.class");
    int rc = class_parse(cf);
    //
    printf("RC = %d\n",rc);
    if(CP_OK == rc)
        printf("Всё ок!\n");
    else
        printf("Чёт пошло по #####!\n");
    return 0;
}