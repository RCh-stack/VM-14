#include "Registers.h"
#include "Memory.cpp"
#include "Processor.cpp"
#include "Command.cpp"

//------------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    system("chcp 1251 > nul");
    cout << "VM-14. Developed: Chuprey Roman. ASTU, 2020." << endl;
    Registers registers;
    Memory memory;
    Processor p(&memory, &registers);
    string name;
    cout << "Enter file name: " << endl;
    cin >> name;
    p.start(name);
    system("pause");
    return 0;
}
