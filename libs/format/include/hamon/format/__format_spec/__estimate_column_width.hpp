/**
 *	@file	__estimate_column_width.hpp
 *
 *	@brief	__estimate_column_width の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___ESTIMATE_COLUMN_WIDTH_HPP
#define HAMON_FORMAT___FORMAT_SPEC___ESTIMATE_COLUMN_WIDTH_HPP

#include <hamon/format/__format_spec/__column_width_result.hpp>
#include <hamon/format/__format_spec/__column_width_rounding.hpp>
#include <hamon/format/__format/__width_estimation_table.hpp>
#include <hamon/format/other/__unicode.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/string_view.hpp>

namespace hamon
{

namespace __format_spec
{

namespace __detail
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")

template <hamon::contiguous_iterator _Iterator>
constexpr __format_spec::__column_width_result<_Iterator>
__estimate_column_width_grapheme_clustering(
    _Iterator __first, _Iterator __last, size_t __maximum, __format_spec::__column_width_rounding __rounding) noexcept
{
	using _CharT = hamon::iter_value_t<_Iterator>;
	__unicode::__extended_grapheme_cluster_view<_CharT> __view {__first, __last};

	__format_spec::__column_width_result<_Iterator> __result {0, __first};
	while (__result.__last_ != __last && __result.__width_ <= __maximum)
	{
		typename __unicode::__extended_grapheme_cluster_view<_CharT>::__cluster __cluster = __view.__consume();
		int __width = __width_estimation_table::__estimated_width(__cluster.__code_point_);

		// When the next entry would exceed the maximum width the previous width
		// might be returned. For example when a width of 100 is requested the
		// returned width might be 99, since the next code point has an estimated
		// column width of 2. This depends on the rounding flag.
		// When the maximum is exceeded the loop will abort the next iteration.
		if (__rounding == __format_spec::__column_width_rounding::__down && __result.__width_ + __width > __maximum)
		{
			return __result;
		}

		__result.__width_ += __width;
		__result.__last_ = __cluster.__last_;
	}

	return __result;
}

HAMON_WARNING_POP()

} // namespace __detail

// Unicode can be stored in several formats: UTF-8, UTF-16, and UTF-32.
// Depending on format the relation between the number of code units stored and
// the number of output columns differs. The first relation is the number of
// code units forming a code point. (The text assumes the code units are
// unsigned.)
// - UTF-8 The number of code units is between one and four. The first 127
//   Unicode code points match the ASCII character set. When the highest bit is
//   set it means the code point has more than one code unit.
// - UTF-16: The number of code units is between 1 and 2. When the first
//   code unit is in the range [0xd800,0xdfff) it means the code point uses two
//   code units.
// - UTF-32: The number of code units is always one.
//
// The code point to the number of columns is specified in
// [format.string.std]/11. This list might change in the future.
//
// Another thing to be taken into account is Grapheme clustering. This means
// that in some cases multiple code points are combined one element in the
// output. For example:
// - an ASCII character with a combined diacritical mark
// - an emoji with a skin tone modifier
// - a group of combined people emoji to create a family
// - a combination of flag emoji
//
// See also:
// - [format.string.general]/11
// - https://en.wikipedia.org/wiki/UTF-8#Encoding
// - https://en.wikipedia.org/wiki/UTF-16#U+D800_to_U+DFFF

constexpr bool __is_ascii(char32_t __c) { return __c < 0x80; }

/// Determines the number of output columns needed to render the input.
///
/// \note When the scanner encounters malformed Unicode it acts as-if every
/// code unit is a one column code point. Typically a terminal uses the same
/// strategy and replaces every malformed code unit with a one column
/// replacement character.
///
/// \param __first    Points to the first element of the input range.
/// \param __last     Points beyond the last element of the input range.
/// \param __maximum  The maximum number of output columns. The returned number
///                   of estimated output columns will not exceed this value.
/// \param __rounding Selects the rounding method.
///                   \c __down result.__width_ <= __maximum
///                   \c __up result.__width_ <= __maximum + 1
template <class _CharT, class _Iterator = typename hamon::basic_string_view<_CharT>::const_iterator>
constexpr __format_spec::__column_width_result<_Iterator>
__estimate_column_width(
    hamon::basic_string_view<_CharT> __str, size_t __maximum, __format_spec::__column_width_rounding __rounding) noexcept
{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")

	// The width estimation is done in two steps:
	// - Quickly process for the ASCII part. ASCII has the following properties
	//   - One code unit is one code point
	//   - Every code point has an estimated width of one
	// - When needed it will a Unicode Grapheme clustering algorithm to find
	//   the proper place for truncation.

	if (__str.empty() || __maximum == 0)
	{
		return {0, __str.begin()};
	}

	// ASCII has one caveat; when an ASCII character is followed by a non-ASCII
	// character they might be part of an extended grapheme cluster. For example:
	//   an ASCII letter and a COMBINING ACUTE ACCENT
	// The truncate should happen after the COMBINING ACUTE ACCENT. Therefore we
	// need to scan one code unit beyond the requested precision. When this code
	// unit is non-ASCII we omit the current code unit and let the Grapheme
	// clustering algorithm do its work.
	auto __it = __str.begin();
	if (__format_spec::__is_ascii(*__it))
	{
		do
		{
			--__maximum;
			++__it;
			if (__it == __str.end())
			{
				return {__str.size(), __str.end()};
			}

			if (__maximum == 0)
			{
				if (__format_spec::__is_ascii(*__it))
				{
					return {static_cast<size_t>(__it - __str.begin()), __it};
				}

				break;
			}
		}
		while (__format_spec::__is_ascii(*__it));
		--__it;
		++__maximum;
	}

	ptrdiff_t __ascii_size = __it - __str.begin();
	__format_spec::__column_width_result __result =
		__detail::__estimate_column_width_grapheme_clustering(__it, __str.end(), __maximum, __rounding);

	__result.__width_ += __ascii_size;
	return __result;
HAMON_WARNING_POP()
}

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___ESTIMATE_COLUMN_WIDTH_HPP
