#pragma once
#include "UserIO.h"

class ExpSystem
{
public:

	static ExpSystem* GetInstance();

	void Init(UserIO* user_io);
	void Start();

private:

	ExpSystem();
    ~ExpSystem();
	static ExpSystem* instance;

	UserIO* userio = 0;
	OS* os;

};
