/**
 *	@file	range_formatter.hpp
 *
 *	@brief	range_formatter の定義
 */

#ifndef HAMON_FORMAT_RANGE_FORMATTER_HPP
#define HAMON_FORMAT_RANGE_FORMATTER_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::range_formatter;

}	// namespace hamon

#else

#include <hamon/format/formattable.hpp>
#include <hamon/format/formatter.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits/remove_cvref.hpp>

namespace hamon
{

// 28.5.7.2 Class template range_formatter[format.range.formatter]

template <typename T, typename charT = char>
//	requires hamon::same_as<hamon::remove_cvref_t<T>, T> && hamon::formattable<T, charT>
class range_formatter
{
	hamon::formatter<T, charT> underlying_;                                          // exposition only
	hamon::basic_string_view<charT> separator_       = HAMON_STATICALLY_WIDEN(charT, ", ");      // exposition only
	hamon::basic_string_view<charT> opening_bracket_ = HAMON_STATICALLY_WIDEN(charT, "["); // exposition only
	hamon::basic_string_view<charT> closing_bracket_ = HAMON_STATICALLY_WIDEN(charT, "]"); // exposition only

public:
	HAMON_CXX14_CONSTEXPR void
	set_separator(hamon::basic_string_view<charT> sep) noexcept
	{
		// [format.range.formatter]/7
		separator_ = sep;
	}

	HAMON_CXX14_CONSTEXPR void
	set_brackets(hamon::basic_string_view<charT> opening, hamon::basic_string_view<charT> closing) noexcept
	{
		// [format.range.formatter]/8
		opening_bracket_ = opening;
		closing_bracket_ = closing;
	}

	HAMON_CXX14_CONSTEXPR hamon::formatter<T, charT>&
	underlying() noexcept
	{
		return underlying_;
	}

	constexpr hamon::formatter<T, charT> const&
	underlying() const noexcept
	{
		return underlying_;
	}

	template <typename ParseContext>
	HAMON_CXX14_CONSTEXPR typename ParseContext::iterator
	parse(ParseContext& ctx);

	//template <hamon::ranges::input_range R, typename FormatContext>
	//requires hamon::formattable<hamon::ranges::range_reference_t<R>, charT> &&
	//	hamon::same_as<hamon::remove_cvref_t<hamon::ranges::range_reference_t<R>>, T>
	//typename FormatContext::iterator
	//format(R&& r, FormatContext& ctx) const;
};

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_RANGE_FORMATTER_HPP
