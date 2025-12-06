#include "MemoryRiver.hpp"
#include <iostream>
int main()
{
    MemoryRiver<double> file;
    file.initialise("Cyrene");
    double x;
    file.read(x, 0);
    std::cout << x;
    return 0;
}