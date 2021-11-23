#include <iostream>

#include "hw.h"

int main (int, char **) {
    custom_map factorial_map;
    factorial_map.fill_custom_map();
    factorial_map.print_custom_map();
    factorial_map.add_next_element();
    factorial_map.print_custom_map();
    return 0;
}
