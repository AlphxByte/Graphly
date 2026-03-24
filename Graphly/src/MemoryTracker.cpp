#include "../include/Graphly/MemoryTracker.h"

using namespace Graphly;

MemoryTracker::MemoryTracker()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtMemCheckpoint(&_startState);
}

MemoryTracker::~MemoryTracker()
{
    _CrtMemState endState, diffState;
    _CrtMemCheckpoint(&endState);

    if (_CrtMemDifference(&diffState, &_startState, &endState))
    {
        _CrtMemDumpStatistics(&diffState);
        _CrtMemDumpAllObjectsSince(&_startState);
    }
}