#ifndef VECTOR_ITERATOR_H

#include "../globals.h"
#include "vector.h"

_COX_BEGIN

template<template <typename> typename Container, typename T>
class _Vector_Iter {
public:
    using value_type = Container<T>::value_type;     
    using pointer    = Container<T>::pointer;
    using reference  = Container<T>::reference;
    using size_type  = Container<T>::size_type;
    
public:
    _Vector_Iter(Container<T>& ref, T* ptr)
        : m_ref(ref), m_ptr(ptr)
    {}

    _Vector_Iter& operator ++() 
    {
        m_ptr++;
        return *this;
    }

    _Vector_Iter operator ++(int)
    {
        _Vector_Iter copy{ *this };
        m_ptr++;
        return copy;
    }

    _Vector_Iter& operator --()
    {
        m_ptr--;
        return *this;
    }

    _Vector_Iter operator --(int)
    {
        _Vector_Iter copy{ *this };
        m_ptr--;
        return copy;
    }

    T& operator * () { return *m_ptr; }
    T*& operator -> () { return m_ptr;  }

    bool operator ==(_Vector_Iter const& other) const noexcept
    {
        return m_ptr == other.m_ptr;
    }

    bool operator !=(_Vector_Iter const& other) const noexcept
    {
        return !(m_ptr == other.m_ptr);
    }

private:
    Container<T>& m_ref;
    T* m_ptr;
};


_COX_END

#endif // !VECTOR_ITERATOR_H

