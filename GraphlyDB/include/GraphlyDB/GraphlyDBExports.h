#ifndef GRAPHLYDB_EXPORTS_HEADER
#define GRAPHLYDB_EXPORTS_HEADER

#ifdef GRAPHYDB_EXPORTS
#define GRAPHLYDB_API __declspec(dllexport)
#else
#define GRAPHLYDB_API __declspec(dllimport)
#endif

#endif // GRAPHLYDB_EXPORTS_HEADER
