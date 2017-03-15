#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "SBitmap.h"

SBitmap LoadBitmapAndAddAlpha(char* a_path);

float Map(float a_value, float a_inMin, float a_inMax, float a_outMin, float a_outMax);