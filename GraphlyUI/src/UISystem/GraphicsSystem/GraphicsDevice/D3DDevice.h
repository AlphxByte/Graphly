#ifndef GRAPHLYUI_D3DDEVICE_HEADER
#define GRAPHLYUI_D3DDEVICE_HEADER

#include <d3d11_4.h>
#include <wrl.h>
#include <memory>

namespace GraphlyUI
{
	class Adapter;

	class D3DDevice final
	{
	public:
		explicit D3DDevice(Adapter* adapter);
		D3DDevice(const D3DDevice& other) = delete;
		D3DDevice(D3DDevice&& other) = delete;
		~D3DDevice();

		[[nodiscard]] ID3D11Device* GetDevice() const;
		[[nodiscard]] ID3D11DeviceContext* GetDeviceContext() const;
		[[nodiscard]] const D3D_FEATURE_LEVEL GetFeatureLevel() const;

		D3DDevice& operator = (const D3DDevice& other) = delete;
		D3DDevice& operator = (D3DDevice&& other) = delete;

	private:
		D3D_FEATURE_LEVEL _featureLevel{};

		Microsoft::WRL::ComPtr<ID3D11Device> _device{};
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _context{};
	};

	using D3DDevicePtr = std::unique_ptr<D3DDevice>;
	using D3DDeviceSharedPtr = std::shared_ptr<D3DDevice>;
}

#endif // GRAPHLYUI_D3DDEVICE_HEADER