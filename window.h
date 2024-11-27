#pragma once
#include "pch.h"
#include "types.h"

struct WindowInfo 
{
    u32 w;
    u32 h;
    str title;

    WindowInfo& set_title(str tname);
    WindowInfo& set_width(u32 width);
    WindowInfo& set_height(u32 height);
};

class Window
{
public:
    void init(WindowInfo &info);
    void reset();

    u32 get_width() { return m_info.w; }
    u32 get_height() { return m_info.h; }
    str get_title() { return m_info.title; }
    
    GLFWwindow *get_native_ptr() { return m_win; }

    bool is_close() { return glfwWindowShouldClose(m_win); }
    void update() { glfwPollEvents(); }

private:
    struct GLFWwindow *m_win = nullptr;
    WindowInfo m_info;
};