#include "string.h"

namespace cox {

	string::string(const char* arr)
	{
		len = strlen(arr);
		CheckSize();
		if (buffer != nullptr)
			strcpy(buffer, arr);

	}

	string::string(string const& other) : len{ other.size() }
	{
		CheckSize();
		if(buffer != nullptr)
			strcpy(buffer, other.buffer);
	}

	string::string(string&& other) noexcept
		: len{ other.size() }, allocated{ other.allocated }
	{
		delete[] buffer;
		buffer = other.buffer;
		other.buffer = nullptr;
	}

	string string::operator+(string const& other) const noexcept
	{
		string copy = *this;
		copy += other;
		
		return copy;
	}

	string string::operator+(const char* other) const noexcept
	{
		string copy = *this;
		copy += other;

		return copy;
	}

	string& string::operator+=(string const& other)
	{
		len += other.size();
		CheckSize();
		strcat(buffer, other.buffer);
		return *this;

	}

	string& string::operator+=(const char* other)
	{
		len += strlen(other);
		CheckSize();
		strcat(buffer, other);
		return *this;

	}

	string& string::operator=(string const& other)
	{
		len = other.size();
		CheckSize();
		strcpy(buffer, other.buffer);
		return *this;
	}

	string& string::operator=(string&& other) noexcept
	{
		len = other.size();
		allocated = other.allocated;
		delete[] buffer;
		buffer = other.buffer;
		other.buffer = nullptr;
		return *this;
	}

	cox::string& string::operator=(const char* arr)
	{
		len = strlen(arr);
		CheckSize();
		strcpy(buffer, arr);
		return *this;
	}

	const char& string::operator[](size_t index) const
	{
		// exceptie pt index > len
		return buffer[index];
	}

	char& string::operator[](size_t index)
	{
		// exceptie pt index > len
		return buffer[index];
	}

	bool string::operator==(string const& other) const noexcept
	{
		if (this->len != other.len)
			return false;

		char* a = buffer;
		char* b = other.buffer;

		for (size_t i = 0; a[i]; ++i)
			if (a[i] != b[i])
				return false;

		return true;
	}

	std::strong_ordering string::operator<=>(string const& other) const noexcept
	{
		char* a = buffer;
		char* b = other.buffer;
		size_t i = 0;
		for ( ; a[i] && b[i]; ++i)
			if (a[i] != b[i])
				return a[i] <=> b[i];

		return a[i] <=> b[i];

	}

	size_t string::find(char const& ch) const noexcept
	{
		for (size_t i = 0; buffer[i]; ++i)
			if (buffer[i] == ch)
				return i;
		return -1;
	}

	size_t string::rfind(char const& ch) const noexcept
	{
		for (int i = (int)len - 1; i >= 0; --i)
			if (buffer[i] == ch)
				return i;
		return -1;
	}

	void string::swap(string& other) noexcept
	{
		std::swap(buffer, other.buffer);
		std::swap(len, other.len);
		std::swap(allocated, other.allocated);
	}

	void string::push_back(char& ch) noexcept
	{
		++len;
		CheckSize();
		buffer[len - 1] = ch;
	}

	void string::pop_back() noexcept
	{ --len; }


	void string::erase(size_t index, size_t count) noexcept
	{
		if (index > len - 1) return;

		char* temp = new char[allocated];
		strncpy(temp, buffer, index);
		temp[index] = '\0';

		if (index + count < len - 1)
			strcpy(temp + index - 1, buffer + index + count - 1);

		delete[] buffer;
		buffer = temp;
	}

	int string::compare(string const& other) const noexcept
	{ return strcmp(buffer, other.buffer); }

	bool string::empty() const noexcept
	{
		if(len == 0)
			return false;
		return true;
	}

	const char* string::data() const noexcept
	{ return buffer; }

	const char* string::c_str() const noexcept
	{ return buffer; }

	char& string::front() const noexcept
	{ return buffer[0]; }

	char& string::back() const noexcept
	{ return buffer[len - 1]; }

	size_t string::size() const noexcept
	{ return len; }

	size_t string::lenght() const noexcept
	{ return len; }

	size_t string::capacity() const noexcept
	{ return allocated; }

	string::~string()
	{ delete[] buffer; }

	void string::CheckSize()
	{
		if (allocated <= len)
			Alocate(len + len / 2 + 1);
	}

	void string::Alocate(size_t alloc)
	{
		allocated = alloc;

		char* newBuffer = new char[allocated];
		
		if(buffer != nullptr)
			strcpy(newBuffer, buffer);

		delete[] buffer;
		buffer = newBuffer;
	}

	std::istream& operator>>
		(std::istream& in, string& s) noexcept
	{
		char* temp = new char[100001];
		in.getline(temp, 100001);
		
		s.buffer = temp;
		temp = nullptr;

		s.allocated = s.len = 100001;
		
		return in;

	}

	std::ostream& operator<<
		(std::ostream& out, string const& s) noexcept
	{
		return out << s.buffer;
	}

};