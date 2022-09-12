#pragma once
#include <iostream>
#include "iterator.h"

namespace cox
{

	template<typename T>
	class List {
	private:
		struct Node {
			Node(Node* prev, T x, Node* next) :
				prev{ prev }, data{ x }, next{ next } 
			{}

			Node* prev;
			T data;
			Node* next;

		};

		size_t nr;
		Node* first, * last;

	public:

		using pointer =			 T*;
		using reference =		 T&;
		using const_reference =	 const T&;
		using node_pointer =	 Node*;
		using iterator =		 Iterator<List>;


		List() : nr{ 0 }, first{ nullptr }, last{ nullptr }
		{}

		List(List const& list) : nr{ 0 }
		{
			Copy(list);
			if (list.Empty()) return;
		}

		List(List&& list) noexcept : nr{ list.nr }
		{
			if (!Empty()) Free();

			Move(list);
		}

		~List()
		{
			Free();
		}


		List& operator = (List const& list)
		{
			nr = 0;

			Copy(list);
			if (list.Empty()) return *this;

			return *this;
		}

		List& operator = (List&& list) noexcept
		{
			nr = list.nr;
			if (!Empty())
			{
				Free(); return *this;
			}

			Move(list);
			return *this;
		}

		// Iterator

		iterator begin() noexcept
		{
			return iterator(*this, first);
		}

		iterator end() noexcept
		{
			return iterator(*this, nullptr);
		}

		node_pointer prev(node_pointer ptr) const noexcept
		{
			if (ptr == nullptr) return last;
			return ptr->prev;
		}

		node_pointer next(node_pointer ptr) const noexcept
		{
			return ptr->next;
		}

		reference data(node_pointer ptr) const noexcept
		{
			return ptr->data;
		}

		// Element acces

		const_reference front() const
		{
			return first->data;
		}

		const_reference back() const
		{
			return last->data;
		}

		// Capacity

		size_t size() const noexcept
		{
			return nr;
		}

		bool Empty() const noexcept
		{
			return first == nullptr;
		}

		operator bool() const noexcept
		{
			return !this->Empty();
		}


		// Modifiers

		void erase(Node* p)
		{
			if (!p || !first) return;

			if (first->next == nullptr)
			{
				delete first;
				first = last = nullptr;
				nr = 0;
				return;
			}

			if (p == first)
			{
				first = first->next;
				delete p;
				first->prev = nullptr;
				nr--;
				return;
			}

			if (p == last)
			{
				last = last->prev;
				last->next = nullptr;
				delete p;
				nr--;
				return;
			}

			p->prev->next = p->next;
			p->next->prev = p->prev;
			nr--;
			delete p;
		}

		void insertAfter(Node* p, const_reference val)
		{
			if (first == nullptr && p == nullptr)
			{
				first = last = new Node(nullptr, val, nullptr);
				nr++;
				return;
			}

			if (p == nullptr) return;

			if (p->next == nullptr)
			{
				last = last->next = new Node(last, val, nullptr);
				nr++;
				return;
			}

			nr++;
			p->next = new Node(p, val, p->next);
			p->next->next->prev = p->next;
		}

		void insertBefore(Node* p, const_reference val)
		{
			if (first == nullptr && p == nullptr)
			{
				first = last = new Node(nullptr, val, nullptr);
				nr++;
				return;
			}

			if (p == nullptr) return;

			if (p == first)
			{
				first = first->prev = new Node(nullptr, val, first);
				nr++;
				return;
			}

			nr++;
			p->prev = new Node(p->prev, val, p);
			p->prev->prev->next = p->prev;
		}

		void clear()
		{
			Free();
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



	private:

		void Free()
		{
			if (first == nullptr && last == nullptr) 
				return;

			nr = 0;
			for (Node* p = first, *aux; p != nullptr; p = aux)
			{
				aux = p->next;
				delete p;
			}

			first = last = nullptr;
		}

		void Copy(List const& list)
		{
			if (!this->Empty()) Free();
			for (Node* p = list.first; p; p = p->next)
				this->push_back(p->data);
		}

		void Move(List& list)
		{
			first = list.first;
			last = list.last;
			list.first = list.last = nullptr;
			list.~List();
			list.nr = 0;
		}

	};

}