#include "array.h"
#include "vector.h"
#include <iostream>

int main()
{

    Array<int, 5> array;

    for (int i = 0; i < array.size(); i++) {
        array.at(i) = i;
        std::cout << array[i] << std::endl;
    }

    for (Array<int, 5>::iterator it = array.begin(); it < array.end(); ++it) {
        std::cout << *it << std::endl;
    }

    for (int value : array) {
        std::cout << value << std::endl;
    }

    std::cout << std::endl;

    std::cout << (array.end() - 3)[1] << std::endl;

    std::cout << (array.end() < array.begin()) << std::endl;
    std::cout << (array.end() > array.begin()) << std::endl;
    std::cout << (array.end() != array.begin()) << std::endl;
}
