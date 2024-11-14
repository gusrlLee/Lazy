#pragma once 
#include <iostream>
#include "Primitives/Ray.h"

namespace Lazy 
{
    class Primitive 
    {
        public:
            virtual bool Hit(Ray* r, HitInfo* info) { return false; }
    };
}
