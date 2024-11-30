#pragma once 
#include "pch.h"
#include "types.h"
#include "core.h"

struct EngineInfo 
{
    CoreInfo cinfo;
};

class Engine : public Core
{
public: 
    void init_engine(EngineInfo &info);
    void reset_engine();
};