#include "../include/GraphlyCore/SystemMetrics.h"

#include <windows.h>

using namespace GraphlyCore;

unsigned SystemMetrics::GetScreenWidth()
{
	return GetSystemMetrics(SM_CXSCREEN);
}

unsigned SystemMetrics::GetScreenHeight()
{
	return GetSystemMetrics(SM_CYSCREEN);
}
