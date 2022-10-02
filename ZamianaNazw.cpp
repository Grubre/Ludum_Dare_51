#include <iostream>
#include <string>
#include <iomanip>

int main(int argc, char* argv[])
{
    for(int i = 0; i < std::stoi(argv[2]); i++)
    {
        std::cout << "mv tile" << std::setw(3) << std::setfill('0') << i << ".png " << argv[1] << "_" << i + 1 << ".png && ";
    }
    std::cout << std::endl;
};
