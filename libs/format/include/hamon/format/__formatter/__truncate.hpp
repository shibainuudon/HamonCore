/**
 *	@file	__truncate.hpp
 *
 *	@brief	__truncate の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___TRUNCATE_HPP
#define HAMON_FORMAT___FORMATTER___TRUNCATE_HPP

#include <hamon/format/__format_spec/__column_width_result.hpp>
#include <hamon/format/__format_spec/__column_width_rounding.hpp>
#include <hamon/format/__format_spec/__estimate_column_width.hpp>
#include <hamon/string_view.hpp>

namespace hamon
{

namespace __formatter
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")

template <class _CharT>
int __truncate(hamon::basic_string_view<_CharT>& __str, int __precision)
{
	__format_spec::__column_width_result __result =
		__format_spec::__estimate_column_width(__str, __precision, __format_spec::__column_width_rounding::__down);
	__str = hamon::basic_string_view<_CharT> {__str.begin(), __result.__last_};
	return static_cast<int>(__result.__width_);
}

HAMON_WARNING_POP()

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___TRUNCATE_HPP
