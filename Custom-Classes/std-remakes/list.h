#ifndef LIST_
#define LIST_

#include <iostream>
#include <initializer_list>

#include "list_iterator.h"
#include "../globals.h"

_COX_BEGIN

template<class Type>
struct Node {
	Node(Node* prev, Type const& x, Node* next) :
		prev{ prev }, data{ x }, next{ next }
	{}

	Node* prev;
	Type data;
	Node* next;

	bool operator == (const Node& other) const
	{
		return &data == &other.data;
	}

};

template<typename T>
class List {
public:
	using value_type	   = T;
	using pointer		   = T*;
	using reference		   = T&;
	using const_reference  = const T&;
	using node_type        = Node<T>;
	using node_pointer	   = node_type*;
	using iterator		   = _List_Iter<List<T>>;
	using const_iterator   = _List_Iter<List<const T>>;
	using reverse_iterator = _Reverse_List_Iter<List<T>>;
	using const_reverse_iterator = _Reverse_List_Iter<List<const T>>;

public:

	List() : nr{ 0 }, first{ nullptr }, last{ nullptr }
	{}

	List(List const& list) : nr{ 0 }
	{
		if (list.empty()) 
			return;
		Copy(list);
	}

	List(List&& list) noexcept : nr{ list.nr }
	{
		if (!empty()) 
			Free();

		Move(list);
	}

	List(std::initializer_list<T> l) 
		: nr{ 0 }, first{ nullptr }, last{ nullptr } 
	{
		for (const auto& value : l)
			emplace_back(value);
	}

	~List()
	{
		Free();
	}

public:

	bool operator == (List const& other) const
	{
		return first == other.first;
	}

	List& operator = (List const& list)
	{
		if (this == &list) 
			return *this;

		nr = 0;
		Copy(list);
		if (list.empty()) 
			return *this;

		return *this;
	}

	List& operator = (List&& list) noexcept
	{
		if (this == &list)
			return *this;

		nr = list.nr;
		if (!empty())
		{
			Free(); 
			return *this;
		}

		Move(list);
		return *this;
	}

public:		// Iterator

	iterator begin() noexcept
	{
		return iterator(*this, first);
	}

	iterator end() noexcept
	{
		return iterator(*this, nullptr);
	}
	
	const_iterator cbegin() const noexcept
	{
		return const_iterator(*((List<const T>*)this), (Node<const T>*)first);
	}

	const_iterator cend() const noexcept
	{
		return const_iterator(*((List<const T>*)this), nullptr);
	}

	reverse_iterator rbegin() noexcept
	{
		return reverse_iterator(*this, last);
	}

	reverse_iterator rend() noexcept
	{
		return reverse_iterator(*this, nullptr);
	}

	const_reverse_iterator crbegin() const noexcept
	{
		return const_reverse_iterator(*((List<const T>*)this), (Node<const T>*)last);
	}

	const_reverse_iterator crend() const noexcept
	{
		return const_reverse_iterator(*((List<const T>*)this), nullptr);
	}

public:		// Element acces

	const_reference front() const
	{
		return first->data;
	}

	const_reference back() const
	{
		return last->data;
	}


	reference front()
	{
		return first->data;
	}

	reference back()
	{
		return last->data;
	}

	size_t size() const noexcept
	{
		return nr;
	}

	bool empty() const noexcept
	{
		return first == nullptr;
	}

	operator bool() const noexcept
	{
		return !this->empty();
	}

		
public:		// Modifiers

	iterator insert(iterator pos, const_reference value)
	{
		return iterator(*this, insertBefore(pos.GetPtr(), value));
	}

	iterator erase(iterator pos)
	{
		if(pos == end())
			return end();
		return iterator(*this, erase(pos.GetPtr()));
	}

	void clear()
	{
		Free();
	}

	void swap(List& other)
	{
		std::swap(first, other.first);
		std::swap(last, other.last);
		std::swap(nr, other.nr);
	}

	void push_back(const_reference x) noexcept
	{
		insertAfter(last, x);
	}

	void pop_back() noexcept
	{
		erase(last);
	}

	void push_front(const_reference x) noexcept
	{
		insertBefore(first, x);
	}

	void pop_front() noexcept
	{
		erase(first);
	}

	template<typename... Args>
	void emplace_back(Args&&... args) 
	{
		// empty list
		if (first == nullptr)
		{
			first = last = new node_type(nullptr, 
				T(std::forward<Args>(args)...), nullptr);
			nr++;
			return;
		}
	 
		// general case
		nr++;
		last = last->next = new node_type(last, 
			T(std::forward<Args>(args)...), nullptr);
	}

private:	// Utility

	node_pointer erase(node_pointer p)
	{
		if (!p || !first) 
			return nullptr;

		// 1 element in list
		if (first->next == nullptr)
		{
			delete first;
			first = last = nullptr;
			nr = 0;
			return nullptr;
		}

		// first element
		if (p == first)
		{
			first = first->next;
			delete p;
			first->prev = nullptr;
			nr--;
			return first;
		}

		// last element
		if (p == last)
		{
			last = last->prev;
			last->next = nullptr;
			delete p;
			nr--;
			return nullptr;
		}

		// general case
		node_pointer tail = p->next;
		p->prev->next = p->next;
		p->next->prev = p->prev;
		nr--;
		delete p;

		return tail;

	}

	void insertAfter(node_pointer p, const_reference val)
	{
		// empty list
		if (first == nullptr && p == nullptr)
		{
			first = last = new node_type(nullptr, val, nullptr);
			nr++;
			return;
		}

		// 1 element
		if (p->next == nullptr)
		{
			last = last->next = new node_type(last, val, nullptr);
			nr++;
			return;
		}

		// general case
		nr++;
		p->next = new node_type(p, val, p->next);
		p->next->next->prev = p->next;
	}

	node_pointer insertBefore(node_pointer p, const_reference val)
	{
		// empty list
		if (first == nullptr && p == nullptr)
		{
			first = last = new node_type(nullptr, val, nullptr);
			nr++;
			return first;
		}

		// 1 element
		if (p == first)
		{
			first = first->prev = new node_type(nullptr, val, first);
			nr++;
			return first;
		}

		if(p == nullptr)
			return last = last->next = new node_type(last, val, nullptr);

		// general case
		nr++;
		p->prev = new node_type(p->prev, val, p);
		p->prev->prev->next = p->prev;
		return p->prev;
	}


	void Free()
	{
		if (first == nullptr && last == nullptr && nr == 0) 
			return;

		nr = 0;
		for (node_pointer p = first, aux; p != nullptr; p = aux)
		{
			aux = p->next;
			delete p;
		}

		first = last = nullptr;
	}

	void Copy(List const& list)
	{
		if (!this->empty()) 
			Free();
		for (node_pointer p = list.first; p; p = p->next)
			this->push_back(p->data);
	}

	void Move(List& list)
	{
		first = list.first;
		last = list.last;
		list.first = list.last = nullptr;
		list.nr = 0;
	}

private:
	size_t nr;
	node_pointer first, last;

};

_COX_END

#endif