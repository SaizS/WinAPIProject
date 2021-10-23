#include "framework.h"

int Math::Random(int min, int max)
{
	return rand() % (max - min) + min;
}
