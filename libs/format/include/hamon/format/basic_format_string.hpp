/**
 *	@file	basic_format_string.hpp
 *
 *	@brief	basic_format_string の定義
 */

#ifndef HAMON_FORMAT_BASIC_FORMAT_STRING_HPP
#define HAMON_FORMAT_BASIC_FORMAT_STRING_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::basic_format_string;

}	// namespace hamon

#else

#include <hamon/format/detail/runtime_format_string.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/string_view.hpp>

namespace hamon
{

// 28.5.4 Class template basic_format_string[format.fmt.string]

template <typename charT, typename... Args>
struct basic_format_string
{
private:
	hamon::basic_string_view<charT> str;

public:
	template <typename T>
	requires hamon::convertible_to<T const&, hamon::basic_string_view<charT>>	// [format.fmt.string]/1
	consteval
	basic_format_string(T const& s)
		: str(s)	// [format.fmt.string]/2
	{
		// [format.fmt.string]/3
		// TODO
//		__format::_Checking_scanner<charT, hamon::remove_cvref_t<Args>...> __scanner(str);
//		__scanner._M_scan();
	}

	basic_format_string(hamon::detail::runtime_format_string<charT> s) noexcept
		: str(s.str) {}

	constexpr hamon::basic_string_view<charT>
	get() const noexcept { return str; }
};

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_BASIC_FORMAT_STRING_HPP
