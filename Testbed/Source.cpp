#include <iostream>
#include <CoreEngine.h>
#include <Viewport.h>

int main(int argc, char** argv)
{
	Viewport window("Testbed", 512, 512, 0);
	CoreEngine core(60.0, &window, nullptr, nullptr, nullptr, nullptr, nullptr);

	core.start();

	return 0;

}