#include <cstddef>

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

template <typename T, std::size_t S>
class Array {
public:
    using valueType = T;
    using iterator = ArrayIterator<Array<T, S>>;

public:
    //-------------------------------------------
    // Element access
    T& at(const std::size_t index)
    {
        return m_data[index];
    }

    const T& at(const std::size_t index) const
    {
        return m_data[index];
    }

    T& operator[](const std::size_t index)
    {
        return this->at(index);
    }

    const T& operator[](const std::size_t index) const
    {
        return this->at(index);
    }

    T& front() { return m_data[0]; }

    const T& front() const { return m_data[0]; }

    T& back() { return m_data[S - 1]; }

    const T& back() const { return m_data[S - 1]; }

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

    constexpr std::size_t size() const { return S; }

    //-------------------------------------------
    // Operations
    void fill(const T& value)
    {
    }

    void swap(Array& other)
    {
    }

private:
    T m_data[S];
};
