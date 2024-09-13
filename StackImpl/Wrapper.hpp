#pragma once
#include <ctime>
#include <format>

#define _TRACE_COPY_AND_MOVE 0

class Wrapper {

public:

	int uuid = 0;

	Wrapper() { uuid = time(0); };
	Wrapper(int t) { uuid = t; };

	~Wrapper() {
		if (_TRACE_COPY_AND_MOVE) printf("~Wrap %p\n", this);
	};

	Wrapper(Wrapper&& c) noexcept { 
		if(_TRACE_COPY_AND_MOVE) printf("Wrap&&\n");
		uuid = c.uuid;
		c.uuid = 0;
	};

	Wrapper(const Wrapper& c) noexcept 
	{ 
		if (_TRACE_COPY_AND_MOVE) printf("Wrap&\n");
		uuid = c.uuid;
	};

	Wrapper& operator=(const Wrapper& t) noexcept {
		if (_TRACE_COPY_AND_MOVE) printf("=Wrap&\n");
		uuid = t.uuid;
		return *this;
	};

	Wrapper& operator==(Wrapper&& t) noexcept { 
		if (_TRACE_COPY_AND_MOVE) printf("=Wrap&&\n");
		uuid = t.uuid;
		t.uuid = 0;
		return *this;
	};

};