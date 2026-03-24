#ifndef GRAPHLY_MEMORY_TRACKER_HEADER
#define GRAPHLY_MEMORY_TRACKER_HEADER

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <memory>

namespace Graphly
{
	class MemoryTracker final
	{
	public:
		MemoryTracker();
		MemoryTracker(const MemoryTracker& other) = delete;
		MemoryTracker(MemoryTracker&& other) = delete;
		~MemoryTracker();

		MemoryTracker& operator = (const MemoryTracker& other) = delete;
		MemoryTracker& operator = (MemoryTracker&& other) = delete;
			
	private:
		_CrtMemState _startState;
	};

	using MemoryTrackerPtr       = std::unique_ptr<MemoryTracker>;
	using MemoryTrackerSharedPtr = std::shared_ptr<MemoryTracker>;
}

#endif // GRAPHLY_MEMORY_TRACKER_HEADER
