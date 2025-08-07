/**
 *	@file	__write_string.hpp
 *
 *	@brief	__write_string の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___WRITE_STRING_HPP
#define HAMON_FORMAT___FORMATTER___WRITE_STRING_HPP

#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/format/__formatter/__write_string_no_precision.hpp>
#include <hamon/format/__formatter/__truncate.hpp>
#include <hamon/format/__formatter/__write.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/string_view.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace __formatter
{

/// Writes a string using format's width estimation algorithm.
///
/// \note When \c _LIBCPP_HAS_UNICODE is false the function assumes the input is ASCII.
template <class _CharT>
auto
__write_string(hamon::basic_string_view<_CharT> __str,
			   hamon::output_iterator<const _CharT&> auto __out_it,
			   __format_spec::__parsed_specifications<_CharT> __specs) -> decltype(__out_it)
{
	if (!__specs.__has_precision())
	{
		return __formatter::__write_string_no_precision(__str, hamon::move(__out_it), __specs);
	}

	int __size = __formatter::__truncate(__str, __specs.__precision_);

	return __formatter::__write(__str.begin(), __str.end(), hamon::move(__out_it), __specs, __size);
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___WRITE_STRING_HPP
