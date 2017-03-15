#pragma once

#include <map>
#include "Callback.h"
#include "SRect.h"
#include "EButtonState.h"

struct SButtonData
{
	SRect m_rect;
	Function m_callback;
};

typedef std::map<EButtonState, SButtonData> ButtonMap;
typedef std::pair<EButtonState, SButtonData> ButtonPair;
