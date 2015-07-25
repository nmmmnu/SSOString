#include "string.h"

const char *String::__NULLSTR = "";

// ==============================

String::String(const char *s){
	if (s == nullptr){
		_terminator = TERM_LOCAL;
		_buff.local[0] = '\0'; // the NULL terminator.

		return;
	}

	const size_t size = strlen(s);

	if (size <= SIZE){
		_terminator = TERM_LOCAL;
		// if size == SIZE,
		// _terminator will serve as the NULL terminator
		// strncpy(_buff.local, s, size == SIZE ? size : size + 1);
		strcpy(_buff.local, s);
	}else{
		_terminator = TERM_PTR;
		_buff.ptr   = strdup(s); // doing malloc()
	}
}

String::String(const String & other) :
		String( other.c_str() ){};

String::String(String && other){
	_buff       = other._buff;
	_terminator = other._terminator;

	other._terminator = TERM_LOCAL;
}

String & String::operator=(String other){
	std::swap(_buff, other._buff);
	std::swap(_terminator, other._terminator);
	return *this;
}

String::~String(){
	if (_terminator == TERM_PTR)
		free(_buff.ptr);
}

// ==============================















void p(String &s){
	printf("%s\n", s ? (const char *) s : "[null]");
}

int main(){
	String s1;			p(s1);
	String s2  = { "hello" };	p(s2);
	String s3a = s2;		p(s3a);
	String s3  = std::move(s3a);	p(s3);
	s1 = s3;			p(s1);
	s1 = "hi";			p(s1);

	String a = "aaaa";
	String b = "bbbb";
	String c = "aaaa";

	printf("%s %s\n", a == c ? "Y" : "N", "Y");
	printf("%s %s\n", a == b ? "Y" : "N", "N");
	printf("%s %s\n", a != b ? "Y" : "N", "Y");
	printf("%s %s\n", a <  b ? "Y" : "N", "Y");
	printf("%s %s\n", a >  b ? "Y" : "N", "N");
	printf("%s %s\n", a <= b ? "Y" : "N", "Y");
	printf("%s %s\n", a >= b ? "Y" : "N", "N");
	printf("%s %s\n", a <= c ? "Y" : "N", "Y");
	printf("%s %s\n", a >= c ? "Y" : "N", "Y");

	printf(">%s %s\n", s1[0] == 'h' ? "Y" : "N", "Y");
	printf(">%s %s\n", s1[1] == 'i' ? "Y" : "N", "Y");
	printf(">%s %s\n", s1[2] ==  0  ? "Y" : "N", "Y");

	printf("%zu\n", sizeof(String));
	return 0;
}

