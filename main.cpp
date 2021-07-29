#include <iostream>
#include <KVMJP.hpp>

using namespace std;
using namespace DmN::KVM::JP;

int main(int argc, char *argv[]) {
    Java_class_file* cf = class_open("hello.class");
    int rc = class_parse(cf);
    //
    cout << "RC = " << rc << endl;
    if(CP_OK == rc)
        cout << "Всё ок!\n";
    else
        cout << "Чёт пошло по #####!\n";
}