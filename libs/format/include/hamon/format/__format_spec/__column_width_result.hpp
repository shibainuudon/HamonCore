/**
 *	@file	__column_width_result.hpp
 *
 *	@brief	__column_width_result の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___COLUMN_WIDTH_RESULT_HPP
#define HAMON_FORMAT___FORMAT_SPEC___COLUMN_WIDTH_RESULT_HPP

#include <hamon/iterator/concepts/contiguous_iterator.hpp>

namespace hamon
{

namespace __format_spec
{

template <hamon::contiguous_iterator _Iterator>
struct __column_width_result
{
	/// The number of output columns.
	size_t __width_;
	/// One beyond the last code unit used in the estimation.
	///
	/// This limits the original output to fit in the wanted number of columns.
	_Iterator __last_;
};

template <hamon::contiguous_iterator _Iterator>
__column_width_result(size_t, _Iterator) -> __column_width_result<_Iterator>;

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___COLUMN_WIDTH_RESULT_HPP
