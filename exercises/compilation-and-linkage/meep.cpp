#include "meep.hpp"


void meep(int times) {
    for(int i = 0; i < times; i++) {
        std::cout << "Meep! ";
    }
    std::cout << std::endl;
}