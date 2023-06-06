#include "matrix.h"

COX_BEGIN_NAMESPACE

Matrix Matrix::GetUnitMatrix(size_type n)
{
    Matrix m = GetNullMatrix(n, n);
    for (int i = 0; i < n; ++i)
        m[i][i] = 1;
    return m;
}

Matrix Matrix::GetNullMatrix(size_type lines, size_type columns)
{
    return Matrix(lines, columns, 0);
}

void Matrix::Allocate(size_type n, size_type m)
{
    if (matrix != nullptr) Free();
    //std::cout << "Alocare matrice " << this << '\n';
    matrix = new pointer[n];
    for (size_type i = 0; i < n; ++i)
        matrix[i] = new value_type[m];
}

Matrix::Matrix(size_type lines, size_type columns, value_type value)
    : lines{ lines }, columns{ columns }
{
    Allocate(lines, columns);

    for (auto& x : *this)
        x = value;
}

Matrix::Matrix(Matrix const& m)
    : lines{ m.lines }, columns { m.columns }
{
    Allocate(lines, columns);
    Copy(m);
}

Matrix::Matrix(Matrix&& m) noexcept
    : lines{ m.lines }, columns{ m.columns }, matrix{ m.matrix }
{
    m.lines = m.columns = 0;
    m.matrix = nullptr;
}

Matrix::~Matrix()
{
    //std::cout << "Distrugere matrice " << this << '\n';
    Free();
}

Matrix& Matrix::operator = (Matrix const& m)
{
    if (m == *this) return *this;
    
    if(matrix != nullptr) Free();

    lines = m.lines;
    columns = m.columns;
    Allocate(lines, columns);
    Copy(m);

    return *this;
}

Matrix& Matrix::operator = (Matrix&& m) noexcept
{
    if (m == *this) return *this;

    if (matrix != nullptr) Free();

    lines = m.lines;
    columns = m.columns;
    matrix = m.matrix;

    m.lines = m.columns = 0;
    m.matrix = nullptr;

    return *this;
}

Matrix& Matrix::operator += (value_type n)
{
    for (auto& x : *this)
        x += n;
    return *this;
}

Matrix& Matrix::operator += (Matrix const& m)
{
    if (!isAddable(m)) return *this;
    for (size_type i = 0; i < lines; ++i)
        for (size_type j = 0; j < columns; ++j)
            matrix[i][j] += m[i][j];
    return *this;
}

Matrix& Matrix::operator -= (value_type n)
{
    for (auto& x : *this)
        x -= n;
    return *this;
}

Matrix& Matrix::operator -= (Matrix const& m)
{
    if (!isAddable(m)) return *this;
    for (size_type i = 0; i < lines; ++i)
        for (size_type j = 0; j < columns; ++j)
            matrix[i][j] -= m[i][j];
    return *this;
}

Matrix& Matrix::operator *= (value_type n)
{
    for (auto& x : *this)
        x *= n;
    return *this;
}


Matrix& Matrix::operator /= (value_type n)
{
    for (auto& x : *this)
        x /= n;
    return *this;
}

void Matrix::Free()
{
    if (matrix == nullptr)
        return;

    for (size_type i = 0; i < lines; ++i)
        delete[] matrix[i];
    delete[] matrix;
    
    matrix = nullptr;
    columns = 0;
    lines = 0;
}

void Matrix::Copy(Matrix const& m)
{
    // exceptie
    if (lines != m.lines ||
        columns != m.columns)
    {
        std::cout << "Copiere cu matrici inegale";
        return;
    }

    for (size_type i = 0; i < lines; ++i)
        for (size_type j = 0; j < columns; ++j)
            matrix[i][j] = m.matrix[i][j];
}


const Matrix::pointer Matrix::operator[](size_type i) const
{
    return matrix[i];
}

Matrix::pointer& Matrix::operator[](size_type i)
{
    return matrix[i];
}

bool Matrix::operator == (Matrix const& m) const noexcept
{
    if (lines != m.lines ||
        columns != m.columns ||
        matrix == nullptr ||
        m.matrix == nullptr)
            return false;

    if (matrix == m.matrix) return true;
    
    for (size_type i = 0; i < lines; ++i)
        for (size_type j = 0; j < columns; ++j)
            if(matrix[i][j] != m.matrix[i][j])
                return false;
    return true;
}

