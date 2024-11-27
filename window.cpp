#include "window.h"
#include "log.h"

WindowInfo &WindowInfo::set_title(str tname)
{
    this->title = tname;
    return *this;
}

WindowInfo &WindowInfo::set_width(u32 width)
{
    w = width;
    return *this;
}

WindowInfo &WindowInfo::set_height(u32 height)
{
    h = height;
    return *this;
}

void Window::init(WindowInfo &info)
{
    LOG("Create window...");

    // glfw library initialization
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // copy window initalization info
    m_info = info;

    // create glfw window
    m_win = glfwCreateWindow(info.w, info.h, info.title.c_str(), nullptr, nullptr);
    if (!m_win)
    {
        glfwTerminate();
        FATAL("[SYSTEM] Failed to create main window.. :-(");
    }

    LOG("Success to create window");
}

void Window::reset()
{
    if (m_win != nullptr)
    {
        glfwDestroyWindow(m_win);
    }
    glfwTerminate();
}
