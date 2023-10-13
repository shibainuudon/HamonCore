/**
 *	@file	nameof.hpp
 *
 *	@brief
 */

#ifndef HAMON_TYPE_INFO_NAMEOF_HPP
#define HAMON_TYPE_INFO_NAMEOF_HPP

#include <hamon/string_view/string_view.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(__clang__)
    #define HAMON_PRETTY_FUNCTION_PREFIX "const char* hamon::detail::pretty_function() [T = "
    #define HAMON_PRETTY_FUNCTION_SUFFIX "]"
#elif defined(__GNUC__) && !defined(__clang__)
    #define HAMON_PRETTY_FUNCTION_PREFIX "constexpr const char* hamon::detail::pretty_function() [with T = "
    #define HAMON_PRETTY_FUNCTION_SUFFIX "]"
#elif defined(_MSC_VER)
    #define HAMON_PRETTY_FUNCTION_PREFIX "const char* __cdecl hamon::detail::pretty_function<"
    #define HAMON_PRETTY_FUNCTION_SUFFIX ">(void)"
#else
    #error "No support for this compiler."
#endif

#define HAMON_PRETTY_FUNCTION_LEFT  (sizeof(HAMON_PRETTY_FUNCTION_PREFIX) - 1)
#define HAMON_PRETTY_FUNCTION_RIGHT (sizeof(HAMON_PRETTY_FUNCTION_SUFFIX) - 1)

template <typename T>
HAMON_CONSTEXPR const char*
pretty_function()
{
	return HAMON_CURRENT_FUNCTION;
}

HAMON_CONSTEXPR hamon::string_view
get_typename(hamon::string_view sv)
{
	return sv.substr(
		HAMON_PRETTY_FUNCTION_LEFT,
		sv.length() - HAMON_PRETTY_FUNCTION_LEFT - HAMON_PRETTY_FUNCTION_RIGHT
	);
}

HAMON_CONSTEXPR hamon::string_view
remove_prefix(hamon::string_view sv, hamon::string_view prefix)
{
	return sv.starts_with(prefix) ? sv.substr(prefix.length(), sv.length() - prefix.length()) : sv;
}

HAMON_CONSTEXPR hamon::string_view
nameof_impl(hamon::string_view type_name)
{
	return remove_prefix(remove_prefix(remove_prefix(type_name, "class "), "struct "), "enum ");
}

#undef HAMON_PRETTY_FUNCTION_PREFIX
#undef HAMON_PRETTY_FUNCTION_SUFFIX
#undef HAMON_PRETTY_FUNCTION_LEFT
#undef HAMON_PRETTY_FUNCTION_RIGHT

}	// namespace detail

template <typename T>
HAMON_NODISCARD HAMON_CONSTEXPR hamon::string_view
nameof() HAMON_NOEXCEPT
{
	return detail::nameof_impl(detail::get_typename(detail::pretty_function<T>()));
}

}	// namespace hamon

#endif // HAMON_TYPE_INFO_NAMEOF_HPP
