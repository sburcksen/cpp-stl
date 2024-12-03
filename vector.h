#include <cassert>
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
    valueType& operator*() const
    {
        return *m_pointer;
    }

    pointerType operator->() const
    {
        return m_pointer;
    }

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

    int operator-(const VectorIterator& other) const
    {
        return m_pointer - other.m_pointer;
    }

    valueType& operator[](const int offset) const
    {
        return *(*this + offset);
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
    using iterator = VectorIterator<Vector<T>>;
    using sizeType = unsigned int;

public:
    Vector()
    {
        reallocate(2);
    }

    Vector(const sizeType capacity)
    {
        reallocate(capacity);
    }

    ~Vector()
    {
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
            reallocateForGrowth();
        }

        new (&m_data[m_size]) T(std::forward<Args>(args)...);
        return m_data[m_size++];
    }

    iterator insert(const iterator pos, const T& element)
    {
        sizeType offset = pos - begin();
        if (m_capacity <= m_size) {
            // TODO: combine reallocate and copyBackwards
            reallocateForGrowth();
        }

        iterator newPos = begin() + offset;
        for (iterator it = this->end() - 1; it >= newPos; --it) {
            *(it + 1) = *it;
        }

        *newPos = element;
        ++m_size;
        return newPos;
    }

    /*iterator insert(const iterator pos, T&& element)
    {
        std::cout << "Test" << std::endl;
    }

    iterator insert(const iterator pos, sizeType count, const T& element)
    {
    }*/

    void popBack()
    {
        if (m_size > 0) {
            m_data[--m_size].~T();
        }
    }

    /*void resize(sizeType count)
    {
    }*/

    void resize(sizeType count, const T& element)
    {
        if (count < m_size) {
            // Shrink
            while (m_size > count) {
                popBack();
            }
        } else if (count > m_size) {
            // Grow
            if (count > m_capacity) {
                reallocate(count);
            }

            for (sizeType i = 0; i < count - m_size; ++i) {
                new (&m_data[m_size + i]) T(element);
            }
            m_size = count;
        }
    }

    void clear()
    {
        for (sizeType i = 0; i < m_size; ++i) {
            m_data[i].~T();
        }

        m_size = 0;
    }

    //-------------------------------------------
    // Element access
    T& operator[](const sizeType index)
    {
        assert(index < m_size);
        return m_data[index];
    }

    const T& operator[](const sizeType index) const
    {
        assert(index < m_size);
        return m_data[index];
    }

    T& at(const sizeType index)
    {
        assert(index < m_size);
        return m_data[index];
    }

    const T& at(const sizeType index) const
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
    void reserve(const sizeType capacity)
    {
        if (capacity > m_capacity) {
            reallocate(capacity);
        }
    }

    void shrinkToFit()
    {
        if (m_capacity > m_size) {
            reallocate(m_size);
        }
    }

    const sizeType size() const { return m_size; }

    const sizeType capacity() const { return m_capacity; }

    const bool empty() const { return m_size == 0; }

    //-------------------------------------------
    // Iterators
    iterator begin()
    {
        return iterator(m_data);
    }

    iterator end()
    {
        return iterator(m_data + m_size);
    }

private:
    void reallocate(sizeType capacity)
    {
        T* newData = (T*)operator new(capacity * sizeof(T));

        for (int i = 0; i < m_size; ++i) {
            new (&newData[i]) T(std::move(m_data[i]));
            m_data[i].~T();
        }

        operator delete(m_data, m_capacity * sizeof(T));
        m_data = newData;
        m_capacity = capacity;
    }

    void reallocateForGrowth()
    {
        reallocate(m_capacity > 0 ? m_capacity * 2 : 2);
    }

private:
    T* m_data = nullptr;

    sizeType m_size = 0;
    sizeType m_capacity = 0;
};
