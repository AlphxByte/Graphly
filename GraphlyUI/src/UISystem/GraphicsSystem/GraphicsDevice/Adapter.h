#ifndef GRAPHLYUI_ADAPTER_HEADER
#define GRAPHLYUI_ADAPTER_HEADER

#include "GraphlyUI/UISystem/GraphicsSystemSettings.h"

#include <dxgi1_6.h>
#include <wrl.h>
#include <memory>

namespace GraphlyUI
{
	class DXGIFactory;

	class Adapter final
	{
	public:
		Adapter(DXGIFactory* dxgiFactory, const AdapterSettings& settings);
		Adapter(const Adapter& other) = delete;
		Adapter(Adapter&& other) = delete;
		~Adapter() = default;

		[[nodiscard]] IDXGIAdapter4* GetAdapter() const;
		[[nodiscard]] const AdapterSettings& GetSettings() const;

		Adapter& operator = (const Adapter& other) = delete;
		Adapter& operator = (Adapter&& other) = delete;

	private:
		AdapterSettings _settings{};
		DXGI_GPU_PREFERENCE _gpuPreference{};

		Microsoft::WRL::ComPtr<IDXGIAdapter4> _adapter{};
	};

	using AdapterPtr = std::unique_ptr<Adapter>;
	using AdapterSharedPtr = std::shared_ptr<Adapter>;
}

#endif // GRAPHLYUI_ADAPTER_HEADER