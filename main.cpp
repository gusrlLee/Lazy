#include <iostream>
#include "window.h"
#include "core.h"
#include "engine.h"

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

    EngineInfo einfo{};
    einfo.cinfo = cinfo;

    auto engine = make<Engine>();
    engine->init_engine(einfo);

    while(!window->is_close())
    {
        // TODO: Render frame
        window->update();
    }

    engine->reset_engine();
    window->reset();

    return 0;
}