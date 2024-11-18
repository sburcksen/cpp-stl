#include "vector.h"
#include <cstddef>
#include <iostream>

template <typename T>
void printVector(const Vector<T>& vector)
{
    for (size_t i = 0; i < vector.size(); ++i) {
        // std::cout << vector.at(i) << std::endl;
    }
}

class Test {
public:
    float x, y;

    Test(float x, float y)
        : x(x)
        , y(y)
    {
        std::cout << "Created" << std::endl;
    }

    Test(const Test& other)
    {
        x = other.x;
        y = other.y;
        std::cout << "Copied" << std::endl;
    }

    Test(Test&& other)
    {
        x = other.x;
        y = other.y;
        std::cout << "Moved" << std::endl;
    }

    ~Test()
    {
        std::cout << "Destroyed" << std::endl;
    }

    Test& operator=(const Test& other)
    {
        std::cout << "Copied 2" << std::endl;
        x = other.x;
        y = other.y;
        return *this;
    }

    Test& operator=(Test&& other)
    {
        std::cout << "Moved 2" << std::endl;
        x = other.x;
        y = other.y;
        return *this;
    }
};

int main()
{

    Vector<Test> vector;

    vector.pushBack(Test(1, 2));
    vector.pushBack(Test(3, 4));

    std::cout << "Finshed" << std::endl;
}
