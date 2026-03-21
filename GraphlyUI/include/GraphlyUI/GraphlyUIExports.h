#ifndef GRAPHLYUI_EXPORTS_HEADER
#define GRAPHLYUI_EXPORTS_HEADER

#ifndef GRAPHLYUI_API

#ifdef GRAPHLYUI_EXPORTS
#define GRAPHLYUI_API __declspec(dllexport)
#else
#define GRAPHLYUI_API __declspec(dllimport)
#endif // GRAPHLYUI_EXPORTS

#endif // GRAPHLYUI_API

#endif // GRAPHLYUI_EXPORTS_HEADER
