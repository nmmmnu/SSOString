#ifndef _MYSTRING_H
#define _MYSTRING_H

#include <memory>
#include <string.h>

class String{
private:
	constexpr
	static size_t SIZE = 2 * sizeof(void *) - 1;

	constexpr static char TERM_LOCAL	= 0;
	constexpr static char TERM_PTR		= 1;

public:
	String() = default;

	String(const char *s);

	String(const String & other);

	String(String && other);

	String & operator=(String other);

	~String();


	const char *c_str() const;
	const char *c_nstr() const;

	int cmp(const String & other) const;

	size_t size() const;

	operator bool() const;
	operator const char *() const;

	char operator [] (size_t pos) const;

	bool operator == (const String & other) const;
	bool operator != (const String & other) const;
	bool operator >  (const String & other) const;
	bool operator >= (const String & other) const;
	bool operator <  (const String & other) const;
	bool operator <= (const String & other) const;

private:
	union Buffer{
		char *ptr;
		char  local[SIZE];
	};

	Buffer _buff;
	char _terminator;

private:
	static const char *__NULLSTR;
};

// ==============================

inline const char *String::c_str() const{
	if (_terminator == TERM_LOCAL)
		return _buff.local[0] ? _buff.local : nullptr;

	return _buff.ptr;
}

inline const char *String::c_nstr() const{
	auto s = c_str();
	return s ? s : __NULLSTR;
}

inline int String::cmp(const String & other) const{
	return strcmp( c_nstr(), other.c_nstr() );
}

inline size_t String::size() const{
	return strlen( c_nstr() );
}



inline String::operator bool() const{
	return c_str();
}

inline String::operator const char *() const{
	return c_str();
}



inline char String::operator [] (size_t pos) const{
	return pos >= size() ? 0 : c_str() [pos];
}

inline bool String::operator == (const String & other) const{
	return cmp(other) == 0;
}

inline bool String::operator != (const String & other) const{
	return cmp(other) != 0;
}

inline bool String::operator >  (const String & other) const{
	return cmp(other) > 0;
}

inline bool String::operator >= (const String & other) const{
	return cmp(other) >= 0;
}

inline bool String::operator <  (const String & other) const{
	return cmp(other) < 0;
}

inline bool String::operator <= (const String & other) const{
	return cmp(other) <= 0;
}

#endif
