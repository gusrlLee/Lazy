#include "Math/Vec2.h"

namespace Lazy 
{
    Vec2::Vec2() : e{0.0f, 0.0f} {}
    Vec2::Vec2(float value) : e{value, value} {}
    Vec2::Vec2(float e1, float e2) : e{e1, e2} {}
}


