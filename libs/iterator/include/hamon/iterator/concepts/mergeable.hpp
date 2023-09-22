/**
 *	@file	mergeable.hpp
 *
 *	@brief	mergeable の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_MERGEABLE_HPP
#define HAMON_ITERATOR_CONCEPTS_MERGEABLE_HPP

#include <hamon/iterator/config.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES_ITERATOR)
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/iterator/concepts/indirectly_copyable.hpp>
#include <hamon/iterator/concepts/indirect_strict_weak_order.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/type_traits/enable_if.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

using std::mergeable;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <
	typename I1,
	typename I2,
	typename Out,
	typename Rel = hamon::ranges::less,
	typename P1 = hamon::identity,
	typename P2 = hamon::identity
>
concept mergeable =
	hamon::input_iterator<I1> &&
	hamon::input_iterator<I2> &&
	hamon::weakly_incrementable<Out> &&
	hamon::indirectly_copyable<I1, Out> &&
	hamon::indirectly_copyable<I2, Out> &&
	hamon::indirect_strict_weak_order<Rel, hamon::projected<I1, P1>, hamon::projected<I2, P2>>;

#else

namespace detail
{

template <typename I1, typename I2, typename Out, typename Rel, typename P1, typename P2>
struct mergeable_impl
{
private:
	template <typename J1, typename J2, typename O2, typename R2, typename Q1, typename Q2,
		typename = hamon::enable_if_t<hamon::input_iterator<J1>::value>,
		typename = hamon::enable_if_t<hamon::input_iterator<J2>::value>,
		typename = hamon::enable_if_t<hamon::weakly_incrementable<O2>::value>,
		typename = hamon::enable_if_t<hamon::indirectly_copyable<J1, O2>::value>,
		typename = hamon::enable_if_t<hamon::indirectly_copyable<J2, O2>::value>,
		typename = hamon::enable_if_t<hamon::indirect_strict_weak_order<
			R2, hamon::projected<J1, Q1>, hamon::projected<J2, Q2>>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename J1, typename J2, typename O2, typename R2, typename Q1, typename Q2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<I1, I2, Out, Rel, P1, P2>(0));
};

}	// namespace detail

template <
	typename I1,
	typename I2,
	typename Out,
	typename Rel = hamon::ranges::less,
	typename P1 = hamon::identity,
	typename P2 = hamon::identity
>
using mergeable =
	typename detail::mergeable_impl<I1, I2, Out, Rel, P1, P2>::type;

#endif

template <
	typename I1,
	typename I2,
	typename Out,
	typename Rel = hamon::ranges::less,
	typename P1 = hamon::identity,
	typename P2 = hamon::identity
>
using mergeable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::mergeable<I1, I2, Out, Rel, P1, P2>>;
#else
	hamon::mergeable<I1, I2, Out, Rel, P1, P2>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_MERGEABLE_HPP
