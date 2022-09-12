#pragma once

namespace cox {

	template <typename Container>
	class Iterator {
	public:

		using pointer	      = typename Container::pointer;			/// T*
		using node_pointer    = typename Container::node_pointer;		/// Node*
		using reference	      = typename Container::reference;			/// T&
		using const_reference = typename Container::const_reference;    /// const T&

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

	private:
		Container& c;
		node_pointer ptr;
	};

};