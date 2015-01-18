#include "Utils.h"

bool inRange(int value, int min, int max)
{
	if ((value < min) || (value > max))
		return false;
	else
		return true;
}