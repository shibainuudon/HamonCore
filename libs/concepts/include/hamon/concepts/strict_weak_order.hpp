/**
 *	@file	strict_weak_order.hpp
 *
 *	@brief	strict_weak_order の定義
 */

#ifndef HAMON_CONCEPTS_STRICT_WEAK_ORDER_HPP
#define HAMON_CONCEPTS_STRICT_WEAK_ORDER_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/relation.hpp>
#endif
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

#if defined(HAMON_USE_STD_CONCEPTS)

using std::strict_weak_order;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Rel, typename T, typename U>
concept strict_weak_order = hamon::relation<Rel, T, U>;

#else

template <typename Rel, typename T, typename U>
using strict_weak_order = hamon::relation<Rel, T, U>;

#endif

template <typename Rel, typename T, typename U>
using strict_weak_order_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::strict_weak_order<Rel, T, U>>;
#else
	hamon::strict_weak_order<Rel, T, U>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_STRICT_WEAK_ORDER_HPP
