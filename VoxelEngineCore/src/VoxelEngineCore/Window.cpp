#include "VoxelEngineCore/Window.hpp"
#include "VoxelEngineCore/Log.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace VoxelEngine
{
    static bool s_GLFW_inicialized = false;

	Window::Window(std::string title, const unsigned int width, const unsigned int height)
		: m_data({std::move(title), width, height})
	{
		int resultCode = init();
	}

	Window::~Window()
	{
        close();
	}

	int Window::init()
	{
        Log_info("Creating window '{0}' width size {1}x{2}", m_data.title, m_data.width, m_data.height);

        if (!s_GLFW_inicialized)
        {
            if (!glfwInit())
            {
                Log_crit("Can,t initialize GLFW!");
                return -1;
            }

            s_GLFW_inicialized = true;
        }

        /* Create a windowed mode window and its OpenGL context */
        m_pWindow = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
        if (!m_pWindow)
        {
            Log_crit("Can,t create window {0} width size {1}x{2}", m_data.title, m_data.width, m_data.height);
            glfwTerminate();
            return -2;
        }

        glfwMakeContextCurrent(m_pWindow);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            Log_crit("Failed to initialize GLAD");
            return -3;
        }

        glfwSetWindowUserPointer(m_pWindow, &m_data);

        glfwSetWindowSizeCallback(m_pWindow,
            [](GLFWwindow* pWindow, int width, int height)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
                data.width = width;
                data.height = height;

                EventWindowResize event(width, height);
                data.eventCallbackFn(event);
            }
        );

        glfwSetCursorPosCallback(m_pWindow,
            [](GLFWwindow* pWindow, double x, double y)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
                
                EventMouseMoved event(x, y);
                data.eventCallbackFn(event);
            }
        );

        return 0;
	}

	void Window::close()
	{
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
	}

	void Window::on_update()
	{
        glClearColor(1, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
	}
}