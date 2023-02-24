#include "VoxelEngineCore/Application.hpp"
#include "VoxelEngineCore/Log.hpp"

#include"VoxelEngineCore/Window.hpp"
#include"VoxelEngineCore/Event.hpp"

namespace VoxelEngine {

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

        m_event_dispatcher.add_event_listener<EventMouseMoved>(
            [](EventMouseMoved& event)
            {
                Log_info("[MouseMoved] Mouse moved to {0}x{1}", event.x, event.y);
            });

        m_event_dispatcher.add_event_listener<EventWindowResize>(
            [](EventWindowResize& event)
            {
                Log_info("[Resized] Changed size to {0}x{1}", event.height, event.height);
            });

        m_event_dispatcher.add_event_listener<EventWindowClose>(
            [&](EventWindowClose& event)
            {
                Log_info("[WindowClose]");
        m_bCloseWindow = true;
            });

        m_pWindow->set_event_callback(
            [&](BaseEvent& event)
            {
                m_event_dispatcher.dispatch(event);
            }
        );

        while (!m_bCloseWindow)
        {
            m_pWindow->on_update();
            on_update();
        }
        m_pWindow = nullptr;

        return 0;
    }
}