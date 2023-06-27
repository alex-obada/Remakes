#ifndef MATRIX_
#define MATRIX_

#include <iostream>
#include <cmath>
#include <algorithm>

#include "../globals.h"
#include "matrix_iterator.h"

_COX_BEGIN

class Matrix {
public:
	using value_type	  = long long;
	using size_type		  = size_t;
	using reference		  = value_type&;
	using const_reference = value_type const&;
	using pointer		  = value_type*;
	using iterator		  = _Matrix_Iterator<Matrix>;

	static const size_type npos = -1;

	Matrix(size_type lines, size_type columns, value_type value = value_type());
	Matrix(Matrix const& m);
	Matrix(Matrix&& m) noexcept;
	~Matrix();

	Matrix& operator = (Matrix const& m);
	Matrix& operator = (Matrix&& m) noexcept;
	
	Matrix& operator += (value_type n);
	Matrix& operator += (Matrix const& m);

	Matrix& operator -= (value_type n);
	Matrix& operator -= (Matrix const& m);

	Matrix& operator *= (value_type n);

	Matrix& operator /= (value_type n);


	Matrix operator + (value_type n);
	Matrix operator + (Matrix const& m);

	Matrix operator - (value_type n);
	Matrix operator - (Matrix const& m);

	Matrix operator * (value_type n);
	Matrix operator / (value_type n);
	
	const pointer operator [](size_type i) const;
	pointer& operator [](size_type i);

	bool operator == (Matrix const& m) const noexcept;

	iterator begin() noexcept;
	iterator end() noexcept;

	bool isAddable(Matrix const& m) const noexcept;

	size_type GetLines() const noexcept;
	size_type GetColumns() const noexcept;

	static bool isSquareMatrix(Matrix const& m);
	static bool isValidMatrix(Matrix const& m);
	static bool isUnitMatrix(Matrix const& m);
	static bool isNullMatrix(Matrix const& m);
	static bool isTriangularMatrix(Matrix const& m);
	
	static Matrix GetTransposed(Matrix const& m);
	static value_type GetTrace(Matrix const& m);

	static Matrix GetUnitMatrix(size_type n);
	static Matrix GetNullMatrix(size_type lines, size_type columns);

	friend std::ostream& operator << (std::ostream& os, Matrix const& m);
private:
	size_type lines, columns;	
	value_type** matrix;

	void Allocate(size_type n, size_type m);
	void Free();
	void Copy(Matrix const& m);
};


_COX_END


#endif // !define MATRIX_
