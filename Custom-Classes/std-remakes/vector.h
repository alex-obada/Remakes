#ifndef VECTOR_
#define VECTOR_

#include <initializer_list>
#include <cstddef>
#include <stdexcept>
#include <utility>

#include "../globals.h"
#include "vector_iterator.h"

_COX_BEGIN

template<typename T>
class vector {
public:
    using value_type                = T;
    using pointer                   = T*;
    using reference                 = T&;
    using const_reference           = T const&;
    using size_type                 = size_t;
    using iterator                  = _Vector_Iter<vector, T>;
    // using const_iterator            = _Vector_Iter<vector, const T>;
    // using reverse_iterator          = std::reverse_iterator<iterator>;
    // using const_reverse_iterator    = std::reverse_iterator<const_iterator>;

    vector() : m_size{ 0 }, m_capacity{ 2 }, m_ptr{ new T[2]} {}

    vector(size_type count, const_reference value = T())
        : m_size{ count }, m_capacity{ count }, m_ptr{ new T[count] }
    {
        for (size_type i = 0; i < m_size; ++i)
            m_ptr[i] = value;
    }

    vector(vector const& other) 
        : m_size{ other.m_size }, m_capacity{ other.m_capacity }, m_ptr{ new T[m_capacity] }
    {
        for (size_type i = 0; i < m_size; ++i)
            m_ptr[i] = other[i];
    }

    vector(vector&& other)
        : m_size{ other.m_size }, m_capacity{ other.m_capacity }, m_ptr{ other.m_ptr }
    {
        other.m_capacity = other.m_size = 0;
        other.m_ptr = nullptr;
    }

    vector& operator = (vector const& other)
    {
        if (*this == other)
            return *this;

        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_ptr = new T[m_capacity];

        for (size_type i = 0; i < m_size; ++i)
            m_ptr[i] = other[i];

        return *this;
    }

    vector& operator = (vector&& other)
    {
        if (*this == other)
            return *this;

        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_ptr = other.m_ptr;

        other.m_capacity = other.m_size = 0;
        other.m_ptr = nullptr;

        return *this;
    }

    ~vector() { delete[] m_ptr; }

    bool operator==(const vector& other) const = default;

    /*
        Element access
    */

    reference operator[](size_type index) { return m_ptr[index]; }
    const_reference operator[](size_type index) const { return m_ptr[index]; }

    reference at(size_type index)
    {
        if (index >= m_size)
            throw std::out_of_range("Index is out of range");

        return m_ptr[index];
    }

    const_reference at(size_type index) const
    {
        if (index >= m_size)
            throw std::out_of_range("Index is out of range");

        return m_ptr[index];
    }

    T* data() { return m_ptr; }
    const T* data() const { return m_ptr; }

    reference front() { return m_ptr[0]; }
    const_reference front() const { return m_ptr[0]; }

    reference back() { return m_ptr[m_size - 1]; }
    const_reference back() const { return m_ptr[m_size - 1]; }

    /*
        Capacity
    */

    bool empty() const noexcept { return m_size == 0; }
    size_type capacity() const noexcept { return m_capacity; }
    size_type size() const noexcept { return m_size; }

    /*
        Iterators
    */

    iterator begin() { return iterator(*this, m_ptr); }
    iterator end() { return iterator(*this, m_ptr + m_size); }

    // reverse_iterator rbegin() { return reverse_iterator(*this, m_ptr); }
    // reverse_iterator rend() { return reverse_iterator(*this, m_ptr + m_size); }


    /*
        Modifiers
    */

    void push_back(const_reference x)
    {
        if (m_capacity < m_size + 1)
            reserve(m_capacity * 2);

        m_ptr[m_size++] = x;
    }

    void push_back(T&& x)
    {
        if (m_capacity < m_size + 1)
            reserve(m_capacity * 2);

        m_ptr[m_size++] = std::move(x);
    }

    template<typename... Args>
    reference emplace_back(Args&&... args)
    {
        if (m_capacity < m_size + 1)
            reserve(m_capacity * 2);

        new(&m_ptr[m_size++]) T(std::forward<Args>(args)...);    
        return back();
    }

    void clear() 
    {
        delete[] m_ptr;
        m_ptr = nullptr;
        m_size = m_capacity = 0;
    }

    void pop_back()
    {
        if (m_size <= 0)
            return;

        m_size--;
        if ( 2 * m_size <= m_capacity)
            shrink_to_fit();
    }

    void swap(vector& other) 
    {
        std::swap(m_ptr, other.m_ptr);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }

    // Allocation

    void reserve(size_type newCapacity)
    {
        if (newCapacity < m_capacity)
            return;

        pointer newPtr = new T[newCapacity];
        for (size_type i = 0; i < m_size; ++i)
            newPtr[i] = std::move(m_ptr[i]);
        
        delete[] m_ptr;
        m_ptr = newPtr;
        m_capacity = newCapacity;
    }

    void shrink_to_fit()
    {
        if (m_capacity == m_size)
            return;

        pointer newPtr = new T[m_size];
        for (size_type i = 0; i < m_size; ++i)
            newPtr[i] = std::move(m_ptr[i]);

        delete[] m_ptr;
        m_ptr = newPtr;
        m_capacity = m_size;
    }
    

private:
    size_t m_size = 0;
    size_t m_capacity = 0;
    T* m_ptr;
};

_COX_END

#endif // !VECTOR_

