#include "engine.h"
#include "log.h"

static std::vector<cstr*> read_shader_file(const str& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (file.is_open())
    {
        FATAL("Failed to open file!");
    }
}

void Engine::init_engine(EngineInfo &info)
{
    init_core(info.cinfo);

}

void Engine::reset_engine()
{
    reset();
}