#pragma once

#include "Core/Platform.h"

#include <string>
#include <vector>

// Readability Macros
#define ETL_INTERNAL_REPEAT_TYPENAME(x) typedef typename string_type::x x
#define ETL_INTERNAL_OPERATOR(x) friend bool operator x (const extended_string& lhs, const extended_string& rhs) { return lhs.m_String x rhs.m_String; }\
friend bool operator x (const extended_string& lhs, const string_type& rhs) { return lhs.m_String x rhs; }\
friend bool operator x (const string_type& lhs, const extended_string& rhs) { return lhs x rhs.m_String; }\
friend bool operator x (const extended_string& lhs, const charT* rhs) { return lhs.m_String x rhs; }\
friend bool operator x (const charT* lhs, const extended_string& rhs) { return lhs x rhs.m_String; }
#define ETL_INTERNAL_ITER(x, y) x y () ETL_NOEXCEPT { return m_String.y (); }\
const_ ## x y () const ETL_NOEXCEPT { return m_String.y (); }\
const_ ## x c ## y () const ETL_NOEXCEPT { return m_String.c ## y (); }
#define ETL_INTERNAL_TEMPLATE_DEF template<class charT, class traits, class Alloc>
#define ETL_INTERNAL_PARAM_STRING extended_string<charT, traits, Alloc>

namespace ETL
{
namespace STLExtensions
{
	template<class charT>
	const charT* new_line();

	template<class charT, class traits = std::char_traits<charT>, class Alloc = std::allocator<charT>>
	class extended_string
	{
	public:
		typedef std::basic_string<charT, traits, Alloc> string_type;
		ETL_INTERNAL_REPEAT_TYPENAME(traits_type);
		ETL_INTERNAL_REPEAT_TYPENAME(allocator_type);
		ETL_INTERNAL_REPEAT_TYPENAME(value_type);
		ETL_INTERNAL_REPEAT_TYPENAME(reference);
		ETL_INTERNAL_REPEAT_TYPENAME(const_reference);
		ETL_INTERNAL_REPEAT_TYPENAME(pointer);
		ETL_INTERNAL_REPEAT_TYPENAME(const_pointer);
		ETL_INTERNAL_REPEAT_TYPENAME(iterator);
		ETL_INTERNAL_REPEAT_TYPENAME(const_iterator);
		ETL_INTERNAL_REPEAT_TYPENAME(reverse_iterator);
		ETL_INTERNAL_REPEAT_TYPENAME(const_reverse_iterator);
		ETL_INTERNAL_REPEAT_TYPENAME(difference_type);
		ETL_INTERNAL_REPEAT_TYPENAME(size_type);
		static const size_type npos = -1;

