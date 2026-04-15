#ifndef GRAPHLYUI_DXGIFACTORY_HEADER
#define GRAPHLYUI_DXGIFACTORY_HEADER

#include <dxgi1_6.h>
#include <wrl.h>
#include <memory>

namespace GraphlyUI
{
	class DXGIFactory final
	{
	public:
		DXGIFactory();
		DXGIFactory(const DXGIFactory& other) = delete;
		DXGIFactory(DXGIFactory&& other) = delete;
		~DXGIFactory() = default;

		[[nodiscard]] IDXGIFactory7* GetFactory() const;

		DXGIFactory& operator = (const DXGIFactory& other) = delete;
		DXGIFactory& operator = (DXGIFactory&& other) = delete;

	private:
		Microsoft::WRL::ComPtr<IDXGIFactory7> _factory{};
	};

	using DXGIFactoryPtr = std::unique_ptr<DXGIFactory>;
	using DXGIFactorySharedPtr = std::shared_ptr<DXGIFactory>;
}

#endif // GRAPHLYUI_DXGIFACTORY_HEADER