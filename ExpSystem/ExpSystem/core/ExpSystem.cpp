#include "ExpSystem.h"
#include <iostream>
#include "../crypto/SHA256.h"
#include <map>
#include <set>
#include <bitset>
#include <intrin.h>

ExpSystem::ExpSystem()
{
	os = Platform::GetCurrentOS();
}

ExpSystem* ExpSystem::instance = nullptr;

ExpSystem* ExpSystem::GetInstance()
{
	if (instance == nullptr) {
		instance = new ExpSystem();
		return instance;
	}
	return instance;
}

void ExpSystem::Init(UserIO* user_io)
{
	userio = user_io;
}

#include <stdint.h>
#include <fstream>
#include <Windows.h>

void Test_Shellcode() {
	auto f = std::ifstream("C:\\root\\temp\\ctf\\challenge\\shellcode3.bin", std::ios_base::binary | std::ios_base::ate);
	int size = f.tellg();
	f.seekg(0);
	uint8_t* buffer = new uint8_t[size + 1];
	f.read((char*)buffer, size);
	f.close();

	printf("BASE = %p\n", buffer);
	printf("START = %p\n", buffer + 0xa60);

	std::string a = "a";
	DWORD old = 0;
	std::cout << VirtualProtect((void*)buffer, size, PAGE_EXECUTE_READWRITE, &old);
	std::cin >> a;
	//CreateFileA("C:\\AirPipe\\syslog", GENERIC_READ, 1, 0, 3, 0x80, 0);
}


void ExpSystem::Start()
{

	//Test_Shellcode();
	//Test_CrackMe(0);
		
}

ExpSystem::~ExpSystem()
{
	delete userio;
}
