#include "Graphly/MemoryTracker.h"

#include <iostream>
#include <stdexcept>

using namespace Graphly;

MemoryTracker::MemoryTracker()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtMemCheckpoint(&_startState);

    HRESULT result = DXGIGetDebugInterface1(0, IID_PPV_ARGS(&_dxgiDebug));
    if (FAILED(result))
        throw std::runtime_error("DXGIDebug failed to initialize.");
}

MemoryTracker::~MemoryTracker()
{
    OutputDebugStringA("============================= MemoryTracker report =============================\n\n");

    _CrtMemState endState, diffState;
    _CrtMemCheckpoint(&endState);

    if (_CrtMemDifference(&diffState, &_startState, &endState))
    {
        _CrtMemDumpStatistics(&diffState);
        _CrtMemDumpAllObjectsSince(&_startState);
    }

    HRESULT result = _dxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_DETAIL);
    if (FAILED(result))
        throw std::runtime_error("DXGIDebug failed to report live objects.");

    OutputDebugStringA("\n=========================== MemoryTracker end report ===========================\n");
}