		// constructor
		explicit extended_string(const allocator_type& alloc = allocator_type()) : m_String(alloc) { }
		extended_string(const extended_string& str) : m_String(str.m_String) { }
		extended_string(const string_type& str) : m_String(str) { }
		extended_string(const extended_string& str, const allocator_type& alloc) : m_String(str.m_String, alloc) { }
		extended_string(const string_type& str, const allocator_type& alloc) : m_String(str, alloc) { }
		extended_string(const extended_string& str, size_type pos, size_type len = npos, const allocator_type alloc = allocator_type()) : m_String(str.m_String, pos, len, alloc) { }
		extended_string(const string_type& str, size_type pos, size_type len = npos, const allocator_type alloc = allocator_type()) : m_String(str, pos, len, alloc) { }
		extended_string(const charT* s, const allocator_type& alloc = allocator_type()) : m_String(s, alloc) { }
		extended_string(const charT* s, size_type n, const allocator_type& alloc = allocator_type()) : m_String(s, n, alloc) { }
		extended_string(size_type n, charT c, const allocator_type& alloc = allocator_type()) : m_String(n, c, alloc) { }
		template<typename InputIterator>
		extended_string(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : m_String(first, last, alloc) { }
		extended_string(std::initializer_list<charT> il, const allocator_type& alloc = allocator_type()) : m_String(il, alloc) { }
		extended_string(extended_string&& str) ETL_NOEXCEPT : m_String(str.m_String) { }
		extended_string(string_type&& str) ETL_NOEXCEPT : m_String(str) { }
		extended_string(extended_string&& str, const allocator_type& alloc) : m_String(str.m_String, alloc) { }
		extended_string(string_type&& str, const allocator_type& alloc) : m_String(str, alloc) { }

		// destructor
		virtual ~extended_string() { }

		// ETL_INTERNAL_OPERATOR=
		extended_string& operator=(const extended_string& str)
		{
			m_String = str.m_String;
			return *this;
		}

		extended_string& operator=(const string_type& str)
		{
			m_String = str;
			return *this;
		}

		extended_string& operator=(const charT* s)
		{
			m_String = s;
			return *this;
		}

		extended_string& operator=(charT c)
		{
			m_String = c;
			return *this;
		}

		extended_string& operator=(std::initializer_list<charT> il)
		{
			m_String = il;
			return *this;
		}

		extended_string& operator=(extended_string&& str) ETL_NOEXCEPT
		{
			m_String = str.m_String;
			return *this;
		}

		extended_string& operator=(string_type&& str) ETL_NOEXCEPT
		{
			m_String = str;
			return *this;
		}

		// begin cbegin
		ETL_INTERNAL_ITER(iterator, begin)
		// end cend
		ETL_INTERNAL_ITER(iterator, end)
		// rbegin crbegin
		ETL_INTERNAL_ITER(reverse_iterator, rbegin)
		// rend crend
		ETL_INTERNAL_ITER(reverse_iterator, rend)

		// size
		size_type size() const ETL_NOEXCEPT { return m_String.size(); }
		// length
		size_type length() const ETL_NOEXCEPT { return m_String.length(); }
		// max_size
		size_type max_size() const ETL_NOEXCEPT { return m_String.max_size(); }
		// resize
		void resize(size_type n) { m_String.resize(n); }
		void resize(size_type n, charT c) { m_String.resize(n, c); }
		// capacity
		size_type capacity() const ETL_NOEXCEPT { return m_String.capacity(); }
		// reserve
		void reserve(size_type n = 0) { m_String.reserve(n); }
		// clear
		void clear() ETL_NOEXCEPT { m_String.clear(); }
		// empty
		bool empty() const ETL_NOEXCEPT { return m_String.empty(); }
		// shrink_to_fit
		void shrink_to_fit() { m_String.shrink_to_fit(); }
		// ETL_INTERNAL_OPERATOR[]
		reference operator[](size_type pos) { return m_String[pos]; }
		const_reference operator[](size_type pos) const { return m_String[pos]; }
		// at
		reference at(size_type pos) { return m_String.at(pos); }
		const_reference at(size_type pos) const { return m_String.at(pos); }
		// back
		charT& back() { return m_String.back(); }
		const charT& back() const { return m_String.back(); }
		// front
		charT& front() { return m_String.front(); }
		const charT& front() const { return m_String.front(); }

		// operator+=
		extended_string& operator+=(const extended_string& str) { m_String += str.m_String; return *this; }
		extended_string& operator+=(const string_type& str) { m_String += str; return *this; }
		extended_string& operator+=(const charT* s) { m_String += s; return *this; }
		extended_string& operator+=(charT c) { m_String += c; return *this; }
		extended_string& operator+=(std::initializer_list<charT> il) { m_String += il; return *this; }

		// append
		extended_string& append(const extended_string& str) { m_String.append(str.m_String); return *this; }
		extended_string& append(const string_type& str) { m_String.append(str); return *this; }
		extended_string& append(const extended_string& str, size_type subpos, size_type sublen)
		{
			m_String.append(str.m_String, subpos, sublen);
			return *this;
		}
		extended_string& append(const string_type& str, size_type subpos, size_type sublen)
		{
			m_String.append(str, subpos, sublen);
			return *this;
		}
		extended_string& append(const charT* s) { m_String.append(s); return *this; }
		extended_string& append(const charT* s, size_type n) { m_String.append(s, n); return *this; }
		extended_string& append(size_type n, charT c) { m_String.append(n, c); return *this; }
		template<class InputIterator>
		extended_string& append(InputIterator first, InputIterator last)
		{
			m_String.append(first, last);
			return *this;
		}
		extended_string& append(std::initializer_list<charT> il) { m_String.append(il); return *this; }

		// push_back
		void push_back(charT c) { m_String.push_back(c); }

		// assign
		extended_string& assign(const extended_string& str) { m_String.assign(str.m_String); return *this; }
		extended_string& assign(const string_type& str) { m_String.assign(str); return *this; }
		extended_string& assign(const charT* s) { m_String.assign(s); return *this; }
		extended_string& assign(const charT* s, size_type n) { m_String.assign(s, n); return *this; }
		extended_string& assign(size_type n, charT c) { m_String.assign(n, c); return *this; }
		template<class InputIterator>
		extended_string& assign(InputIterator first, InputIterator last)
		{
			m_String.assign(first, last);
			return *this;
		}
		extended_string& assign(std::initializer_list<charT> il) { m_String.assign(il); return *this; }
		extended_string& assign(extended_string&& str) ETL_NOEXCEPT { m_String.assign(str.m_String); return *this; }
		extended_string& assign(string_type&& str) ETL_NOEXCEPT { m_String.assign(str); return *this; }

		// insert
		extended_string& insert(size_type pos, const extended_string& str) { m_String.insert(pos, str.m_String); return *this; }
		extended_string& insert(size_type pos, const string_type& str) { m_String.insert(pos, str); return *this; }
		extended_string& insert(size_type pos, const extended_string& str, size_type subpos, size_type sublen)
		{
			m_String.insert(pos, str.m_String, subpos, sublen);
			return *this;
		}
		extended_string& insert(size_type pos, const string_type & str, size_type subpos, size_type sublen)
		{
			m_String.insert(pos, str, subpos, sublen);
			return *this;
		}
		extended_string& insert(size_type pos, const charT* s) { m_String.insert(pos, s); return *this; }
		extended_string& insert(size_type pos, const charT* s, size_type n) { m_String.insert(pos, s, n); return *this; }
		extended_string& insert(size_type pos, size_type n, charT c) { m_String.insert(pos, n, c); return *this; }
		iterator insert(const_iterator p, size_type n, charT c) { return m_String.insert(p, n, c); }
		iterator insert(const_iterator p, charT c) { return m_String.insert(p, c); }
		template<class InputIterator>
		iterator insert(iterator p, InputIterator first, InputIterator last)
		{
			return m_String.insert(p, first, last);
		}
		extended_string& insert(const_iterator p, std::initializer_list<charT> il) { m_String.insert(p, il); return *this; }

		// erase
		extended_string& erase(size_type pos = 9, size_type len = npos) { m_String.erase(pos, npos); return *this; }
		iterator erase(const_iterator p) { return m_String.erase(p); }
		iterator erase(const_iterator first, const_iterator last) { return m_String.erase(first, last); }

		// replace
		extended_string& replace(size_type pos, size_type len, const extended_string& str) { m_String.replace(pos, len, str.m_String); return *this; }
		extended_string& replace(size_type pos, size_type len, const string_type& str) { m_String.replace(pos, len, str); return *this; }
		extended_string& replace(const_iterator i1, const_iterator i2, const extended_string& str)
		{
			m_String.replace(i1, i2, str.m_String);
			return *this;
		}
		extended_string& replace(const_iterator i1, const_iterator i2, const string_type& str)
		{
			m_String.replace(i1, i2, str);
			return *this;
		}
		extended_string& replace(size_type pos, size_type len, const extended_string& str, size_type subpos, size_type sublen)
		{
			m_String.replace(pos, len, str.m_String, subpos, sublen);
			return *this;
		}
		extended_string& replace(size_type pos, size_type len, const string_type& str, size_type subpos, size_type sublen)
		{
			m_String.replace(pos, len, str, subpos, sublen);
			return *this;
		}
		extended_string& replace(size_type pos, size_type len, const charT* s) { m_String.replace(pos, len, s); return *this; }
		extended_string& replace(const_iterator i1, const_iterator i2, const charT* s) { m_String.replace(i1, i2, s); return *this; }
		extended_string& replace(size_type pos, size_type len, const charT* s, size_type n)
		{
			m_String.replace(pos, len, s, n);
			return *this;
		}
		extended_string& replace(const_iterator i1, const_iterator i2, const charT* s, size_type n)
		{
			m_String.replace(i1, i2, s, n);
			return *this;
		}
		extended_string& replace(size_type pos, size_type len, size_type n, charT c) { m_String.replace(pos, len, n, c); return *this; }
		extended_string& replace(const_iterator i1, const_iterator i2, size_type n, charT c)
		{
			m_String.replace(i1, i2, n, c);
			return *this;
		}
		template<class InputIterator>
		extended_string& replace(const_iterator i1, const_iterator i2, InputIterator first, InputIterator last)
		{
			m_String.replace(i1, i2, first, last);
			return *this;
		}
		extended_string& replace(const_iterator i1, const_iterator i2, std::initializer_list<charT> il)
		{
			m_String.replace(i1, i2, il);
			return *this;
		}

		// swap
		void swap(extended_string& str) { m_String.swap(str.m_String); }
		void swap(string_type& str) { m_String.swap(str); }
		// pop_back
		void pop_back() { m_String.pop_back(); }
		// c_str
		const charT* c_str() const ETL_NOEXCEPT { return m_String.c_str(); }
		// data
		const charT* data() const ETL_NOEXCEPT { return m_String.data(); }
		// get_allocator
		allocator_type get_allocator() const ETL_NOEXCEPT { return m_String.get_allocator(); }
		// copy
		size_type copy(charT* s, size_type len, size_type pos = 0) const { return m_String.copy(s, len, pos); }

		// find
		size_type find(const extended_string& str, size_type pos = 0) const ETL_NOEXCEPT { return m_String.find(str.m_String, pos); }
		size_type find(const string_type& str, size_type pos = 0) const ETL_NOEXCEPT { return m_String.find(str, pos); }
		size_type find(const charT* s, size_type pos = 0) const { return m_String.find(s, pos); }
		size_type find(const charT* s, size_type pos, size_type n) const { return m_String.find(s, pos, n); }
		size_type find(charT c, size_type pos = 0) const ETL_NOEXCEPT { return m_String.find(c, pos); }

		// rfind
		size_type rfind(const extended_string& str, size_type pos = npos) const ETL_NOEXCEPT { return m_String.rfind(str.m_String, pos); }
		size_type rfind(const string_type& str, size_type pos = npos) const ETL_NOEXCEPT { return m_String.rfind(str, pos); }
		size_type rfind(const charT* s, size_type pos = npos) const { return m_String.rfind(s, pos); }
		size_type rfind(const charT* s, size_type pos, size_type n) const { return m_String.rfind(s, pos, n); }
		size_type rfind(charT c, size_type pos = npos) const ETL_NOEXCEPT { return m_String.rfind(c, pos); }

		// find_first_of
		size_type find_first_of(const extended_string& str, size_type pos = 0) const ETL_NOEXCEPT { return m_String.find_first_of(str.m_String, pos); }
		size_type find_first_of(const string_type& str, size_type pos = 0) const ETL_NOEXCEPT { return m_String.find_first_of(str, pos); }
		size_type find_first_of(const charT* s, size_type pos = 0) const { return m_String.find_first_of(s, pos); }
		size_type find_first_of(const charT* s, size_type pos, size_type n) const { return m_String.find_first_of(s, pos, n); }
		size_type find_first_of(charT c, size_type pos = 0) const ETL_NOEXCEPT { return m_String.find_first_of(c, pos); }

		// find_last_of
		size_type find_last_of(const extended_string& str, size_type pos = npos) const ETL_NOEXCEPT { return m_String.find_last_of(str.m_String, pos); }
		size_type find_last_of(const string_type& str, size_type pos = npos) const ETL_NOEXCEPT { return m_String.find_last_of(str, pos); }
		size_type find_last_of(const charT* s, size_type pos = npos) const { return m_String.find_last_of(s, pos); }
		size_type find_last_of(const charT* s, size_type pos, size_type n) const { return m_String.find_last_of(s, pos, n); }
		size_type find_last_of(charT c, size_type pos = npos) const ETL_NOEXCEPT { return m_String.find_last_of(c, pos); }

		// find_first_not_of
		size_type find_first_not_of(const extended_string& str, size_type pos = 0) const ETL_NOEXCEPT { return m_String.find_first_not_of(str.m_String, pos); }
		size_type find_first_not_of(const string_type& str, size_type pos = 0) const ETL_NOEXCEPT { return m_String.find_first_not_of(str, pos); }
		size_type find_first_not_of(const charT* s, size_type pos = 0) const { return m_String.find_first_not_of(s, pos); }
		size_type find_first_not_of(const charT* s, size_type pos, size_type n) const { return m_String.find_first_not_of(s, pos, n); }
		size_type find_first_not_of(charT c, size_type pos = 0) const ETL_NOEXCEPT { return m_String.find_first_not_of(c, pos); }

		// find_last_not_of
		size_type find_last_not_of(const extended_string& str, size_type pos = npos) const ETL_NOEXCEPT { return m_String.find_last_not_of(str.m_String, pos); }
		size_type find_last_not_of(const string_type& str, size_type pos = npos) const ETL_NOEXCEPT { return m_String.find_last_not_of(str, pos); }
		size_type find_last_not_of(const charT* s, size_type pos = npos) const { return m_String.find_last_not_of(s, pos); }
		size_type find_last_not_of(const charT* s, size_type pos, size_type n) const { return m_String.find_last_not_of(s, pos, n); }
		size_type find_last_not_of(charT c, size_type pos = npos) const ETL_NOEXCEPT { return m_String.find_last_not_of(c, pos); }

		// substr
		extended_string substr(size_type pos = 0, size_type len = npos) const { return extended_string(m_String.substr(pos, len)); }

		// compare
		int compare(const extended_string& str) const ETL_NOEXCEPT { return m_String.compare(str.m_String); }
		int compare(const string_type& str) const ETL_NOEXCEPT { return m_String.compare(str); }
		int compare(size_type pos, size_type len, const extended_string& str) { return m_String.compare(pos, len, str.m_String); }
		int compare(size_type pos, size_type len, const string_type& str) { return m_String.compare(pos, len, str); }
		int compare(size_type pos, size_type len, const extended_string& str, size_type subpos, size_type sublen) const
		{
			return m_String.compare(pos, len, str.m_String, subpos, sublen);
		}
		int compare(size_type pos, size_type len, const string_type& str, size_type subpos, size_type sublen) const
		{
			return m_String.compare(pos, len, str, subpos, sublen);
		}
		int compare(const charT* s) const { return m_String.compare(s); }
		int compare(size_type pos, size_type len, const charT* s) const { return m_String.compare(pos, len, s); }
		int compare(size_type pos, size_type len, const charT* s, size_type n) const { return m_String.compare(pos, len, s, n); }

		// operator+
		friend extended_string operator+(const extended_string& lhs, const extended_string& rhs) { return extended_string(lhs.m_String + rhs.m_String); }
		friend extended_string operator+(const extended_string& lhs, const string_type& rhs) { return extended_string(lhs.m_String + rhs); }
		friend extended_string operator+(const string_type& lhs, const extended_string& rhs) { return extended_string(lhs + rhs.m_String()); }

		friend extended_string operator+(extended_string&& lhs, extended_string&& rhs) { return extended_string(lhs.m_String + rhs.m_String); }
		friend extended_string operator+(extended_string&& lhs, string_type&& rhs) { return extended_string(lhs.m_String + rhs); }
		friend extended_string operator+(string_type&& lhs, extended_string&& rhs) { return extended_string(lhs + rhs.m_String); }

		friend extended_string operator+(extended_string&& lhs, const extended_string& rhs) { return extended_string(lhs.m_String + rhs.m_String); }
		friend extended_string operator+(extended_string&& lhs, const string_type& rhs) { return extended_string(lhs.m_String + rhs); }
		friend extended_string operator+(string_type&& lhs, const extended_string& rhs) { return extended_string(lhs + rhs.m_String); }

		friend extended_string operator+(const extended_string& lhs, extended_string&& rhs) { return extended_string(lhs.m_String + rhs.m_String); }
		friend extended_string operator+(const extended_string& lhs, string_type&& rhs) { return extended_string(lhs.m_String + rhs.m_String); }
		friend extended_string operator+(const string_type& lhs, extended_string&& rhs) { return extended_string(lhs + rhs.m_String); }

		friend extended_string operator+(const extended_string& lhs, const charT* rhs) { return extended_string(lhs.m_String + rhs); }
		friend extended_string operator+(extended_string&& lhs, const charT* rhs) { return extended_string(lhs.m_String + rhs); }
		friend extended_string operator+(const charT* lhs, const extended_string& rhs) { return extended_string(lhs + rhs.m_String); }
		friend extended_string operator+(const charT* lhs, extended_string&& rhs) { return extended_string(lhs + rhs.m_String); }

		friend extended_string operator+(const extended_string& lhs, charT rhs) { return extended_string(lhs.m_String + rhs); }
		friend extended_string operator+(extended_string&& lhs, charT rhs) { return extended_string(lhs.m_String + rhs); }
		friend extended_string operator+(charT lhs, const extended_string& rhs) { return extended_string(lhs + rhs.m_String); }
		friend extended_string operator+(charT lhs, extended_string&& rhs) { return extended_string(lhs + rhs.m_String); }

		// operator==
		ETL_INTERNAL_OPERATOR(== )
		// operator!=
		ETL_INTERNAL_OPERATOR(!= )
		// operator<
		ETL_INTERNAL_OPERATOR(< )
		// operator<=
		ETL_INTERNAL_OPERATOR(<= )
		// operator>
		ETL_INTERNAL_OPERATOR(> )
		// operator>=
		ETL_INTERNAL_OPERATOR(>= )

		// swap
		friend void swap(extended_string& x, extended_string& y) { std::swap(x.m_String, y.m_String); }
		friend void swap(extended_string& x, string_type& y) { std::swap(x.m_String, y); }
		friend void swap(string_type& x, extended_string& y) { std::swap(x, y.m_String); }
		
#if ETL_MSVC
		// ETL_INTERNAL_OPERATOR>>
		friend std::basic_istream<charT, traits>& operator>>(std::basic_istream<charT, traits>& is, extended_string& str) { return is >> str.m_String; }
		// ETL_INTERNAL_OPERATOR<<
		friend std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& os, extended_string& str) { return os << str.m_String; }
#else
		// ETL_INTERNAL_OPERATOR>>
		friend std::basic_istream<charT, traits>& operator>>(std::basic_istream<charT, traits>& is, const extended_string& str) { return is >> str.m_String; }
		// ETL_INTERNAL_OPERATOR<<
		friend std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& os, const extended_string& str) { return os << str.m_String; }
#endif
		
