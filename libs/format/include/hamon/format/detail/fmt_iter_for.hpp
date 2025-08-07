/**
 *	@file	fmt_iter_for.hpp
 *
 *	@brief	fmt_iter_for の定義
 */

#ifndef HAMON_FORMAT_DETAIL_FMT_ITER_FOR_HPP
#define HAMON_FORMAT_DETAIL_FMT_ITER_FOR_HPP


namespace hamon
{

namespace detail
{

// 28.5.6.3 Concept formattable[format.formattable]

// The output iterator isn't specified. A formatter should accept any
// output_iterator. This iterator is a minimal iterator to test the concept.
// (Note testing for (w)format_context would be a valid choice, but requires
// selecting the proper one depending on the type of CharT.)
template <typename CharT>
using fmt_iter_for = CharT*;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORMAT_DETAIL_FMT_ITER_FOR_HPP
