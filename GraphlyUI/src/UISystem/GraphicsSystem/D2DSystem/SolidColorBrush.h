#ifndef GRAPHLYUI_SOLID_COLOR_BRUSH_HEADER
#define GRAPHLYUI_SOLID_COLOR_BRUSH_HEADER

#include "GraphlyMath/Vector.h"

#include <d2d1_3.h>
#include <d2d1_3helper.h>
#include <wrl.h>
#include <memory>

namespace GraphlyUI
{
	class D2DDevice;

	class SolidColorBrush final
	{
	public:
		SolidColorBrush(D2DDevice* d2dDevice, const GraphlyMath::Vector4& color);
		SolidColorBrush(D2DDevice* d2dDevice, GraphlyMath::Vector4&& color);
		SolidColorBrush(const SolidColorBrush& other) = delete;
		SolidColorBrush(SolidColorBrush&& other) = delete;
		~SolidColorBrush() = default;

		void SetColor(const GraphlyMath::Vector4& color);
		void SetColor(GraphlyMath::Vector4&& color);
		[[nodiscard]] const GraphlyMath::Vector4& GetColor() const;
		[[nodiscard]] ID2D1SolidColorBrush* GetBrush() const;

		SolidColorBrush& operator = (const SolidColorBrush& other) = delete;
		SolidColorBrush& operator = (SolidColorBrush&& other) = delete;

	private:
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> _brush{};
	};

	using SolidColorBrushPtr = std::unique_ptr<SolidColorBrush>;
	using SolidColorBrushSharedPtr = std::shared_ptr<SolidColorBrush>;
}

#endif // GRAPHLYUI_SOLID_COLOR_BRUSH_HEADER
