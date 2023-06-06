#ifndef FRACTIE_
#define FRACTIE_

#ifndef __GNUC__
    #define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

#include <iostream>

#include "../globals.h"

COX_BEGIN_NAMESPACE

class Fractie {
public:
    Fractie(int numarator, int numitor);

    void SimplificareFr() noexcept;

    // Settere si Getere

    void SetNumarator(int numarator) noexcept;
    int GetNumarator() const noexcept;
    void SetNumitor(int numitor) noexcept;
    int GetNumitor() const noexcept;

    // op unari

    Fractie& operator ++ () noexcept;
    Fractie operator ++ (int) noexcept;

    // op aritmetici

    Fractie operator + (const Fractie& x) const noexcept;
    Fractie operator - (const Fractie& x) const noexcept;
    Fractie operator * (const Fractie& x) const noexcept;
    Fractie operator / (const Fractie& x) const noexcept;

    Fractie operator + (int nr) const noexcept;
    Fractie operator - (int nr) const noexcept;
    Fractie operator * (int nr) const noexcept;
    Fractie operator / (int nr) const noexcept;

    // assigment operator

    Fractie& operator  = (Fractie const& x) noexcept;
    Fractie& operator += (Fractie const& x) noexcept;
    Fractie& operator -= (Fractie const& x) noexcept;
    Fractie& operator *= (Fractie const& x) noexcept;
    Fractie& operator /= (Fractie const& x) noexcept;

    Fractie& operator  = (int nr) noexcept;
    Fractie& operator += (int nr) noexcept;
    Fractie& operator -= (int nr) noexcept;
    Fractie& operator *= (int nr) noexcept;
    Fractie& operator /= (int nr) noexcept;

    // logic operators

    std::strong_ordering operator <=> (Fractie const& x) const noexcept;
    bool operator == (const Fractie& x) const noexcept;
    bool operator != (const Fractie& x) const noexcept;

    // stream
    friend std::ostream& operator << (std::ostream& out, const Fractie& x);
    friend std::istream& operator >> (std::istream& in, Fractie& x);

private:
    int numarator;
    int numitor;

    void SimplificareFr(int& a, int& b);

    static int Cmmdc(int a, int b);
    static int Cmmmc(int a, int b);
    static int NrCifre(int n);

};

COX_END_NAMESPACE

#endif