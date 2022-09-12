#pragma once

namespace cox {

	template <class Container>
	class Iterator {
	public:

		using pointer	      = Container::pointer;			/// T*
		using node_pointer    = Container::node_pointer;		/// Node*
		using reference	      = Container::reference;			/// T&
		using const_reference = Container::const_reference;    /// const T&

		Iterator(Container& c, node_pointer ptr) :
			c {c}, ptr {ptr} 
		{}

		Iterator& operator++ ()
		{
			ptr = c.next(ptr);
			return *this;
		}

		Iterator& operator-- ()
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

		bool operator == (Iterator const& other) const noexcept
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

};