﻿#include "application.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "resources_manager.hpp"
#include "inputs_manager.hpp"
#include "engine_master.hpp"
#include "debug.hpp"
#include "time.hpp"

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
		Core::Debug::Log::info("Creating the Application");
	}

	Application::~Application()
	{
		Resources::ResourcesManager::kill();

		Debug::Log::info("Destroying the Application");

		Input::InputManager::kill();
		Debug::Assertion::kill();
		Engine::EngineMaster::kill();

		TimeManager::kill();

		Debug::Log::kill();

		// Destroy ImGui context
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		// Destroy glfw window
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	GLFWwindow* Application::createWindow(unsigned int screenWidth, unsigned int screenHeight, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
	{
		// Check if the Application instance is already initialized
		if (instance()->initialized)
			return nullptr;

		// glfw - Initialize and configuration
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create window
		Debug::Log::info("Creating the window");
		GLFWwindow* newWindow = glfwCreateWindow(screenWidth, screenHeight, title, monitor, share);

		// If the window could not be created, exit the program
		Debug::Assertion::out(newWindow, "Failed to create GLFW window");

		// Initialize glfw context
		glfwMakeContextCurrent(newWindow);
		glfwSetFramebufferSizeCallback(newWindow, framebufferSizeCallback);

		// glad - Load all OpenGL function pointers, if it fails, assert
		Debug::Assertion::out(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD");

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

		// Check if the Application is already initialized
		if (AP->initialized)
		{
			Debug::Log::error("The Application is already initialized");
			return;
		}

		// Return the Window created by GLFW
		AP->window = createWindow(screenWidth, screenHeight, title, monitor, share);
		AP->initialized = true;
 		Debug::Log::info("Application initialized");

		// Init Managers
		Resources::ResourcesManager::init();

		Input::InputManager::init(AP->window);
	}

	void Application::update()
	{
		Application* AP = instance();

		// Loop while the game is running
		while (!glfwWindowShouldClose(AP->window))
		{
			// Update ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// Compute managers
			TimeManager::computeTime();
			Input::InputManager::compute();

			// Update the Engine
			Engine::EngineMaster::update();

			// Render ImGui
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			// glfw - Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			glfwSwapBuffers(AP->window);
			glfwPollEvents();
		}
	}

	void Application::closeApplication()
	{
		// Tell to glfw to close the window 
		glfwSetWindowShouldClose(instance()->window, true);
	}

	float Application::getAspect()
	{
		// Return the aspect of the Window
		int width, height;
		glfwGetWindowSize(instance()->window, &width, &height);
		return (float)width / (float)height;
	}

	void Application::setCursor(bool isCursorFree)
	{
		Application* AP = instance();

		// Toggle the cursor visibility
		if (!isCursorFree)
		{
			glfwSetInputMode(AP->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			return;
		}

		glfwSetInputMode(AP->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}