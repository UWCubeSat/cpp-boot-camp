#include "meep.hpp"
#include "keep.hpp"

int main() {
    int times = 4;
    meep(times);
    keep(times);
    keep(times);
    meep(times);
    return 0;
}