Matrix::iterator Matrix::begin() noexcept
{
    return iterator(*this, {0, 0});
}

Matrix::iterator Matrix::end() noexcept
{
    return iterator(*this, {npos, npos});
}

bool Matrix::isAddable(Matrix const& m) const noexcept
{
    return !lines && lines == m.lines 
           && columns == m.columns;
}

Matrix::size_type Matrix::GetLines() const noexcept
{
    return lines;
}

Matrix::size_type Matrix::GetColumns() const noexcept
{
    return columns;
}

bool Matrix::isSquareMatrix(Matrix const& m)
{
    return m.lines && m.columns == m.lines;
}

bool Matrix::isValidMatrix(Matrix const& m)
{
    return m.matrix != nullptr && m.lines && m.columns;
}

bool Matrix::isUnitMatrix(Matrix const& m)
{
    if (!isSquareMatrix(m))
        return false;

    for (size_type i = 0; i < m.lines; ++i)
        for (size_type j = 0; j < m.columns; ++j)
            if (i == j && m[i][j] != 1)
                return false;
            else if (i != j && m[i][j] != 0)
                return false;

    return true;
}

bool Matrix::isNullMatrix(Matrix const& m)
{
    if (!Matrix::isValidMatrix(m)) return false;

    for (size_type i = 0; i < m.GetLines(); ++i)
        for (size_type j = 0; j < m.GetColumns(); ++j)
            if (m[i][j] != 0)
                return false;
    return true;
}

bool Matrix::isTriangularMatrix(Matrix const& m)
{
    bool diagonal, over, under;
    diagonal = over = under = false;

    for (size_type i = 0; i < m.lines; ++i)
        for (size_type j = 0; j < m.columns; ++j)
        {
            if (i == j)
                diagonal |= m[i][j];
            if (i < j)
                under |= m[i][j];
            if (i > j)
                over |= m[i][j];
        }

    if (diagonal == false) return false;
    if ((over && !under)
        || !over && under)
        return true;

    return false;
}

Matrix Matrix::GetTransposed(Matrix const& m)
{
    Matrix copy(m.columns, m.lines);
    for (size_type i = 0; i < m.lines; ++i)
        for (size_type j = 0; j < m.columns; ++j)
            copy[j][i] = m[i][j];
    return copy;
}

Matrix::value_type Matrix::GetTrace(Matrix const& m)
{
    if (!Matrix::isSquareMatrix(m)) return -1;
    
    value_type trace{ 0 };
    for (size_type i = 0; i < m.lines; ++i)
        trace += m[i][i];
    return trace;
}


std::ostream& operator << (std::ostream& os, Matrix const& m)
{
    for (Matrix::size_type i = 0; i < m.lines; ++i, os << '\n')
        for (Matrix::size_type j = 0; j < m.columns; ++j)
            os << m[i][j] << ' ';
    return os;
}


Matrix Matrix::operator + (value_type n)
{
    Matrix m = *this;
    for (auto& x : m)
        x += n;
    return m;
}

Matrix Matrix::operator + (Matrix const& m)
{
    if (!isAddable(m)) return *this;
    Matrix c(lines, columns, 0);
    for (size_type i = 0; i < lines; ++i)
        for (size_type j = 0; j < columns; ++j)
            c[i][j] = matrix[i][j] + m[i][j];
    return c;
}

Matrix Matrix::operator - (value_type n)
{
    Matrix m = *this;
    for (auto& x : m)
        x -= n;
    return m;
}

Matrix Matrix::operator - (Matrix const& m)
{
    if (!isAddable(m)) return *this;
    Matrix c(lines, columns, 0);
    for (size_type i = 0; i < lines; ++i)
        for (size_type j = 0; j < columns; ++j)
            c[i][j] = matrix[i][j] - m[i][j];
    return c;
}

Matrix Matrix::operator * (value_type n)
{
    Matrix m = *this;
    for (auto& x : m)
        x *= n;
    return m;
}

Matrix Matrix::operator / (value_type n)
{
    Matrix m = *this;
    for (auto& x : m)
        x /= n;
    return m;
}



COX_END_NAMESPACE