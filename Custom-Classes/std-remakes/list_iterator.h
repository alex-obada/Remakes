#ifndef LIST_ITER_
#define LIST_ITER_

#include "../globals.h"

_COX_BEGIN

template <class Container>
class _List_Iter {
public:

	using value_type	    = Container::value_type;
	using pointer	        = Container::pointer;	
	using reference	        = Container::reference;	
	using node_pointer      = Container::node_pointer;

	_List_Iter(Container& c, node_pointer ptr) :
		c{ c }, ptr{ ptr } {}

	_List_Iter& operator++ ()
	{
		ptr = ptr->next;
		return *this;
	}

	_List_Iter operator++ (int)
	{
		_List_Iter copy = *this;
		++(*this);
		return copy;
	}

	_List_Iter& operator-- ()
	{
		if (ptr == nullptr)
		{
			node_pointer* data = (node_pointer*)&c.back();
			ptr = (node_pointer)(data - 1);
		}
		else
			ptr = ptr->prev;

		return *this;
	}

	_List_Iter operator-- (int)
	{
		_List_Iter copy = *this;
		--(*this);
		return copy;
	}

	reference operator* ()
	{
		return ptr->data;
	}

	pointer operator-> ()
	{
		return &ptr->data;
	}

	bool operator == (_List_Iter const& other) const noexcept
	{
		return ptr == other.ptr;
	}

	node_pointer GetPtr() const noexcept
	{
		return ptr;
	}

protected:
	Container& c;
	node_pointer ptr;

};


template <class Container>
class _Reverse_List_Iter {
public:

	using value_type   = Container::value_type;
	using pointer	   = Container::pointer;
	using reference    = Container::reference;
	using node_type    = Container::node_type;
	using node_pointer = Container::node_pointer;

	_Reverse_List_Iter(Container& c, node_pointer ptr) :
		c{ c }, ptr{ ptr } {}

	_Reverse_List_Iter& operator++ ()
	{
		ptr = ptr->prev;
		return *this;
	}

	_Reverse_List_Iter operator++ (int)
	{
		_Reverse_List_Iter copy = *this;
		++(*this);
		return copy;
	}

	_Reverse_List_Iter& operator-- ()
	{
		if (ptr == nullptr)
		{
			node_pointer* data = (node_pointer*)&c.front();
			ptr = (node_pointer)(data - 1);
		}
		else
			ptr = ptr->next;

		return *this;
	}

	_Reverse_List_Iter operator-- (int)
	{
		_Reverse_List_Iter copy = *this;
		--(*this);
		return copy;
	}

	reference operator* ()
	{
		return ptr->data;
	}

	pointer operator-> ()
	{
		return &ptr->data;
	}

	bool operator == (_Reverse_List_Iter const& other) const noexcept
	{
		return ptr == other.ptr;
	}

	node_pointer GetPtr() const noexcept
	{
		return ptr;
	}

protected:
	Container& c;
	node_pointer ptr;

};

_COX_END

#endif