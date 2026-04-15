#ifndef GRAPHLYUI_DXGIDEVICE_HEADER
#define GRAPHLYUI_DXGIDEVICE_HEADER

#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <memory>

namespace GraphlyUI
{
	class D3DDevice;

	class DXGIDevice final
	{
	public:
		explicit DXGIDevice(D3DDevice* d3dDevice);
		DXGIDevice(const DXGIDevice& other) = delete;
		DXGIDevice(DXGIDevice&& other) = delete;
		~DXGIDevice() = default;

		[[nodiscard]] IDXGIDevice4* GetDevice() const;

		DXGIDevice& operator = (const DXGIDevice& other) = delete;
		DXGIDevice& operator = (DXGIDevice&& other) = delete;

	private:
		// Owned resources
		Microsoft::WRL::ComPtr<IDXGIDevice4> _device{};
	};

	using DXGIDevicePtr = std::unique_ptr<DXGIDevice>;
	using DXGIDeviceSharedPtr = std::shared_ptr<DXGIDevice>;
}

#endif // GRAPHLYUI_DXGIDEVICE_HEADER
