#ifndef GRAPHLYUI_D2DSYSTEM_HEADER
#define GRAPHLYUI_D2DSYSTEM_HEADER

#include "D2DFactory.h"
#include "D2DDevice.h"

namespace GraphlyUI
{
	class DXGIDevice;

	class D2DSystem final
	{
	public:
		explicit D2DSystem(DXGIDevice* dxgiDevice);
		D2DSystem(const D2DSystem& other) = delete;
		D2DSystem(D2DSystem&& other) = delete;
		~D2DSystem() = default;

		[[nodiscard]] D2DFactory* GetD2DFactory() const;
		[[nodiscard]] D2DDevice* GetD2DDevice() const;

		D2DSystem& operator = (const D2DSystem& other) = delete;
		D2DSystem& operator = (D2DSystem&& other) = delete;

	private:
		[[nodiscard]] bool Initialize();

	private:
		// Owned resources
		D2DFactoryPtr _d2dFactory{};
		D2DDevicePtr _d2dDevice{};

		// Not owned resources
		DXGIDevice* _dxgiDevice{};
	};

	using D2DSystemPtr = std::unique_ptr<D2DSystem>;
	using D2DSystemSharedPtr = std::shared_ptr<D2DSystem>;
}

#endif // GRAPHLYUI_D2DSYSTEM_HEADER
