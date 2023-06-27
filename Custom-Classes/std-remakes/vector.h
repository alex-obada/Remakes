#ifndef VECTOR_
#define VECTOR_

#include <initializer_list>

#include "../globals.h"

_COX_BEGIN

template<typename T>
class vector {
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_reference = T const&;
    using size_type = size_t;
    //using iterator =
    //using const_iterator =
    //using reverse_iterator =
    //using const_reverse_iterator =

    vector() : n{ 0 }, cap{ 0 }, ptr{ nullptr }
    {}

    vector(size_type count, const_reference value = T())
        : n{ count }, cap{ count }, ptr{ new T[size] }
    {
        for (size_type i = 0; i < size(); ++i)
            ptr[i] = value;
    }

    vector(vector const& other) 
        : n{ other.size }, cap{ other.capacity }, ptr{ new T[capacity] }
    {
        for (size_type i = 0; i < size(); ++i)
            ptr[i] = other[i];
    }

    vector(vector&& other)
        : n{ other.size }, cap{ other.capacity }, ptr{ other.ptr }
    {
        other.cap = other.n = 0;
        other.ptr = nullptr;
    }

    vector& operator = (vector const& other)
    {
        n = other.n;
        cap = other.cap;
        ptr = new T[cap];

        for (size_type i = 0; i < size(); ++i)
            ptr[i] = other[i];
    }

    vector& operator = (vector&& other)
    {
        n = other.n;
        cap = other.cap;
        ptr = other.ptr;

        other.cap = other.n = 0;
        other.ptr = nullptr;
    }

    ~vector()
    {
        delete[] ptr;
    }

    reference operator[](size_type index)
    {
        return ptr[index];
    }

    const_reference operator[](size_type index) const
    {
        return ptr[index];
    }

    void reserve(size_type newCapacity)
    {
        if (newCapacity < capacity())
            return;

        pointer newPtr = new T[newCapacity];
        for (size_type i = 0; i < size(); ++i)
            newPtr[i] = ptr[i];
        
        delete[] ptr;
        ptr = newPtr;
        cap = newCapacity;
    }

    void shrink_to_fit()
    {
        if (capacity() == size())
            return;

        pointer newPtr = new T[size()];
        for (size_type i = 0; i < size(); ++i)
            newPtr[i] = ptr[i];

        delete[] ptr;
        ptr = newPtr;
        cap = size;
    }

    size_type capacity() const noexcept
    {
        return cap;
    }

    size_type size() const noexcept
    {
        return n;
    }

private:
    size_t n;
    size_t cap;
    T* ptr;
};

_COX_END

#endif // !VECTOR_

