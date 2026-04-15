#ifndef GRAPHLYUI_D2DDEVICE_HEADER
#define GRAPHLYUI_D2DDEVICE_HEADER

#include "GraphlyMath/GraphlyMath.h"
#include "SolidColorBrush.h"

#include <d2d1_3.h>
#include <d2d1_3helper.h>
#include <wrl.h>
#include <memory>

namespace GraphlyUI
{
	class D2DFactory;
	class DXGIDevice;

	class D2DDevice final
	{
	public:
		explicit D2DDevice(D2DFactory* d2dFactory, DXGIDevice* dxgiDevice);
		D2DDevice(const D2DDevice& other) = delete;
		D2DDevice(D2DDevice&& other) = delete;
		~D2DDevice() = default;

		void BeginDraw();
		void EndDraw();
		void PushAxisAlignedClip(const GraphlyMath::Vector4& rect);
		void PopAxisAlignedClip();
		void Clear(const GraphlyMath::Vector4& color);
		void SetTransform(const D2D1_MATRIX_3X2_F& transform);
		void GetTransform(D2D1_MATRIX_3X2_F& transform);
		void FillRectangle(const GraphlyMath::Vector4& rect, SolidColorBrush* brush);

		[[nodiscard]] ID2D1Device6* GetDevice() const;
		[[nodiscard]] ID2D1DeviceContext6* GetContext() const;

		D2DDevice& operator = (const D2DDevice& other) = delete;
		D2DDevice& operator = (D2DDevice&& other) = delete;

	private:
		[[nodiscard]] bool Initialize();

	private:
		Microsoft::WRL::ComPtr<ID2D1Device6> _device{};
		Microsoft::WRL::ComPtr<ID2D1DeviceContext6> _context{};
	};

	using D2DDevicePtr = std::unique_ptr<D2DDevice>;
	using D2DDeviceSharedPtr = std::shared_ptr<D2DDevice>;
}

#endif // GRAPHLYUI_D2DDEVICE_HEADER
