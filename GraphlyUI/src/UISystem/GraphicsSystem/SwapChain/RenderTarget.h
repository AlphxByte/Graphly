#ifndef GRAPHLYUI_RENDER_TARGET_HEADER
#define GRAPHLYUI_RENDER_TARGET_HEADER

#include <dxgi1_6.h>
#include <d2d1_3.h>
#include <d2d1_3helper.h>
#include <wrl.h>
#include <memory>

namespace GraphlyUI
{
	class RenderTarget final
	{
	public:
		explicit RenderTarget(ID2D1DeviceContext6* context, IDXGISurface1* surface);
		RenderTarget(const RenderTarget& other) = delete;
		RenderTarget(RenderTarget&& other) = delete;
		~RenderTarget() = default;

		void CreateRenderTarget(IDXGISurface1* surface);
		void ResetRenderTarget();

		[[nodiscard]] ID2D1Bitmap1* GetBitmap() const;

		RenderTarget& operator = (const RenderTarget& other) = delete;
		RenderTarget& operator = (RenderTarget&& other) = delete;

	private:
		Microsoft::WRL::ComPtr<ID2D1Bitmap1> _bitmap{};

		// Not owned resources
		ID2D1DeviceContext6* _context;
	};

	using RenderTargetPtr = std::unique_ptr<RenderTarget>;
	using RenderTargetSharedPtr = std::shared_ptr<RenderTarget>;
}

#endif // GRAPHLYUI_RENDER_TARGET_HEADER
