
// STL includes
#include <stdio.h>
#include <iostream>
#include <string>

#include <external\hash\hash.h>

#include "static_hash.h"

int main(int argc, void** argv) {

    std::string str;
    uint32_t hash = 0;

    while (true) {
        printf("input: ");
        std::getline(std::cin, str);

        if (str.empty()) break;
        hash = gea::g_hash32(str.c_str(), str.length());

        printf(" == 0x%08x\n", hash);
    }

    return 0;
}
