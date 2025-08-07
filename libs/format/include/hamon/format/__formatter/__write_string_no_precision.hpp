/**
 *	@file	__write_string_no_precision.hpp
 *
 *	@brief	__write_string_no_precision の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___WRITE_STRING_NO_PRECISION_HPP
#define HAMON_FORMAT___FORMATTER___WRITE_STRING_NO_PRECISION_HPP

#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/format/__format_spec/__estimate_column_width.hpp>
#include <hamon/format/__format_spec/__column_width_rounding.hpp>
#include <hamon/format/__formatter/__copy.hpp>
#include <hamon/format/__formatter/__write.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/string_view.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace __formatter
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")

/// Writes a string using format's width estimation algorithm.
///
/// \pre !__specs.__has_precision()
///
/// \note When \c _LIBCPP_HAS_UNICODE is false the function assumes the input is ASCII.
template <class _CharT>
auto __write_string_no_precision(
	hamon::basic_string_view<_CharT> __str,
	hamon::output_iterator<const _CharT&> auto __out_it,
	__format_spec::__parsed_specifications<_CharT> __specs) -> decltype(__out_it)
{
	//_LIBCPP_ASSERT_INTERNAL(!__specs.__has_precision(), "use __write_string");

	// No padding -> copy the string
	if (!__specs.__has_width())
	{
		return __formatter::__copy(__str, hamon::move(__out_it));
	}

	// Note when the estimated width is larger than size there's no padding. So
	// there's no reason to get the real size when the estimate is larger than or
	// equal to the minimum field width.
	size_t __size =
		__format_spec::__estimate_column_width(__str, __specs.__width_, __format_spec::__column_width_rounding::__up)
		.__width_;
	return __formatter::__write(__str, hamon::move(__out_it), __specs, __size);
}

HAMON_WARNING_POP()

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___WRITE_STRING_NO_PRECISION_HPP
