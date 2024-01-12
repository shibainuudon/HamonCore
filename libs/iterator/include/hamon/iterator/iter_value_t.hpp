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

#include <hamon/iterator/indirectly_readable_traits.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/detail/is_iterator_traits_primary.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/remove_cvref.hpp>

namespace hamon
{

namespace detail
{

template <typename RI>
using iter_value_t_impl =
	typename hamon::conditional_t<hamon::detail::is_iterator_traits_primary<RI>::value,
		hamon::indirectly_readable_traits<RI>,	// [readable.traits]2.1
		hamon::iterator_traits<RI>				// [readable.traits]2.2
	>::value_type;

}	// namespace detail

// [readable.traits]/2
template <typename T>
using iter_value_t = detail::iter_value_t_impl<hamon::remove_cvref_t<T>>;

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_ITER_VALUE_T_HPP
