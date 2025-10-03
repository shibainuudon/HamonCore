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

#include <hamon/format/basic_format_parse_context.hpp>
#include <hamon/format/detail/runtime_format_string.hpp>
#include <hamon/format/__format/__compile_time_basic_format_context.hpp>
#include <hamon/format/__format/__compile_time_handle.hpp>
#include <hamon/format/__format/__arg_t.hpp>
#include <hamon/format/__format/__determine_arg_t.hpp>
#include <hamon/format/__format/__vformat_to.hpp>
#include <hamon/array.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits/remove_cvref.hpp>

namespace hamon
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4127)	// 条件式が定数です。

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
		using Context = __format::__compile_time_basic_format_context<charT>;

		hamon::array<__format::__arg_t, sizeof...(Args)> __types_ {
			__format::__determine_arg_t<Context, hamon::remove_cvref_t<Args>>()...};

		hamon::array<__format::__compile_time_handle<charT>, sizeof...(Args)> __handles_ {[] {
			using U = hamon::remove_cvref_t<Args>;
			__format::__compile_time_handle<charT> __handle;
			if (__format::__determine_arg_t<Context, U>() == __format::__arg_t::__handle)
			{
				__handle.template __enable<U>();
			}

			return __handle;
		}()...};

		// [format.fmt.string]/3
		__format::__vformat_to(
			hamon::basic_format_parse_context<charT>{str, sizeof...(Args)},
			Context{__types_.data(), __handles_.data(), sizeof...(Args)});
	}

	basic_format_string(hamon::detail::runtime_format_string<charT> s) noexcept
		: str(s.str) {}

	constexpr hamon::basic_string_view<charT>
	get() const noexcept { return str; }
};

HAMON_WARNING_POP()

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_BASIC_FORMAT_STRING_HPP
