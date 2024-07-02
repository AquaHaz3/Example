#include "FormatUtil.h"
#include <sstream>

std::string FormatUtil::DumpPrintableASCII(uint8_t* data, size_t size)
{
	auto out = std::ostringstream();
	for (int i = 0; i < size; i++) {
		int c = data[i];
		if (std::isprint(c)) 
		{
			out << (char)c;
		}
		else {
			out << ".";
		}
	}
	return out.str();
}
