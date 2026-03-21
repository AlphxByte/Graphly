#ifndef GRAPHLY_GRAPHLYWINDOW_HEADER
#define GRAPHLY_GRAPHLYWINDOW_HEADER

#include "GraphlyUI/Window.h"
#include "GraphlyCore/Logger.h"

namespace Graphly
{
	class GraphlyWindow : public GraphlyUI::Window
	{
	public:
		GraphlyWindow(GraphlyCore::Logger* logger, const GraphlyUI::WindowSettings& settings);
		GraphlyWindow(const GraphlyWindow& other) = delete;
		GraphlyWindow(GraphlyWindow&& other) = delete;
		~GraphlyWindow() = default;

		GraphlyWindow& operator = (const GraphlyWindow& other) = delete;
		GraphlyWindow& operator = (GraphlyWindow&& other) = delete;

	private:
		GraphlyCore::Logger* _logger;
	};

	using GraphlyWindowPtr       = std::unique_ptr<GraphlyWindow>;
	using GraphlyWindowSharedPtr = std::shared_ptr<GraphlyWindow>;
}

#endif // GRAPHLY_GRAPHLYWINDOW_HEADER
