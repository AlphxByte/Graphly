#ifndef GRAPHLY_MEMORY_TRACKER_HEADER
#define GRAPHLY_MEMORY_TRACKER_HEADER

#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <wrl.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <memory>

namespace Graphly
{
	/* OPTIONAL:
	* 
	* Use ID3D11Debug make a more detailed report for Direct3D objects. 
	* This interface is dependent on ID3D11Device
	* 
	*/

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
		_CrtMemState _startState; // CRTDEBUG state
		Microsoft::WRL::ComPtr<IDXGIDebug1> _dxgiDebug{}; // DXGI debug interface
	};

	using MemoryTrackerPtr       = std::unique_ptr<MemoryTracker>;
	using MemoryTrackerSharedPtr = std::shared_ptr<MemoryTracker>;
}

#endif // GRAPHLY_MEMORY_TRACKER_HEADER
