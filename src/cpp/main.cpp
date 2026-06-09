#include "core.h"

#include <iostream>

int main() {
    const long long left = 40;
    const long long right = 2;

    std::cout << "Bolun native build" << '\n';
    std::cout << bolun_language_policy() << '\n';
    std::cout << "C result: " << bolun_c_add(left, right) << '\n';
    std::cout << "Assembly result: " << bolun_asm_add(left, right) << '\n';

    return 0;
}
