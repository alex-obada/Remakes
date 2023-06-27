#ifndef LIST_ITER_
#define LIST_ITER_

#include "../globals.h"

_COX_BEGIN

template <class Container>
class _List_Iterator {
public:

	using pointer	      = Container::pointer;				/// T*
	using node_pointer    = Container::node_pointer;		/// Node*
	using reference	      = Container::reference;			/// T&
	using const_reference = Container::const_reference;     /// const T&

	_List_Iterator(Container& c, node_pointer ptr) :
		c {c}, ptr {ptr} 
	{}

	_List_Iterator& operator++ ()
	{
		ptr = c.next(ptr);
		return *this;
	}

	_List_Iterator& operator-- ()
	{
		ptr = c.prev(ptr);
		return *this;
	}

	reference operator* ()
	{
		return c.data(ptr);
	}

	node_pointer operator-> ()
	{
		return ptr;
	}

	bool operator == (_List_Iterator const& other) const noexcept
	{
		return ptr == other.ptr;
	}

	node_pointer GetPtr() const noexcept
	{
		return ptr;
	}

private:
	Container& c;
	node_pointer ptr;
};

_COX_END

#endif