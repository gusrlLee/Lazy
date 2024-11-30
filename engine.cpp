#include "engine.h"

void Engine::init_engine(EngineInfo &info)
{
    init_core(info.cinfo);
}

void Engine::reset_engine()
{
    reset();
}