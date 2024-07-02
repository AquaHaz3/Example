#pragma once
#include <vector>

typedef void (*_stack_cmd)(int cx, int dx, int offset);

struct s_command 
{
	int id;
	int ecx;
	int edx;
	int offset;

	s_command(int id, int cx, int dx, int offset) {
		this->id = id;
		this->ecx = cx;
		this->edx = dx;
		this->offset = offset;
	}
};

class CrackMe
{

public:

	CrackMe() {};
	void Start();
	void PrintStackDump(bool dump = false);
	void AddCMD(int id, int cx, int dx, int offset);
	void Execute();

private:

	int current_cmd = 0;
	std::vector<s_command*> program = std::vector<s_command*>();

};

