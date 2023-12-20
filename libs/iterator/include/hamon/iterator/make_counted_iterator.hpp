/**
 *	@file	make_counted_iterator.hpp
 *
 *	@brief	make_counted_iterator の定義
 */

#ifndef HAMON_ITERATOR_MAKE_COUNTED_ITERATOR_HPP
#define HAMON_ITERATOR_MAKE_COUNTED_ITERATOR_HPP

#include <hamon/iterator/counted_iterator.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <HAMON_CONSTRAINED_PARAM(hamon::input_or_output_iterator, I)>
HAMON_CXX11_CONSTEXPR hamon::counted_iterator<I>
make_counted_iterator(I it, hamon::iter_difference_t<I> n)
HAMON_NOEXCEPT_IF_EXPR(hamon::counted_iterator<I>(hamon::move(it), n))
{
	return hamon::counted_iterator<I>(hamon::move(it), n);
}

}	// namespace hamon

#endif // HAMON_ITERATOR_MAKE_COUNTED_ITERATOR_HPP
