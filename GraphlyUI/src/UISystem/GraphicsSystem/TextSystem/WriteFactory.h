#ifndef GRAPHLYUI_WRITE_FACTORY_HEADER
#define GRAPHLYUI_WRITE_FACTORY_HEADER

#include <dwrite_3.h>
#include <wrl.h>
#include <memory>

namespace GraphlyUI
{
	class WriteFactory final
	{
	public:
		WriteFactory();
		WriteFactory(const WriteFactory& other) = delete;
		WriteFactory(WriteFactory&& other) = delete;
		~WriteFactory() = default;

		[[nodiscard]] IDWriteFactory8* GetFactory() const;

		WriteFactory& operator = (const WriteFactory& other) = delete;
		WriteFactory& operator = (WriteFactory&& other) = delete;

	private:
		Microsoft::WRL::ComPtr<IDWriteFactory8> _factory{};
	};

	using WriteFactoryPtr = std::unique_ptr<WriteFactory>;
	using WriteFactorySharedPtr = std::shared_ptr<WriteFactory>;
}

#endif // GRAPHLYUI_WRITE_FACTORY_HEADER
