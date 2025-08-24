#include "utility.h"
#include <algorithm>

template <typename Array>
class ArrayIterator {
public:
    using valueType = typename Array::valueType;

public:
    ArrayIterator(valueType* pointer)
        : m_pointer(pointer)
    {
    }

public:
    valueType& operator*() const
    {
        return *m_pointer;
    }

    valueType* operator->() const
    {
        return m_pointer;
    }

    ArrayIterator& operator++()
    {
        ++m_pointer;
        return *this;
    }

    ArrayIterator operator++(int)
    {
        ArrayIterator copy = *this;
        ++m_pointer;
        return copy;
    }

    ArrayIterator& operator--()
    {
        --m_pointer;
        return *this;
    }

    ArrayIterator operator--(int)
    {
        ArrayIterator copy = *this;
        --m_pointer;
        return copy;
    }

    ArrayIterator& operator+=(const int offset)
    {
        m_pointer += offset;
        return *this;
    }

    ArrayIterator operator+(const int offset) const
    {
        ArrayIterator copy = *this;
        copy += offset;
        return copy;
    }

    ArrayIterator& operator-=(const int offset)
    {
        m_pointer -= offset;
        return *this;
    }

    ArrayIterator operator-(const int offset) const
    {
        ArrayIterator copy = *this;
        copy -= offset;
        return copy;
    }

    valueType& operator[](const int offset) const
    {
        return *(*this + offset);
    }

    bool operator==(const ArrayIterator& other) const
    {
        return m_pointer == other.m_pointer;
    }

    bool operator!=(const ArrayIterator& other) const
    {
        return !(*this == other);
    }

    bool operator<(const ArrayIterator& other) const
    {
        return m_pointer < other.m_pointer;
    }

    bool operator>(const ArrayIterator& other) const
    {
        return other < *this;
    }

    bool operator<=(const ArrayIterator& other) const
    {
        return !(other < *this);
    }

    bool operator>=(const ArrayIterator& other) const
    {
        return !(*this < other);
    }

private:
    valueType* m_pointer;
};

template <typename T, sizeType S>
class Array {
public:
    using valueType = T;
    using sizeType = sizeType;
    using differenceType = differenceType;
    using reference = valueType&;
    using constReference = const valueType&;
    using pointer = valueType*;
    using constPointer = const valueType*;
    using iterator = ArrayIterator<Array<T, S>>;

public:
    //-------------------------------------------
    // Element access
    reference at(sizeType index)
    {
        return m_data[index];
    }

    constReference at(sizeType index) const
    {
        return m_data[index];
    }

    reference operator[](sizeType index)
    {
        return this->at(index);
    }

    constReference operator[](sizeType index) const
    {
        return this->at(index);
    }

    reference front() { return m_data[0]; }

    constReference front() const { return m_data[0]; }

    reference back() { return m_data[S - 1]; }

    constReference back() const { return m_data[S - 1]; }

    T* data() { return m_data; }

    const T* data() const { return m_data; }

    //-------------------------------------------
    // Iterators
    iterator begin()
    {
        return iterator(m_data);
    }

    iterator end()
    {
        return iterator(m_data + S);
    }

    //-------------------------------------------
    // Capacity
    constexpr bool empty() const { return S == 0; }

    constexpr sizeType size() const { return S; }

    constexpr sizeType maxSize() const { return S; }

    //-------------------------------------------
    // Operations
    void fill(const T& element)
    {
        fillWithElement(begin(), S, element);
    }

    void swap(Array& other)
    {
        iterator it1 = begin();
        iterator it2 = other.begin();
        for (; it1 != end(); ++it1, ++it2) {
            valueType tmp = *it1;
            *it1 = *it2;
            *it2 = tmp;
        }
    }

public:
    T m_data[S];
};

template <typename T, sizeType S>
bool operator==(const Array<T, S>& left, const Array<T, S>& right)
{
    return equal(left.begin(), left.end(), right.begin());
}

template <sizeType I, typename T, sizeType S>
sizeType& get(Array<T, S>& array)
{
    return array.at(I);
}

template <sizeType I, typename T, sizeType S>
sizeType&& get(Array<T, S>& array)
{
    return std::move(get<I>(array));
}

template <sizeType I, typename T, sizeType S>
const sizeType& get(Array<T, S>& array)
{
    return array.at(I);
}

template <sizeType I, typename T, sizeType S>
const sizeType&& get(Array<T, S>& array)
{
    return std::move(get<I>(array));
}

template <typename T, sizeType S>
void swap(Array<T, S>& left, Array<T, S>& right)
{
    left.swap(right);
}
