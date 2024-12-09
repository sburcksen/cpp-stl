#include "stl/include/array.h"
// #include "stl/include/vector.h"
#include <iostream>
#include <string>

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

    std::cout << "Array::fill test" << std::endl;

    Array<int, 5> array2;
    array2.fill(123);

    for (int value : array2) {
        std::cout << value << std::endl;
    }

    std::cout << "Array::swap test" << std::endl;
    Array<std::string, 3> arraySwap1 { "a", "b", "c" }, arraySwap2 { "d", "e", "f" };
    Array<std::string, 4> arraySwap3 { "g", "h", "i", "j" };
    Array<std::string, 2> arraySwap4 { "g", "h" };

    arraySwap1.swap(arraySwap2);
    for (auto value : arraySwap1) {
        std::cout << value << std::endl;
    }
    for (auto value : arraySwap2) {
        std::cout << value << std::endl;
    }
}
