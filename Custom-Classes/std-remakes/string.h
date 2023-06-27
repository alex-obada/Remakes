#ifndef STRING_
#define STRING_
#define _CRT_SECURE_NO_WARNINGS 1

#include "../globals.h"

#include <cstring>
#include <iostream>

_COX_BEGIN

class string
{
public:
	string() = default;
	string(const char* arr);
	string(string const& other);
	string(string&& other) noexcept;
	~string();

	string operator + (string const& other) const noexcept;
	string operator + (const char* other) const noexcept;
	string& operator += (string const& other);
	string& operator += (const char* other);
	string& operator = (string const& other);
	string& operator = (string&& other) noexcept;
	string& operator = (const char* arr);
	const char& operator [] (size_t index) const noexcept;
	char& operator [] (size_t index);
	std::strong_ordering operator <=> (string const& other) const noexcept;
	bool operator ==(string const& other) const noexcept;

	friend std::istream& operator >> 
		(std::istream& in, string& s) noexcept;
	friend std::ostream& operator << 
		(std::ostream& out, string const& s) noexcept;

	size_t find(char const& ch) const noexcept;
	size_t rfind(char const& ch) const noexcept;

	void swap(string& other) noexcept;
	void push_back(char& ch) noexcept;
	void pop_back() noexcept;
	void erase(size_t index, size_t count) noexcept;
	int compare(string const& other) const noexcept;
		
	const char* data() const noexcept;
	const char* c_str() const noexcept;
	char& front() const noexcept;
	char& back() const noexcept;

	bool empty() const noexcept;
	size_t size() const noexcept;
	size_t lenght() const noexcept;
	size_t capacity() const noexcept;


private:
	void CheckSize();
	void Alocate(size_t alloc);

	size_t len = 0;
	size_t allocated = 0;
	char* buffer = nullptr;
};

_COX_END

#endif
