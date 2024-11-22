#include <cassert>
#include <cstddef>
#include <iostream>
#include <new>
#include <ostream>

template <typename Vector>
class VectorIterator {
public:
    using valueType = typename Vector::valueType;
    using pointerType = valueType*;

public:
    VectorIterator(pointerType pointer)
        : m_pointer(pointer)
    {
    }

public:
    VectorIterator& operator++()
    {
        ++m_pointer;
        return *this;
    }

    VectorIterator& operator++(int)
    {
        VectorIterator copy = *this;
        ++(*this);
        return copy;
    }

    VectorIterator& operator--()
    {
        --m_pointer;
        return *this;
    }

    VectorIterator& operator--(int)
    {
        VectorIterator copy = *this;
        --(*this);
        return copy;
    }

    VectorIterator& operator+=(const int offset)
    {
        m_pointer += offset;
        return *this;
    }

    VectorIterator operator+(const int offset) const
    {
        VectorIterator copy = *this;
        copy += offset;
        return copy;
    }

    VectorIterator& operator-=(const int offset)
    {
        m_pointer -= offset;
        return *this;
    }

    VectorIterator operator-(const int offset) const
    {
        VectorIterator copy = *this;
        copy -= offset;
        return copy;
    }

    valueType& operator*() const
    {
        return *m_pointer;
    }

    valueType& operator[](const int offset) const
    {
        return *(*this + offset);
    }

    pointerType operator->() const
    {
        return m_pointer;
    }

    bool operator==(const VectorIterator& other) const
    {
        return m_pointer == other.m_pointer;
    }

    bool operator!=(const VectorIterator& other) const
    {
        return !(*this == other.m_pointer);
    }

    bool operator<(const VectorIterator& other) const
    {
        return m_pointer < other.m_pointer;
    }

    bool operator>(const VectorIterator& other) const
    {
        return other < *this;
    }

    bool operator<=(const VectorIterator& other) const
    {
        return !(other < *this);
    }

    bool operator>=(const VectorIterator& other) const
    {
        return !(*this < other);
    }

private:
    pointerType m_pointer;
};

template <typename T>
class Vector {
public:
    using valueType = T;
    using Iterator = VectorIterator<Vector<T>>;

public:
    Vector()
    {
        reAllocate(2);
    }

    Vector(const size_t capacity)
    {
        reAllocate(capacity);
    }

    ~Vector()
    {
        std::cout << "~Vector()" << std::endl;
        clear();
        operator delete(m_data, m_capacity * sizeof(T));
    }

public:
    //-------------------------------------------
    // Modifiers
    void pushBack(const T& element)
    {
        emplaceBack(element);
    }

    void pushBack(T&& element)
    {
        emplaceBack(std::move(element));
    }

    template <typename... Args>
    T& emplaceBack(Args&&... args)
    {
        if (m_capacity <= m_size) {
            reAllocate(m_capacity > 0 ? m_capacity * 2 : 2);
        }

        new (&m_data[m_size]) T(std::forward<Args>(args)...);
        return m_data[m_size++];
    }

    void insert(const T& element)
    {
    }

    void insert(T&& element)
    {
    }

    void popBack()
    {
        if (m_size > 0) {
            m_data[--m_size].~T();
        }
    }

    void clear()
    {
        for (size_t i = 0; i < m_size; ++i) {
            m_data[i].~T();
        }

        m_size = 0;
    }

    //-------------------------------------------
    // Element access
    T& operator[](const size_t index)
    {
        assert(index < m_size);
        return m_data[index];
    }

    const T& operator[](const size_t index) const
    {
        assert(index < m_size);
        return m_data[index];
    }

    T& at(const size_t index)
    {
        assert(index < m_size);
        return m_data[index];
    }

    const T& at(const size_t index) const
    {
        assert(index < m_size);
        return m_data[index];
    }

    T& front()
    {
        assert(!empty());
        return m_data[0];
    }

    const T& front() const
    {
        assert(!empty());
        return m_data[0];
    }

    T& back()
    {
        assert(!empty());
        return m_data[m_size - 1];
    }

    const T& back() const
    {
        assert(!empty());
        return m_data[m_size - 1];
    }

    //-------------------------------------------
    // Capacity
    void reserve(const size_t capacity)
    {
        if (capacity > m_capacity) {
            reAllocate(capacity);
        }
    }

    void shrinkToFit()
    {
        if (m_capacity > m_size) {
            reAllocate(m_size);
        }
    }

    const size_t size() const { return m_size; }

    const size_t capacity() const { return m_capacity; }

    const bool empty() const { return m_size == 0; }

    //-------------------------------------------
    // Iterators
    Iterator begin()
    {
        return Iterator(m_data);
    }

    Iterator end()
    {
        return Iterator(m_data + m_size);
    }

private:
    void reAllocate(size_t capacity)
    {
        std::cout << "ReAllocate with new capacity " << capacity << std::endl;
        T* newData = (T*)operator new(capacity * sizeof(T));

        for (int i = 0; i < m_size; ++i) {
            new (&newData[i]) T(std::move(m_data[i]));
            m_data[i].~T();
        }

        operator delete(m_data, m_capacity * sizeof(T));
        m_data = newData;
        m_capacity = capacity;
    }

private:
    T* m_data = nullptr;

    size_t m_size = 0;
    size_t m_capacity = 0;
};
