#ifndef GRAPHLYUI_UISYSTEM_HEADER
#define GRAPHLYUI_UISYSTEM_HEADER

#include "../GraphlyUIExports.h"
#include "Window/Window.h"
#include "GraphicsSystemSettings.h"
#include "Window/UIElement/Text.h"

#include <string>
#include <memory>
#include <stdexcept>

namespace GraphlyUI
{
	struct GRAPHLYUI_API UISystemSettings final
	{
		GraphicsSystemSettings graphicsSettings;
	};

	class GraphicsSystem;
	class EventSystem;

	class GRAPHLYUI_API UISystem final
	{
	public:
		UISystem(const UISystemSettings& settings);
		UISystem(UISystemSettings&& settings);
		UISystem(const UISystem& other) = delete;
		UISystem(UISystem&& other) = delete;
		~UISystem();

		[[nodiscard]] bool IsRunning();
		void Run();
		void Quit(int exitCode);
		void BeginFrame();
		void Render(Window* window);
		void EndFrame();
		void PushEvent(Window* window, UINT message, WPARAM wParam, LPARAM lParam);
		void ProcessEvents();

		void CreateTextFormat(std::string_view name, const TextFormatSettings& settings);
		void CreateTextFormat(std::string_view name, TextFormatSettings&& settings);

		Window* CreateWindowFromSettings(std::string_view name, const WindowSettings& settings);
		Window* CreateWindowFromSettings(std::string_view name, WindowSettings&& settings);
		template<typename T, typename... Args>
		T* CreateWindowFromSettings(std::string_view name, Args&&... args)
		{
			static_assert(std::is_base_of<Window, T>::value, "T must derive from Window.");
			auto window = std::make_unique<T>(std::forward<Args>(args)...);
			static_cast<Window*>(window.get())->Initialize(GetGraphicsSystem());
			T* wind = window.get();

			try
			{
				CreateWindowFromSettingsImpl(name, std::move(window));
			}
			catch (const std::runtime_error& e)
			{
				return nullptr;
			}

			return wind;
		}

		bool DestroyWindow(std::string_view name);
		[[nodiscard]] Window* GetWindow(std::string_view name);

		UISystem& operator = (const UISystem& other) = delete;
		UISystem& operator = (UISystem&& other) = delete;

	private:
		[[nodiscard]] GraphicsSystem* GetGraphicsSystem() const;
		void CreateWindowFromSettingsImpl(std::string_view name, std::unique_ptr<Window> window);

		struct UISystemImpl;
		std::unique_ptr<UISystemImpl> _impl{};

		friend class EventSystem;
	};

	using UISystemPtr = std::unique_ptr<UISystem>;
	using UISystemSharedPtr = std::shared_ptr<UISystem>;
}

#endif // GRAPHLYUI_UISYSTEM_HEADER
