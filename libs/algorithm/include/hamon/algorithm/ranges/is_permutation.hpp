/**
 *	@file	is_permutation.hpp
 *
 *	@brief	ranges::is_permutation の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_IS_PERMUTATION_HPP
#define HAMON_ALGORITHM_RANGES_IS_PERMUTATION_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::is_permutation;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/find_if.hpp>
#include <hamon/algorithm/ranges/count_if.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_equivalence_relation.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

struct is_permutation_fn
{
private:
	template <typename Pred, typename T>
	struct comp_scan_t
	{
		Pred& m_pred;
		T&    m_scan_proj;

		template <typename U>
		HAMON_CXX14_CONSTEXPR auto operator()(U&& arg) const
		->decltype(hamon::invoke(m_pred, m_scan_proj, std::forward<U>(arg)))
		{
			return hamon::invoke(m_pred, m_scan_proj, std::forward<U>(arg));
		}
	};

public:
	template<
		HAMON_CONSTRAINED_PARAM(hamon::forward_iterator, Iter1),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter1, Sent1),
		HAMON_CONSTRAINED_PARAM(hamon::forward_iterator, Iter2),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter2, Sent2),
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity,
		typename ProjectedIter1 = hamon::projected<Iter1, Proj1>,
		typename ProjectedIter2 = hamon::projected<Iter2, Proj2>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_equivalence_relation,
			ProjectedIter1,
			ProjectedIter2,
			Pred,
			hamon::ranges::equal_to)
	>
	HAMON_CXX14_CONSTEXPR bool operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		constexpr bool sized_iters =
			(hamon::sized_sentinel_for_t<Sent1, Iter1>::value &&
			 hamon::sized_sentinel_for_t<Sent2, Iter2>::value);

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (sized_iters)
#else
		if (sized_iters)
#endif
		{
			auto d1 = ranges::distance(first1, last1);
			auto d2 = ranges::distance(first2, last2);
			if (d1 != d2)
			{
				return false;
			}
		}

		// Efficiently compare identical prefixes:  O(N) if sequences
		// have the same elements in the same order.
		for (; first1 != last1 && first2 != last2; ++first1, (void)++first2)
		{
			if (!(bool)hamon::invoke(pred,
				hamon::invoke(proj1, *first1),
				hamon::invoke(proj2, *first2)))
			{
				break;
			}
		}

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (sized_iters)
#else
		if (sized_iters)
#endif
		{
			if (first1 == last1)
			{
				return true;
			}
		}
		else
		{
			auto d1 = ranges::distance(first1, last1);
			auto d2 = ranges::distance(first2, last2);
			if (d1 == 0 && d2 == 0)
			{
				return true;
			}

			if (d1 != d2)
			{
				return false;
			}
		}

		for (auto scan = first1; scan != last1; ++scan)
		{
			const auto scan_proj{ hamon::invoke(proj1, *scan) };
			auto comp_scan = comp_scan_t<Pred, decltype(scan_proj)> {pred, scan_proj};

			if (scan != ranges::find_if(first1, scan, comp_scan, proj1))
			{
				continue; // We've seen this one before.
			}

			auto matches = ranges::count_if(first2, last2, comp_scan, proj2);
			if (matches == 0 || ranges::count_if(scan, last1, comp_scan, proj1) != matches)
			{
				return false;
			}
		}

		return true;
	}

	template<
		HAMON_CONSTRAINED_PARAM(hamon::ranges::forward_range, Range1),
		HAMON_CONSTRAINED_PARAM(hamon::ranges::forward_range, Range2),
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity,
		typename ProjectedIter1 = hamon::projected<ranges::iterator_t<Range1>, Proj1>,
		typename ProjectedIter2 = hamon::projected<ranges::iterator_t<Range2>, Proj2>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_equivalence_relation,
			ProjectedIter1,
			ProjectedIter2,
			Pred,
			hamon::ranges::equal_to)
	>
	HAMON_CXX14_CONSTEXPR bool operator()(
		Range1&& r1,
		Range2&& r2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		return (*this)(
			ranges::begin(r1), ranges::end(r1),
			ranges::begin(r2), ranges::end(r2),
			hamon::move(pred),
			hamon::move(proj1),
			hamon::move(proj2));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR is_permutation_fn is_permutation{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_IS_PERMUTATION_HPP
