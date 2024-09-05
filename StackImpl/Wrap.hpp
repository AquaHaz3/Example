#pragma once
#include <ctime>
#include <format>

#define _TRACE_COPY_AND_MOVE 0

class Wrap {

public:

	int uuid = 0;

	Wrap() { uuid = time(0); };
	Wrap(int t) { uuid = t; };

	~Wrap() {
		//if (_TRACE_COPY_AND_MOVE) printf("~Wrap\n");
	};

	Wrap(Wrap&& c) noexcept { 
		if(_TRACE_COPY_AND_MOVE) printf("Wrap&&\n");
		uuid = c.uuid;
		c.uuid = 0;
	};

	Wrap(const Wrap& c) noexcept 
	{ 
		if (_TRACE_COPY_AND_MOVE) printf("Wrap&\n");
		uuid = c.uuid;
	};

	Wrap& operator=(const Wrap& t) noexcept {
		if (_TRACE_COPY_AND_MOVE) printf("=Wrap&\n");
		uuid = t.uuid;
		return *this;
	};

	Wrap& operator==(Wrap&& t) noexcept { 
		if (_TRACE_COPY_AND_MOVE) printf("=Wrap&&\n");
		uuid = t.uuid;
		t.uuid = 0;
		return *this;
	};

};