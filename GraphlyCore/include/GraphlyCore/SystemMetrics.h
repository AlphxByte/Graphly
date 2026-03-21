#ifndef GRAPHLYCORE_SYSTEM_METRICS_HEADER
#define GRAPHLYCORE_SYSTEM_METRICS_HEADER

namespace GraphlyCore
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

#endif // GRAPHLYCORE_SYSTEM_METRICS_HEADER
