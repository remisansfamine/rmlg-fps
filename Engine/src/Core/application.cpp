#include "application.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// TODO: remove iostream inclusion
#include <iostream>

#include "resources_manager.hpp"
#include "debug.hpp"

// glfw - Whenever the window size changed (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	// Modify viewport size after window resize
	glViewport(0, 0, width, height);
}

namespace Core
{
	Application::Application()
	{
		Core::Debug::Log::logInfo("Creating the Application");
	}

	Application::~Application()
	{
		Resources::ResourcesManager::kill();

		// TODO: Kill graph/physicManager/ etc..

		Core::Debug::Log::logInfo("Destroying the Application");

		Core::Debug::Assertion::kill();
		Core::Debug::Log::kill();

		// Destroy ImGui context
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		// Destroy glfw window
		glfwDestroyWindow(window);
		glfwTerminate();
	}



	GLFWwindow* Application::createWindow(unsigned int screenWidth, unsigned int screenHeight, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
	{
		if (instance()->initialized)
			return nullptr;

		// glfw - Initialize and configuration
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create window
		Core::Debug::Log::logInfo("Creating the window");
		GLFWwindow* newWindow = glfwCreateWindow(screenWidth, screenHeight, title, monitor, share);

		// If the window could not be created, exit the program
		Core::Debug::Assertion::out(newWindow, "Failed to create GLFW window");

		// Initialize glfw context
		glfwMakeContextCurrent(newWindow);
		glfwSetFramebufferSizeCallback(newWindow, framebufferSizeCallback);

		// glad - Load all OpenGL function pointers, if it fails, assert
		Core::Debug::Assertion::out(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD");

		// ImGui - Initialization
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(newWindow, true);
		ImGui_ImplOpenGL3_Init("#version 130");

		return newWindow;
	}

	void Application::init(unsigned int screenWidth, unsigned int screenHeight, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
	{
		Application* AP = instance();


		if (AP->initialized)
		{
			Core::Debug::Log::logError("The Application is already initialized");
			return;
		}

		AP->window = createWindow(screenWidth, screenHeight, title, monitor, share);
		AP->initialized = true;

		Core::Debug::Log::logInfo("Application initialized");

		// Init Resources Manager
		Resources::ResourcesManager::init();
	}

	void Application::update()
	{
		// TODO: remove
		std::cout << "Bonsoir LERE" << std::endl;
	}
}