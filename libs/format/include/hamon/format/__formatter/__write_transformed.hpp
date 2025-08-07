/**
 *	@file	__write_transformed.hpp
 *
 *	@brief	__write_transformed の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___WRITE_TRANSFORMED_HPP
#define HAMON_FORMAT___FORMATTER___WRITE_TRANSFORMED_HPP

#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/format/__formatter/__transform.hpp>
#include <hamon/format/__formatter/__padding_size.hpp>
#include <hamon/format/__formatter/__fill.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace __formatter
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")

template <hamon::contiguous_iterator _Iterator,
	class _CharT = typename hamon::iterator_traits<_Iterator>::value_type,
	class _ParserCharT,
	class _UnaryOperation>
auto __write_transformed(
		_Iterator __first,
		_Iterator __last,
		hamon::output_iterator<const _CharT&> auto __out_it,
		__format_spec::__parsed_specifications<_ParserCharT> __specs,
		_UnaryOperation __op) -> decltype(__out_it)
{
//	_LIBCPP_ASSERT_VALID_INPUT_RANGE(__first <= __last, "Not a valid range");

	ptrdiff_t __size = __last - __first;
	if (__size >= __specs.__width_)
	{
		return __formatter::__transform(__first, __last, hamon::move(__out_it), __op);
	}

	__padding_size_result __padding = __formatter::__padding_size(__size, __specs.__width_, __specs.__alignment_);
	__out_it                        = __formatter::__fill(hamon::move(__out_it), __padding.__before_, __specs.__fill_);
	__out_it                        = __formatter::__transform(__first, __last, hamon::move(__out_it), __op);
	return __formatter::__fill(hamon::move(__out_it), __padding.__after_, __specs.__fill_);
}

HAMON_WARNING_POP()

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___WRITE_TRANSFORMED_HPP
