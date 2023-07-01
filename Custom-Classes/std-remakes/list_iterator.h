#ifndef LIST_ITER_
#define LIST_ITER_

#include "../globals.h"

_COX_BEGIN

template <class Container>
class _List_Iter {
public:

	using value_type	    = Container::value_type;			/// T
	using pointer	        = Container::pointer;				/// T*
	using reference	        = Container::reference;			/// T&
	using node_pointer      = Container::node_pointer;		/// Node*
	//using iterator_category = std::bidirectional_iterator_tag;

	_List_Iter(Container& c, node_pointer ptr) :
		c{ c }, ptr{ ptr } 
	{}

	_List_Iter& operator++ ()
	{
		ptr = ptr->next;
		return *this;
	}

	_List_Iter operator++ (int)
	{
		_List_Iter copy = *this;
		ptr = ptr->next;
		return copy;
	}

	_List_Iter& operator-- ()
	{
		ptr = ptr->prev;
		return *this;
	}

	_List_Iter operator-- (int)
	{
		_List_Iter copy = *this;
		ptr = ptr->prev;
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
class _Const_List_Iter {
public:

	using pointer		   = Container::pointer;		    /// T*
	using const_reference  = Container::const_reference;	/// const T&
	using node_pointer	   = Container::node_pointer;		/// Node*

	_Const_List_Iter(Container& c, node_pointer ptr) :
		c{ c }, ptr{ ptr }
	{}

	_Const_List_Iter& operator++ ()
	{
		ptr = ptr->next;
		return *this;
	}

	_Const_List_Iter operator++ (int) 
	{
		_Const_List_Iter copy = *this;
		ptr = ptr->next;
		return copy;
	}

	_Const_List_Iter& operator-- ()
	{
		ptr = ptr->prev;
		return *this;
	}

	_Const_List_Iter operator-- (int) 
	{
		_Const_List_Iter copy = *this;
		ptr = ptr->prev;
		return copy;
	}

	const_reference operator* () const
	{
		return ptr->data;
	}

	const pointer operator-> () const
	{
		return &ptr->data;
	}

	bool operator == (_Const_List_Iter const& other) const noexcept
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