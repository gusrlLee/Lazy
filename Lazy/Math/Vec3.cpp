#include "Math/Vec3.h"

namespace Lazy
{
    Vec3::Vec3() : e{0.0f, 0.0f, 0.0f} {}
    Vec3::Vec3(float value) : e{value, value, value} {}
    Vec3::Vec3(float e1, float e2, float e3) : e{e1, e2, e3} {}
}
