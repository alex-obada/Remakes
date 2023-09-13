#ifndef UNIQUE_PTR_
#define UNIQUE_PTR_

#include <utility>

#include "../globals.h"

_COX_BEGIN

template <typename T>
class unique_ptr {
public:
    using type      = T;
    using pointer   = T*;
    using reference = T&;

    unique_ptr(T* ptr = nullptr) : m_ptr {ptr}
    {}

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator =(const unique_ptr&) = delete;

    unique_ptr(unique_ptr&& other) 
        : m_ptr {other.release()}
    {}

    unique_ptr& operator =(unique_ptr&& other)
    {
        if (this != &other)
            reset(other.release());
        return *this;
    }

    pointer operator ->() const noexcept
    {
        return m_ptr;
    } 

    reference operator *() const noexcept
    {
        return *m_ptr;
    } 

    pointer get() const noexcept
    {
        return m_ptr;
    }
    
    pointer release() noexcept
    {
        //pointer copy = m_ptr;
        //m_ptr = nullptr;
        //return copy;
        return std::exchange(m_ptr, nullptr);
    }

    void reset(pointer ptr = nullptr) noexcept
    {
        if(m_ptr)
            delete ptr;

        m_ptr = ptr;
    }

    void swap(unique_ptr& other) noexcept
    {
        std::swap(m_ptr, other.m_ptr);
    }

    explicit operator bool() const noexcept
    {
        return m_ptr;
    }

    ~unique_ptr() noexcept
    {
        delete m_ptr;
    }

private: 
    T* m_ptr;
};


template<typename T, class... Args>
unique_ptr<T> make_unique(Args&&... args)
{
    return unique_ptr(new T(args...));
}

_COX_END

#endif // !UNIQUE_PTR_
