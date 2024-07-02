#include "Launcher.h"

int main(int argc, char** argv) 
{
	Launcher launcher = Launcher();
	launcher.Launch(AppDesign::Console);
	return 0;
}