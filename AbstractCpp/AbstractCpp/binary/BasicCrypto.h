#pragma once

#include <string>
#include <bitset>

namespace crypto 
{
	
	__int64 lrot(__int64 x, int shift, int word_size) 
	{
		__int64 mask = 0xffff'ffff'ffff'ffff >> (64 - word_size);
		return ((x << shift) & mask) | (x >> (word_size - shift));
	}
	
	__int64 rrot(__int64 x, int shift, int word_size) 
	{
		__int64 mask = 0xffff'ffff'ffff'ffff >> (64 - word_size);
		return (x >> shift) | ((x << (word_size - shift) & mask));
	}

	std::string bin4(uint8_t x) {
		return std::bitset<4>(x).to_string();
	}
	
	std::string bin8(uint8_t x) {
		return std::bitset<8>(x).to_string();
	}
	
	std::string bin(__int64 x) {
		return std::bitset<64>(x).to_string();
	}

}