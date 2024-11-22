#include "vector.h"
#include <iostream>

int main()
{
    Vector<int> vector;

    vector.emplaceBack(1);
    vector.emplaceBack(2);
    vector.emplaceBack(3);
    vector.emplaceBack(4);

    for (auto& value : vector) {
        std::cout << value << std::endl;
    }

    std::cout << std::endl;

    vector.insert(vector.begin() + 3, 11);

    std::cout << std::endl;

    for (Vector<int>::iterator it = vector.begin(); it != vector.end(); ++it) {
        std::cout << *it << std::endl;
    }

    std::cout << std::endl;

    vector.resize(1, 1);
    for (auto& value : vector) {
        std::cout << value << std::endl;
    }

    std::cout << std::endl;

    vector.resize(10, 1);
    for (auto& value : vector) {
        std::cout << value << std::endl;
    }

    std::cout << "Finshed" << std::endl;
}
