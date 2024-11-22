#include "vector.h"
#include <iostream>

int main()
{

    Vector<int> vector;

    vector.emplaceBack(1);
    vector.emplaceBack(2);
    vector.emplaceBack(3);
    vector.emplaceBack(4);
    vector.emplaceBack(5);
    vector.emplaceBack(6);

    for (auto& value : vector) {
        std::cout << value << std::endl;
    }

    std::cout << std::endl;

    for (Vector<int>::Iterator it = vector.begin(); it != vector.end(); ++it) {
        std::cout << *it << std::endl;
    }

    std::cout << std::endl;

    Vector<int>::Iterator iterator = vector.begin();

    std::cout << iterator[0] << std::endl;
    iterator += 2;
    std::cout << iterator[0] << std::endl;

    auto secondIt = iterator - 1;

    std::cout << *secondIt << std::endl;

    std::cout << (secondIt < iterator) << std::endl;
    std::cout << (secondIt > iterator) << std::endl;

    std::cout << (secondIt == (iterator - 1)) << std::endl;

    std::cout << "Finshed" << std::endl;
}
