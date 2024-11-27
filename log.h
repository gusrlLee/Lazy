#pragma once 

#include "pch.h"
#include "types.h"

class Log 
{
    public:
        static void log(cstr* buf);
        static void info(cstr* buf);
        static void warn(cstr* buf);
        static void error(cstr* buf);
        static void fatal(cstr* buf);
};


#define LOG(...)        Log::log(__VA_ARGS__)
#define INFO(...)       Log::info(__VA_ARGS__)
#define WARN(...)       Log::warn(__VA_ARGS__)
#define ERROR(...)      Log::error(__VA_ARGS__)
#define FATAL(...)      Log::fatal(__VA_ARGS__)

#define CHECK(x)                                                   \
    do {                                                                \
        VkResult err = x;                                               \
        if (err) {                                                      \
            std::cout << "Found error : " << err << std::endl;          \
            abort();                                                    \
        }                                                               \
    } while (0)