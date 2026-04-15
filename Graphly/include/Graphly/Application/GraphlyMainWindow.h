#ifndef GRAPHLY_GRAPHLY_MAIN_WINDOW_HEADER
#define GRAPHLY_GRAPHLY_MAIN_WINDOW_HEADER

#include "GraphlyUI/UISystem/Window/Window.h"
#include "Logger.h"

namespace Graphly
{
	class GraphlyMainWindow : public GraphlyUI::Window
	{
	public:
		GraphlyMainWindow(Logger* logger, const GraphlyUI::WindowSettings& settings);
		GraphlyMainWindow(const GraphlyMainWindow& other) = delete;
		GraphlyMainWindow(GraphlyMainWindow&& other) = delete;
		~GraphlyMainWindow() = default;

		GraphlyMainWindow& operator = (const GraphlyMainWindow& other) = delete;
		GraphlyMainWindow& operator = (GraphlyMainWindow&& other) = delete;

	private:
		Logger* _logger;
	};

	using GraphlyMainWindowPtr       = std::unique_ptr<GraphlyMainWindow>;
	using GraphlyMainWindowSharedPtr = std::shared_ptr<GraphlyMainWindow>;
}

#endif // GRAPHLY_GRAPHLY_MAIN_WINDOW_HEADER
