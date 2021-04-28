#include "graph.hpp"
#include "debug.hpp"

namespace Core::Engine
{
	Graph::Graph()
	{
		Core::Debug::Log::info("Creating the Graph");
	}

	Graph::~Graph()
	{
		Core::Debug::Log::info("Destroying the Graph");
	}

	void Graph::loadScene(const std::string& scenePath)
	{

	}

	void Graph::saveCurrentScene()
	{
		
	}

	void Graph::init()
	{

	}

	void Graph::draw()
	{
		Graph* graph = instance();

		graph->curScene.draw();
	}

	void Graph::update()
	{
		Graph* graph = instance();

		graph->curScene.update();
	}
}