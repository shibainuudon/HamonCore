/**
 *	@file	fmt_maybe_const.hpp
 *
 *	@brief	fmt_maybe_const の定義
 */

#ifndef HAMON_FORMAT_DETAIL_FMT_MAYBE_CONST_HPP
#define HAMON_FORMAT_DETAIL_FMT_MAYBE_CONST_HPP

#include <hamon/format/detail/const_formattable_range.hpp>
#include <hamon/type_traits/conditional.hpp>

namespace hamon
{

namespace detail
{

// [format.formattable], concept formattable

template <typename R, typename charT>
using fmt_maybe_const =
	hamon::conditional_t<hamon::detail::const_formattable_range<R, charT>, const R, R>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORMAT_DETAIL_FMT_MAYBE_CONST_HPP
