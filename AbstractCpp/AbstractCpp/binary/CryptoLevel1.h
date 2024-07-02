#pragma once

#include <cstdint>
#include "BasicCrypto.h"

typedef union 
{

	int a;
	char bytes[4];

} word32, lazy4;

typedef union 
{

	__int64 a;
	char bytes[8];

} word64, lazy8;

lazy8 get_lazy8(uint8_t y) {
	word64 r;
	auto set = std::bitset<8>(y);
	r.bytes[0] = set[0]; r.bytes[1] = set[1];
	r.bytes[2] = set[2]; r.bytes[3] = set[3];
	r.bytes[4] = set[4]; r.bytes[5] = set[5];
	r.bytes[6] = set[6]; r.bytes[7] = set[7];
	return r;
}

uint8_t unpack_lazy8(lazy8 lazy) {
	uint8_t g = 0;
	g |= lazy.bytes[0];      g |= lazy.bytes[1] << 1;
	g |= lazy.bytes[2] << 2; g |= lazy.bytes[3] << 3;
	g |= lazy.bytes[4] << 4; g |= lazy.bytes[5] << 5;
	g |= lazy.bytes[6] << 6; g |= lazy.bytes[7] << 7;
	return g;
}

uint8_t find_collision_8(lazy8 y)
{
	word64 box;

	box.bytes[7] = 0;
	box.bytes[6] = y.bytes[7] ^ y.bytes[4] ^ y.bytes[1];
	box.bytes[5] = y.bytes[2] ^ y.bytes[5];
	box.bytes[4] = y.bytes[7];
	box.bytes[3] = y.bytes[7] ^ y.bytes[6] ^ y.bytes[4] ^ y.bytes[1];
	box.bytes[2] = y.bytes[2];
	box.bytes[1] = y.bytes[7] ^ y.bytes[4];
	box.bytes[0] = y.bytes[2] ^ y.bytes[5] ^ y.bytes[0];

	return unpack_lazy8(box);
}

uint8_t simple8(uint8_t x) 
{
	using namespace crypto;
	return (uint8_t)(lrot(x, 3, 8) ^ x);
}