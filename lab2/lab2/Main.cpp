#include <iostream>
#include <string>
#include "World.h"
using namespace Life;
int main()
{
    World world("file.txt");
    world.print_world();

    int iterations;
    std::cout << "Enter the number of iterations: ";
    std::cin >> iterations;

    for (int i = 0; i < iterations; ++i) {
        world.next_generation();
        world.print_world();
        if (world.is_stable()) {
            std::cout << "World is stable. Exiting." << std::endl;
            return 0;
        }
    }


    return 0;
}
