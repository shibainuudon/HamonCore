/**
 *	@file	const_formattable_range.hpp
 *
 *	@brief	const_formattable_range の定義
 */

#ifndef HAMON_FORMAT_DETAIL_CONST_FORMATTABLE_RANGE_HPP
#define HAMON_FORMAT_DETAIL_CONST_FORMATTABLE_RANGE_HPP

#include <hamon/format/formattable.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/range_reference_t.hpp>

namespace hamon
{

namespace detail
{

// [format.formattable], concept formattable

template <typename R, typename charT>
concept const_formattable_range =
	hamon::ranges::input_range<const R> &&
	hamon::formattable<hamon::ranges::range_reference_t<const R>, charT>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORMAT_DETAIL_CONST_FORMATTABLE_RANGE_HPP
