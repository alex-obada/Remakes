#ifndef MATRIX_ITER_
#define MATRIX_ITER_

#include <utility>

#include "../globals.h"
#include "matrix.h"

_COX_BEGIN

template<class Container>
class _Matrix_Iterator {
public:
	using value_type		= Container::value_type;
	using size_type			= Container::size_type;
	using reference			= Container::reference;
	using const_reference	= Container::const_reference;
	using pointer			= Container::pointer;
	using pair				= std::pair<value_type, value_type>;

	static const value_type npos = Container::npos;


	_Matrix_Iterator(Container& c, pair ptr)
		: c{ c }, ptr{ ptr }
	{}

	_Matrix_Iterator(_Matrix_Iterator const& it)
		: c{ it.c }, ptr{ it.ptr }
	{}

	_Matrix_Iterator& operator ++ ()
	{
		value_type& n = ptr.first;
		value_type& m = ptr.second;
		++m;
		if (m == c.GetColumns())
			++n, m = 0;
		if (n == c.GetLines())
			n = npos, m = npos;
		return *this;
	}

	_Matrix_Iterator& operator ++ (int)
	{
		_Matrix_Iterator it = *this;
		
		value_type& n = ptr.first;
		value_type& m = ptr.second;
		
		++m;
		if (m == c.GetColumns())
			++n, m = 0;
		if (n == c.GetLines())
			n = npos, m = npos;
		
		return it;
	}

	_Matrix_Iterator& operator -- ()
	{
		value_type& n = ptr.first;
		value_type& m = ptr.second;
		
		if (n == npos || m == npos)
		{
			n = c.GetLines() - 1;
			m = c.GetColumns() - 1;
			return *this;
		}

		--m;
		if (m == npos)
			--n, m = c.GetColumns() - 1;
			
		
		return *this;
	}

	_Matrix_Iterator& operator -- (int)
	{
		_Matrix_Iterator it = *this;

		value_type& n = ptr.first;
		value_type& m = ptr.second;

		if (n == npos || m == npos)
		{
			n = c.GetLines() - 1;
			m = c.GetColumns() - 1;
			return it;
		}

		--m;
		if (m == npos)
			--n, m = c.GetColumns() - 1;


		return it;
	}

	reference operator * ()
	{
		return c[ptr.first][ptr.second];
	}

	bool operator == (_Matrix_Iterator const& i) const noexcept
	{
		return i.ptr == ptr;
	}

private:
	Container& c;
	pair ptr;

};

_COX_END

#endif // !define MATRIX_ITER_