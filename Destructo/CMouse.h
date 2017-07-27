#pragma once

#include <stdint.h>

class CMouse
{
public:
    static uint32_t x;
    static uint32_t y;
    static bool isLeftMouseDown;
    static bool isRightMouseDown;
};