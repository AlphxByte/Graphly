#include "Graphly/SystemMetrics.h"

#include <windows.h>

using namespace Graphly;

unsigned SystemMetrics::GetScreenWidth()
{
	return GetSystemMetrics(SM_CXSCREEN);
}

unsigned SystemMetrics::GetScreenHeight()
{
	return GetSystemMetrics(SM_CYSCREEN);
}
