#pragma once

#include "pch.h"

template <typename T>
using ref = std::shared_ptr<T>;
template <typename T, typename... Args>
constexpr ref<T> make(Args &&...args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef size_t size;

typedef float f32;
typedef double f64;
typedef std::string str;
typedef const char cstr;