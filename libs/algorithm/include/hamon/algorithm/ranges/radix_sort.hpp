/**
 *	@file	radix_sort.hpp
 *
 *	@brief	ranges::radix_sort の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_RADIX_SORT_HPP
#define HAMON_ALGORITHM_RANGES_RADIX_SORT_HPP

#include <hamon/algorithm/radix_sort.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/unsigned_integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/permutable.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter, typename Tmp, typename Proj>
HAMON_CONCEPT_OR_BOOL radix_sortable =
	hamon::permutable<Iter> &&
	hamon::indirectly_swappable<Iter, Tmp> &&
	hamon::unsigned_integral<
		hamon::iter_value_t<hamon::projected<Iter, Proj>>
	>;

#else

template <typename Iter, typename Tmp, typename Proj>
struct radix_sortable_impl
{
private:
	template <typename I, typename T, typename P,
		typename = hamon::enable_if_t<hamon::permutable<I>>,
		typename = hamon::enable_if_t<hamon::indirectly_swappable<I, T>>,
		typename = hamon::enable_if_t<
			hamon::unsigned_integral<
				hamon::iter_value_t<hamon::projected<I, P>>
			>
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename I, typename T, typename P>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter, Tmp, Proj>(0));
};

template <typename Iter, typename Tmp, typename Proj>
HAMON_CONCEPT_OR_BOOL radix_sortable =
	detail::radix_sortable_impl<Iter, Tmp, Proj>::type::value;

#endif

}	// namespace detail

struct radix_sort_fn
{
	template <
		HAMON_CONSTRAINT(hamon::random_access_iterator, Iter),
		HAMON_CONSTRAINT(hamon::sentinel_for, Iter, Sent),
		HAMON_CONSTRAINT(hamon::random_access_iterator, Tmp),
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Iter first, Sent last, Tmp tmp, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES_(
		Iter,
		hamon::ranges::detail::radix_sortable<Iter, Tmp, Proj>)
	{
		auto lasti = ranges::next(first, last);
		hamon::radix_sort(
			hamon::move(first), lasti,
			hamon::move(tmp),
			proj);
		return lasti;
	}

	template <
		HAMON_CONSTRAINT(ranges::random_access_range, Range),
		HAMON_CONSTRAINT(hamon::random_access_iterator, Tmp),
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, Tmp tmp, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES_(
		ranges::borrowed_iterator_t<Range>,
		hamon::ranges::detail::radix_sortable<
			ranges::iterator_t<Range>, Tmp, Proj
		>)
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			hamon::move(tmp),
			hamon::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR radix_sort_fn radix_sort{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_ALGORITHM_RANGES_RADIX_SORT_HPP
