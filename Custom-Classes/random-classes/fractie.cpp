#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <numeric>

#include "fractie.h"

_COX_BEGIN

int Fractie::Cmmdc(int a, int b)
{
    return std::gcd(a, b);
}

int Fractie::Cmmmc(int a, int b)
{
    return 1LL * a * b / Cmmdc(a, b);
}


void Fractie::SimplificareFr(int& a, int& b)
{
    int cmmdc = Cmmdc(a, b);
    a /= cmmdc;
    b /= cmmdc;
}


Fractie::Fractie(int numarator = 1, int numitor = 1) :
    numarator(numarator), numitor(numitor)
{
    if (!numitor)
    {
        std::cout << "\nnumitor 0  -->  " << __PRETTY_FUNCTION__ << "\n\n";
        std::exit(0);
    }
    SimplificareFr(this->numarator, this->numitor);
}

void Fractie::SimplificareFr() noexcept
{
    SimplificareFr(numarator, numitor);
}


// Settere si Getere

void Fractie::SetNumarator(int numarator) noexcept
{
    this->numarator = numarator;
    SimplificareFr();
}

int Fractie::GetNumarator() const noexcept
{
    return numarator;
}

void Fractie::SetNumitor(int numitor) noexcept
{
    if (!numitor)
    {
        std::cout << "\nnumitor 0  -->  " << __PRETTY_FUNCTION__ << "\n\n";
        std::exit(0);
    }

    this->numitor = numitor;
    SimplificareFr();

}

int Fractie::GetNumitor() const noexcept
{
    return numitor;
}

// op unari

Fractie& Fractie::operator ++ () noexcept
{
    numarator = numarator + numitor;
    return *this;
}

Fractie Fractie::operator ++ (int) noexcept
{
    Fractie copie = *this;
    numarator = numarator + numitor;

    return copie;
}

// op aritmetici cu fractii

Fractie Fractie::operator + (const Fractie& x) const noexcept
{
    int newnumitor = Fractie::Cmmmc(x.numitor, numitor);
    int newnumarator = numarator * (newnumitor / numitor) +
        x.numarator * (newnumitor / x.numitor);

    return Fractie(newnumarator, newnumitor);
}

Fractie Fractie::operator - (const Fractie& x) const noexcept
{
    int newnumitor = Fractie::Cmmmc(x.numitor, numitor);
    int newnumarator = numarator * (newnumitor / numitor) -
        x.numarator * (newnumitor / x.numitor);

    return Fractie(newnumarator, newnumitor);
}

Fractie Fractie::operator * (const Fractie& x) const noexcept
{
    int newnumitor = numitor * x.numitor;
    int newnumarator = numarator * x.numarator;

    return Fractie(newnumarator, newnumitor);
}

Fractie Fractie::operator / (const Fractie& x) const noexcept
{
    int newnumitor = x.numarator * numitor;
    int newnumarator = numarator * x.numitor;

    return Fractie(newnumarator, newnumitor);
}

// op aritmetici cu valori intregi

Fractie Fractie::operator + (int x) const noexcept
{
    Fractie copie = *this, tmp(x);
    return copie + tmp;
}

Fractie Fractie::operator - (int x) const noexcept
{
    Fractie copie = *this, tmp(x);
    return copie - tmp;
}

Fractie Fractie::operator * (int x) const noexcept
{
    Fractie copie = *this, tmp(x);
    return copie * tmp;
}

Fractie Fractie::operator / (int x) const noexcept
{
    Fractie copie = *this, tmp(x);
    return copie / tmp;
}

// assigment operators

Fractie& Fractie::operator = (Fractie const& x) noexcept
{
    numarator = x.numarator;
    numitor = x.numitor;
    return *this;
}

Fractie& Fractie::operator = (int nr) noexcept
{
    numitor = 1;
    numarator = nr;
    return *this;
}

// combined assigment operators cu fractii

Fractie& Fractie::operator += (Fractie const& x) noexcept
{
    int newnumitor = Cmmmc(x.numitor, numitor);
    int newnumarator = numarator * (newnumitor / numitor) +
        x.numarator * (newnumitor / x.numitor);
    SimplificareFr(newnumarator, newnumitor);
    numitor = newnumitor;
    numarator = newnumarator;
    return *this;
}

Fractie& Fractie::operator -= (Fractie const& x) noexcept
{
    int newnumitor = Cmmmc(x.numitor, numitor);
    int newnumarator = numarator * (newnumitor / numitor) -
        x.numarator * (newnumitor / x.numitor);
    SimplificareFr(newnumarator, newnumitor);
    numitor = newnumitor;
    numarator = newnumarator;
    return *this;
}

Fractie& Fractie::operator *= (Fractie const& x)  noexcept
{
    int newnumitor = numitor * x.numitor;
    int newnumarator = numarator * x.numarator;
    SimplificareFr(newnumarator, newnumitor);
    numitor = newnumitor;
    numarator = newnumarator;
    return *this;
}

Fractie& Fractie::operator /= (Fractie const& x) noexcept
{
    int newnumitor = numitor * x.numarator;
    int newnumarator = numarator * x.numitor;
    SimplificareFr(newnumarator, newnumitor);
    numitor = newnumitor;
    numarator = newnumarator;
    return *this;
}

// combined assigment operators cu valori intregi

Fractie& Fractie::operator += (int nr) noexcept
{
    numarator += nr * numitor;
    SimplificareFr();
    return *this;
}

Fractie& Fractie::operator -= (int nr) noexcept
{
    numarator -= nr * numitor;
    SimplificareFr();
    return *this;
}

Fractie& Fractie::operator *= (int nr)  noexcept
{
    numarator *= nr;
    SimplificareFr();
    return *this;
}

Fractie& Fractie::operator /= (int nr) noexcept
{
    numitor *= nr;
    SimplificareFr();
    return *this;
}

// logic operators

std::strong_ordering Fractie::operator <=> (Fractie const& x) const noexcept
{
    return numarator * x.numitor <=> numitor * x.numarator;
}

bool Fractie::operator == (const Fractie& x) const noexcept
{
    return numarator * x.numitor == numitor * x.numarator;
}

bool Fractie::operator != (const Fractie& x) const noexcept
{
    return numarator * x.numitor != numitor * x.numarator;
}

// stream

std::ostream& operator << (std::ostream& out, const Fractie& x)
{
    int max_len = std::max(Fractie::NrCifre(x.GetNumarator()), Fractie::NrCifre(x.GetNumitor()));
    if (x.numitor == 1)
        out << x.numarator << '\n';
    else
    {
        out << std::setw(max_len) << x.numarator << '\n';
        for (int i = 1; i <= max_len; ++i)
            out << '-';
        out << '\n';
        out << std::setw(max_len) << x.numitor;
    }
    return out << '\n';

}

std::istream& operator >> (std::istream& in, Fractie& x)
{
    std::cout << "numarator: ";
    in >> x.numarator;

    std::cout << "numitor  : ";
    in >> x.numitor;
    if (!x.numitor)
    {
        std::cout << "\nnumitor 0  -->  " << __PRETTY_FUNCTION__ << "\n\n";
        std::exit(0);
    }

    std::cout << '\n';

    x.SimplificareFr(x.numitor, x.numarator);

    return in;
}

int Fractie::NrCifre(int n)
{
    int cnt{ 0 };
    if (!n)
        ++cnt;
    if (n < 0)
    {
        n *= -1;
        ++cnt;
    }
    while (n)
    {
        ++cnt;
        n /= 10;
    }
    return cnt;
}

_COX_END