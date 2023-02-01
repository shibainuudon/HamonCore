/**
 *	@file	sortable.hpp
 *
 *	@brief	sortable の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_SORTABLE_HPP
#define HAMON_ITERATOR_CONCEPTS_SORTABLE_HPP

#include <hamon/iterator/config.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/ranges/less.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::sortable;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/permutable.hpp>
#include <hamon/iterator/concepts/indirect_strict_weak_order.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <
	typename Iter,
	typename Rel = hamon::ranges::less,
	typename Proj = hamon::identity
>
concept sortable =
	hamon::permutable<Iter> &&
	hamon::indirect_strict_weak_order<Rel, hamon::projected<Iter, Proj>>;

#else

namespace detail
{

template <typename Iter, typename Rel, typename Proj>
struct sortable_impl
{
private:
	template <typename I, typename R, typename P,
		typename = hamon::enable_if_t<hamon::permutable<I>::value>,
		typename = hamon::enable_if_t<hamon::indirect_strict_weak_order<
			R, hamon::projected<I, P>>::value>
	>
	static auto test(int) -> std::true_type;

	template <typename I, typename R, typename P>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<Iter, Rel, Proj>(0));
};

}	// namespace detail

template <
	typename Iter,
	typename Rel = hamon::ranges::less,
	typename Proj = hamon::identity
>
using sortable =
	typename detail::sortable_impl<Iter, Rel, Proj>::type;

#endif

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <
	typename Iter,
	typename Rel = hamon::ranges::less,
	typename Proj = hamon::identity
>
using sortable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::sortable<Iter, Rel, Proj>>;
#else
	hamon::sortable<Iter, Rel, Proj>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_SORTABLE_HPP
