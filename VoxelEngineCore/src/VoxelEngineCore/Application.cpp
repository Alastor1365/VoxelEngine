#include "VoxelEngineCore/Application.hpp"
#include "VoxelEngineCore/Log.hpp"

#include"VoxelEngineCore/Window.hpp"

namespace VoxelEngine
{
	Application::Application()
	{
		Log_info("Starting Application");
	}

	Application::~Application()
	{
		Log_info("Closing Application");
	}

	int Application::start(unsigned int window_width, unsigned int window_height, const char* title)
	{
		m_pWindow = std::make_unique<Window>(title, window_width, window_height);

		while (true)
		{
			m_pWindow->on_update();
			on_update();
		}

        return 0;
    }

    void Application::on_update()
    {

    }
}