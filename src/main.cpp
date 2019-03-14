#include "Application.h"

int main()
{
	Application* theApp = new Application();
	if (theApp->startup(1280, 720) == true)
	{
		while (theApp->update(0.01f) == true)
			theApp->draw();
		theApp->shutdown();
	}
	else
	{
		delete theApp;
		return -1;
	}
	delete theApp;

	return 0;
}