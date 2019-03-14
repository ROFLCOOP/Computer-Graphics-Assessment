#pragma once

#include <glfw3.h>

class Application
{
public:
	Application();
	~Application();
	
	virtual bool startup();
	virtual bool update();
	virtual void draw();
	virtual void shutdown();
};

