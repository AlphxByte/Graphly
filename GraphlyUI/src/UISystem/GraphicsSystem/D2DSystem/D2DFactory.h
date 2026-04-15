#ifndef GRAPHLYUI_D2DFACTORY_HEADER
#define GRAPHLYUI_D2DFACTORY_HEADER

#include <d2d1_3.h>
#include <d2d1_3helper.h>
#include <wrl.h>
#include <memory>

namespace GraphlyUI
{
	class D2DFactory final
	{
	public:
		D2DFactory();
		D2DFactory(const D2DFactory& other) = delete;
		D2DFactory(D2DFactory&& other) = delete;
		~D2DFactory() = default;

		[[nodiscard]] ID2D1Factory7* GetFactory() const;

		D2DFactory& operator = (const D2DFactory& other) = delete;
		D2DFactory& operator = (D2DFactory&& other) = delete;

	private:
		Microsoft::WRL::ComPtr<ID2D1Factory7> _factory{};
	};

	using D2DFactoryPtr = std::unique_ptr<D2DFactory>;
	using D2DFactorySharedPtr = std::shared_ptr<D2DFactory>;
}

#endif // GRAPHLYUI_D2DFACTORY_HEADER
