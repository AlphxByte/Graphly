#ifndef GRAPHLYUI_WIBDOW_STYLES_HEADER
#define GRAPHLYUI_WIBDOW_STYLES_HEADER

#include "../../GraphlyUIExports.h"

#include <windows.h>

namespace GraphlyUI
{
	enum class GRAPHLYUI_API WindowStyleFlags : unsigned
	{
		None = 0,
        Visible = WS_VISIBLE,
		OverlappedWindow = WS_OVERLAPPEDWINDOW
	};

	enum class GRAPHLYUI_API WindowExStyleFlags : unsigned
	{
		None = 0
	};

    enum class GRAPHLYUI_API WindowIconFlags
    {
        Other,
        Application,
        Asterisk,
        Error,
        Exclamation,
        Hand,
        Information,
        Question,
        Warning,
        Winlogo,
        Shield
    };

    enum class GRAPHLYUI_API WindowCursorFlags
    {
        Other,
        Arrow,
        IBeam,
        Wait,
        Cross,
        UpArrow,
        Size,
        Icon,
        Sizenwse,
        Sizenesw,
        Sizewe,
        Sizens,
        SizeAll,
        No,
        Hand,
        Appstarting
    };

    template<typename T>
    struct BitWiseOperations
    {
        static constexpr bool value = false;
    };

    template<>
    struct BitWiseOperations<WindowStyleFlags>
    {
        static constexpr bool value = true;
    };

    template<>
    struct BitWiseOperations<WindowExStyleFlags>
    {
        static constexpr bool value = true;
    };

    template<typename Flag>
    inline constexpr std::enable_if_t<BitWiseOperations<Flag>::value, Flag>
    operator|(const Flag& ls, const Flag& rs)
    {
        using Type = std::underlying_type_t<Flag>;
        return static_cast<Flag>
        (
            static_cast<Type>(ls) |
            static_cast<Type>(rs)
       );
    }

    template<typename Flag>
    inline constexpr std::enable_if_t<BitWiseOperations<Flag>::value, Flag>
    operator&(const Flag& ls, const Flag& rs) 
    {
        using Type = std::underlying_type_t<Flag>;
        return static_cast<Flag>
        (
            static_cast<Type>(ls) &
            static_cast<Type>(rs)
        );
    }

    template<typename Flag>
    inline constexpr std::enable_if_t<BitWiseOperations<Flag>::value, Flag>
    operator^(const Flag& ls, const Flag& rs)
    {
        using Type = std::underlying_type_t<Flag>;
        return static_cast<Flag>
        (
            static_cast<Type>(ls) &
            static_cast<Type>(rs)
        );
    }

    template<typename Flag>
    inline constexpr std::enable_if_t<BitWiseOperations<Flag>::value, Flag>
    operator~(const Flag& f)
    {
        using Type = std::underlying_type_t<Flag>;
        return static_cast<Flag>(~static_cast<Type>(f));
    }

    template<typename Flag>
    inline constexpr std::enable_if_t<BitWiseOperations<Flag>::value, Flag>
    operator|=(Flag& ls, const Flag& rs)
    {
        ls = ls | rs;
        return rs;
    }

    template<typename Flag>
    inline constexpr std::enable_if_t<BitWiseOperations<Flag>::value, Flag>
    operator&=(Flag& ls, const Flag& rs)
    {
        ls = ls & rs;
        return ls;
    }

    template<typename Flag>
    inline constexpr std::enable_if_t<BitWiseOperations<Flag>::value, Flag>
    operator^=(Flag& ls, const Flag& rs)
    {
        ls = ls ^ rs;
        return ls;
    }
}

#endif // GRAPHLYUI_WIBDOW_STYLES_HEADER