#pragma once
#include "Core/CoreBasicTypes.hpp"

class Pin;
struct Link
{
	u32 id;
	Pin* startPin;
	Pin* endPin;
};
