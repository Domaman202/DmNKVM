#include <JavaParser.hpp>

using namespace DmN::KVM::JP;

int main(int argc, char *argv[]) {
    Java_class_file* cf = class_open("hello.class");
    int rc = class_parse(cf);
    //
    printf("RC = %d\n",rc);
    if(CP_OK == rc)
        printf("Всё ок!\n");
    else
        printf("Чёт пошло по #####!\n");
}