		// getline
		friend std::basic_istream<charT, traits>& getline(std::basic_istream<charT, traits>& is, extended_string& str, charT delim) { return getline(is, str.m_String, delim); }
		friend std::basic_istream<charT, traits>& getline(std::basic_istream<charT, traits>&& is, extended_string& str, charT delim) { return getline(is, str.m_String, delim); }
		friend std::basic_istream<charT, traits>& getline(std::basic_istream<charT, traits>& is, extended_string& str) { return getline(is, str.m_String); }
		friend std::basic_istream<charT, traits>& getline(std::basic_istream<charT, traits>&& is, extended_string& str) { return getline(is, str.m_String); }

		//////////////////////////////////////////////////////////////////////////
		// Added functions
		//////////////////////////////////////////////////////////////////////////
		
		// split
		std::vector<extended_string> split(charT delim, bool keep_delim = false) const;
		std::vector<extended_string> split(const charT* delims, bool keep_delims = false) const;
		std::vector<extended_string> split(const extended_string& delims, bool keep_delims = false) const
		{
			return split(delims.c_str(), keep_delims);
		}
		std::vector<extended_string> split(const string_type& delims, bool keep_delims = false) const
		{
			return split(delims.c_str(), keep_delims);
		}

		// split_lines
		std::vector<extended_string> split_lines(bool keep_line_ends = false) const
		{
			return split(new_line<charT>(), keep_line_ends);
		}

	protected:
		std::basic_string<charT> m_String;

		bool char_in_str(charT c, const charT* s, size_type len) const;
		size_type string_length(const charT* s) const
		{
			const charT nullTerminator = (charT)0;
			size_type len = 0;
			while (s[len] != nullTerminator)
			{
				++len;
			}
			return len;
		}
	};

	template<>
	const char* new_line();
	template<>
	const wchar_t* new_line();
	template<>
	const char16_t* new_line();
	template<>
	const char32_t* new_line();
}
}


#include "extended_string.hpp"

#undef ETL_INTERNAL_REPEAT_TYPENAME
#undef ETL_INTERNAL_OPERATOR
#undef ETL_INTERNAL_ITER
#undef ETL_INTERNAL_TEMPLATE_DEF
#undef ETL_INTERNAL_PARAM_STRING