#pragma once

#include <iostream>

namespace cox {

    template<typename T> class Matrix {
    public:

        Matrix() : n{ 0 }, m{ 0 }, a{ nullptr }, n_alloc{ 0 }
        {}

        Matrix(size_t n, size_t m, T val = T()) : 
            n{ n }, m{ m }, n_alloc{ 0 }
        {
            if (n && m)
            {
                Alloc();
                for (size_t i = 0; i < n; ++i)
                    for (size_t j = 0; j < m; ++j)
                        a[i][j] = val;
            }
            else a = nullptr;
        }

        Matrix(Matrix<T>&& other) :
            n{ other.n }, m{ other.m }, a{ other.a }
        { other.~Matrix(); }

        Matrix(Matrix<T> const& other) :
            n{ other.n }, m{ other.m }
        { Copy(other); }

        ~Matrix()
        { Free(); }

        size_t height() const noexcept
        { return n; }

        size_t width() const noexcept
        { return m; }

        Matrix<T>& operator = (Matrix<T> const& other)
        {
            n = other.n;
            m = other.m;
            if (other.a != nullptr) Copy(other);
            return *this;
        }

        T*& operator[](size_t i)
        { return a[i]; }

        const T* operator[](size_t i) const
        { return a[i]; }

        bool Empty() const noexcept
        { return a == nullptr; }

        friend std::ostream& operator << (std::ostream& out, Matrix<T> const& m)
        {
            if (m.a == nullptr)
                return out << "\nempty matrix\n";
            for (size_t i = 0; i < m.n; ++i, out << '\n')
                for (size_t j = 0; j < m.m; ++j)
                    out << m.a[i][j] << ' ';
            return out;
        }


    private:
        size_t n, m;
        T** a;
        size_t n_alloc;

        void Alloc()
        {
            n_alloc = n;
            a = new T * [n_alloc];

            for (size_t i = 0; i < n_alloc; ++i)
                a[i] = new T[m];
        }

        void Free()
        {
            if (a == nullptr) return;
            for (size_t i = 0; i < n_alloc; ++i)
                delete[] a[i];
            delete[] a;
            a = nullptr;
        }

        void Copy(Matrix<T> const& other)
        {
            Free();
            Alloc();
            for (size_t i = 0; i < n; ++i)
                for (size_t j = 0; j < m; ++j)
                    a[i][j] = other[i][j];
        }
    };

};