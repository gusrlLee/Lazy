#include "log.h"

void Log::info(cstr *buf)
{
    std::cout << "[SYSTEM_INFO] : " << buf << '\n';
}

void Log::log(cstr *buf)
{
    std::clog << "[SYSTEM_LOG] : " << buf << '\n';
}

void Log::warn(cstr *buf)
{
    std::clog << "[SYSTEM_WARNNING] : " << buf << '\n';
}

void Log::error(cstr *buf)
{
    std::cerr << "[SYSTEM_ERROR] : " << buf << '\n';
}

void Log::fatal(cstr *buf)
{
    throw std::runtime_error(buf);
}