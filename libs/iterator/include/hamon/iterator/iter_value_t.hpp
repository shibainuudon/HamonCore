/**
 *	@file	iter_value_t.hpp
 *
 *	@brief	iter_value_t の定義
 */

#ifndef HAMON_ITERATOR_ITER_VALUE_T_HPP
#define HAMON_ITERATOR_ITER_VALUE_T_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::iter_value_t;

}	// namespace hamon

#else

#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/iterator/indirectly_readable_traits.hpp>
#include <hamon/iterator/concepts/detail/iter_traits.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
using iter_value_t_impl =
	typename detail::iter_traits<T, hamon::indirectly_readable_traits<T>>::value_type;

}	// namespace detail

template <typename T>
using iter_value_t = detail::iter_value_t_impl<hamon::remove_cvref_t<T>>;

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_ITER_VALUE_T_HPP
