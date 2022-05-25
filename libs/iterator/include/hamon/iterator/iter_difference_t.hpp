/**
 *	@file	iter_difference_t.hpp
 *
 *	@brief	iter_difference_t の定義
 */

#ifndef HAMON_ITERATOR_ITER_DIFFERENCE_T_HPP
#define HAMON_ITERATOR_ITER_DIFFERENCE_T_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::iter_difference_t;

}	// namespace hamon

#else

#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/iterator/incrementable_traits.hpp>
#include <hamon/iterator/concepts/detail/iter_traits.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
using iter_diff_t_impl =
	typename detail::iter_traits<T, hamon::incrementable_traits<T>>::difference_type;

}	// namespace detail

template <typename T>
using iter_difference_t = detail::iter_diff_t_impl<hamon::remove_cvref_t<T>>;

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_ITER_DIFFERENCE_T_HPP
