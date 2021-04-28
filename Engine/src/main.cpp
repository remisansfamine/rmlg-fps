#include <string>
#include <iostream>
#include <crtdbg.h>

#include "application.hpp"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// Check for leak
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	try
	{
		Core::Application::init(SCR_WIDTH, SCR_HEIGHT, "Engine");

		// TODO: Update AP
		Core::Application::update();
	}
	catch (const char* msg)
	{
		//Log::logAssertion(msg);
	}
	catch (const std::string& msg)
	{
		//Log::logAssertion(msg);
	}
	catch (const std::exception& assertion)
	{
		//Log::logAssertion(assertion.what());
	}

	Core::Application::kill();

	return 0;
}