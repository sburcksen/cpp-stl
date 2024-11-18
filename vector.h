#include <cassert>
#include <cstddef>
#include <iostream>
#include <new>
#include <ostream>
#include <utility>

template <typename T>
class Vector {
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
        operator delete(m_Data, m_Capacity * sizeof(T));
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
        if (m_Capacity <= m_Size) {
            reAllocate(m_Capacity > 0 ? m_Capacity * 2 : 2);
        }

        new (&m_Data[m_Size]) T(std::forward<Args>(args)...);
        return m_Data[m_Size++];
    }

    void insert(const T& element)
    {
    }

    void insert(T&& element)
    {
    }

    void popBack()
    {
        if (m_Size > 0) {
            m_Data[--m_Size].~T();
        }
    }

    void clear()
    {
        for (size_t i = 0; i < m_Size; ++i) {
            m_Data[i].~T();
        }

        m_Size = 0;
    }

    //-------------------------------------------
    // Element access

    T& operator[](const size_t index)
    {
        assert(index < m_Size);
        return m_Data[index];
    }

    const T& operator[](const size_t index) const
    {
        assert(index < m_Size);
        return m_Data[index];
    }

    T& at(const size_t index)
    {
        assert(index < m_Size);
        return m_Data[index];
    }

    const T& at(const size_t index) const
    {
        assert(index < m_Size);
        return m_Data[index];
    }

    T& front()
    {
        assert(!empty());
        return m_Data[0];
    }

    const T& front() const
    {
        assert(!empty());
        return m_Data[0];
    }

    T& back()
    {
        assert(!empty());
        return m_Data[m_Size - 1];
    }

    const T& back() const
    {
        assert(!empty());
        return m_Data[m_Size - 1];
    }

    //-------------------------------------------
    // Capacity

    void reserve(const size_t capacity)
    {
        if (capacity > m_Capacity) {
            reAllocate(capacity);
        }
    }

    void shrinkToFit()
    {
        if (m_Capacity > m_Size) {
            reAllocate(m_Size);
        }
    }

    const size_t size() const { return m_Size; }

    const size_t capacity() const { return m_Capacity; }

    const bool empty() const { return m_Size == 0; }

private:
    void reAllocate(size_t capacity)
    {
        std::cout << "ReAllocate with new capacity " << capacity << std::endl;
        T* newData = (T*)operator new(capacity * sizeof(T));

        for (int i = 0; i < m_Size; ++i) {
            new (&newData[i]) T(std::move(m_Data[i]));
            m_Data[i].~T();
        }

        operator delete(m_Data, m_Capacity * sizeof(T));
        m_Data = newData;
        m_Capacity = capacity;
    }

private:
    T* m_Data = nullptr;

    size_t m_Size = 0;
    size_t m_Capacity = 0;
};
