/**
 *	@file	__write_using_trailing_zeros.hpp
 *
 *	@brief	__write_using_trailing_zeros の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___WRITE_USING_TRAILING_ZEROS_HPP
#define HAMON_FORMAT___FORMATTER___WRITE_USING_TRAILING_ZEROS_HPP

#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/format/__formatter/__padding_size.hpp>
#include <hamon/format/__formatter/__fill.hpp>
#include <hamon/format/__formatter/__copy.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace __formatter
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")

/// Writes additional zero's for the precision before the exponent.
/// This is used when the precision requested in the format string is larger
/// than the maximum precision of the floating-point type. These precision
/// digits are always 0.
///
/// \param __exponent           The location of the exponent character.
/// \param __num_trailing_zeros The number of 0's to write before the exponent
///                             character.
template <class _CharT, class _ParserCharT>
auto __write_using_trailing_zeros(
	const _CharT* __first,
	const _CharT* __last,
	hamon::output_iterator<const _CharT&> auto __out_it,
	__format_spec::__parsed_specifications<_ParserCharT> __specs,
	size_t __size,
	const _CharT* __exponent,
	size_t __num_trailing_zeros) -> decltype(__out_it)
{
	//_LIBCPP_ASSERT_INTERNAL(__first <= __last, "Not a valid range");
	//_LIBCPP_ASSERT_INTERNAL(__num_trailing_zeros > 0, "The overload not writing trailing zeros should have been used");

	__formatter::__padding_size_result __padding =
		__formatter::__padding_size(__size + __num_trailing_zeros, __specs.__width_, __specs.__alignment_);
	__out_it = __formatter::__fill(hamon::move(__out_it), __padding.__before_, __specs.__fill_);
	__out_it = __formatter::__copy(__first, __exponent, hamon::move(__out_it));
	__out_it = __formatter::__fill(hamon::move(__out_it), __num_trailing_zeros, _CharT('0'));
	__out_it = __formatter::__copy(__exponent, __last, hamon::move(__out_it));
	return __formatter::__fill(hamon::move(__out_it), __padding.__after_, __specs.__fill_);
}

HAMON_WARNING_POP()

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___WRITE_USING_TRAILING_ZEROS_HPP
