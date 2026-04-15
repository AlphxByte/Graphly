#ifndef GRAPHLYUI_GRAPHICS_DEVICE_HEADER
#define GRAPHLYUI_GRAPHICS_DEVICE_HEADER

#include "DXGIFactory.h"
#include "Adapter.h"
#include "D3DDevice.h"
#include "DXGIDevice.h"

namespace GraphlyUI
{
	class GraphicsDevice final
	{
	public:
		GraphicsDevice(const AdapterSettings& adapterSettings);
		GraphicsDevice(AdapterSettings&& adapterSettings);
		GraphicsDevice(const GraphicsDevice& other) = delete;
		GraphicsDevice(GraphicsDevice&& other) = delete;
		~GraphicsDevice() = default;

		[[nodiscard]] DXGIFactory* GetDXGIFactory() const;
		[[nodiscard]] Adapter* GetAdapter() const;
		[[nodiscard]] D3DDevice* GetD3DDevice() const;
		[[nodiscard]] DXGIDevice* GetDXGIDevice() const;

		GraphicsDevice& operator = (const GraphicsDevice& other) = delete;
		GraphicsDevice& operator = (GraphicsDevice&& other) = delete;

	private:
		[[nodiscard]] bool Initialize();

	private:
		AdapterSettings _adapterSettings{};

		DXGIFactoryPtr _dxgiFactory{};
		AdapterPtr _adapter{};
		D3DDevicePtr _d3dDevice{};
		DXGIDevicePtr _dxgiDevice{};
	};

	using GraphicsDevicePtr = std::unique_ptr<GraphicsDevice>;
	using GraphicsDeviceSharedPtr = std::shared_ptr<GraphicsDevice>;
}

#endif // GRAPHLYUI_GRAPHICS_DEVICE_HEADER
