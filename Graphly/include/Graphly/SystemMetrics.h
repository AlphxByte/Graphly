#ifndef GRAPHLY_SYSTEM_METRICS_HEADER
#define GRAPHLY_SYSTEM_METRICS_HEADER

namespace Graphly
{
	class SystemMetrics final
	{
	public:
		SystemMetrics() = default;
		SystemMetrics(const SystemMetrics& other) = delete;
		SystemMetrics(SystemMetrics&& other) = delete;
		~SystemMetrics() = default;

		static unsigned GetScreenWidth();
		static unsigned GetScreenHeight();

		SystemMetrics& operator = (const SystemMetrics& other) = delete;
		SystemMetrics& operator = (SystemMetrics&& other) = delete;
	};
}

#endif // GRAPHLY_SYSTEM_METRICS_HEADER
