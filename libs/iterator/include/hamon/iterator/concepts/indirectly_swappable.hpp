/**
 *	@file	indirectly_swappable.hpp
 *
 *	@brief	indirectly_swappable の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_INDIRECTLY_SWAPPABLE_HPP
#define HAMON_ITERATOR_CONCEPTS_INDIRECTLY_SWAPPABLE_HPP

#include <hamon/iterator/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES_ITERATOR)
#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

using std::indirectly_swappable;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename I1, typename I2 = I1>
concept indirectly_swappable =
	hamon::indirectly_readable<I1> &&
	hamon::indirectly_readable<I2> &&
	requires(I1 const i1, I2 const i2)
	{
		hamon::ranges::iter_swap(i1, i1);
		hamon::ranges::iter_swap(i2, i2);
		hamon::ranges::iter_swap(i1, i2);
		hamon::ranges::iter_swap(i2, i1);
	};

#else

namespace detail
{

template <typename I1, typename I2>
struct indirectly_swappable_impl
{
private:
	template <typename J1, typename J2,
		typename = hamon::enable_if_t<hamon::indirectly_readable<J1>::value>,
		typename = hamon::enable_if_t<hamon::indirectly_readable<J2>::value>,
		typename = decltype(hamon::ranges::iter_swap(hamon::declval<J1 const>(), hamon::declval<J1 const>())),
		typename = decltype(hamon::ranges::iter_swap(hamon::declval<J1 const>(), hamon::declval<J2 const>())),
		typename = decltype(hamon::ranges::iter_swap(hamon::declval<J2 const>(), hamon::declval<J1 const>())),
		typename = decltype(hamon::ranges::iter_swap(hamon::declval<J2 const>(), hamon::declval<J2 const>()))
	>
	static auto test(int) -> hamon::true_type;

	template <typename J1, typename J2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<I1, I2>(0));
};

}	// namespace detail

template <typename I1, typename I2 = I1>
using indirectly_swappable =
	typename detail::indirectly_swappable_impl<I1, I2>::type;

#endif

template <typename I1, typename I2 = I1>
using indirectly_swappable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::indirectly_swappable<I1, I2>>;
#else
	hamon::indirectly_swappable<I1, I2>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_INDIRECTLY_SWAPPABLE_HPP
