#include <iostream>
#include "window.h"
#include "core.h"

int main()
{
    WindowInfo winfo{};
    winfo.set_width(720);
    winfo.set_height(480);
    winfo.set_title("My first engine!");

    auto window = make<Window>();
    window->init(winfo);


    CoreInfo cinfo{};
    cinfo.set_win_ptr(window->get_native_ptr());
    cinfo.set_validation_layer(true);

    auto core = make<Core>();
    core->init_core(cinfo);

    while(!window->is_close())
    {
        // TODO: Render frame
        window->update();
    }

    core->reset();
    window->reset();
    return 0;
}