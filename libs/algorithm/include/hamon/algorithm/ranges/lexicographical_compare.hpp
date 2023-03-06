/**
 *	@file	lexicographical_compare.hpp
 *
 *	@brief	ranges::lexicographical_compare の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_LEXICOGRAPHICAL_COMPARE_HPP
#define HAMON_ALGORITHM_RANGES_LEXICOGRAPHICAL_COMPARE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::lexicographical_compare;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
//#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_strict_weak_order.hpp>
#include <hamon/iterator/projected.hpp>
//#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
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

struct lexicographical_compare_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter1),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter1, Sent1),
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter2),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter2, Sent2),
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity,
		typename ProjectedIter1 = hamon::projected<Iter1, Proj1>,
		typename ProjectedIter2 = hamon::projected<Iter2, Proj2>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_strict_weak_order,
			ProjectedIter1,
			ProjectedIter2,
			Comp,
			ranges::less)
	>
	HAMON_CXX14_CONSTEXPR bool operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Comp  comp  = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
#if 0
		if constexpr (
			detail::is_normal_iterator<Iter1> &&
			same_as<Iter1, Sent1>)
		{
			return (*this)(first1.base(), last1.base(),
				hamon::move(first2), hamon::move(last2),
				hamon::move(comp),
				hamon::move(proj1), hamon::move(proj2));
		}
		else if constexpr (
			detail::is_normal_iterator<Iter2> &&
			same_as<Iter2, Sent2>)
		{
			return (*this)(hamon::move(first1), hamon::move(last1),
				first2.base(), last2.base(),
				hamon::move(comp),
				hamon::move(proj1), hamon::move(proj2));
		}
		else
#endif
		{
#if 0
			constexpr bool sized_iters =
				(hamon::sized_sentinel_for<Sent1, Iter1> &&
				 hamon::sized_sentinel_for<Sent2, Iter2>);
			if constexpr (sized_iters)
			{
				using ValueType1 = hamon::iter_value_t<Iter1>;
				using ValueType2 = hamon::iter_value_t<Iter2>;
				// This condition is consistent with the one in
				// lexicographical_compare_aux in <bits/stl_algobase.h>.
				constexpr bool use_memcmp = (is_byte<ValueType1>::value
						&& is_byte<ValueType2>::value
						&& !gnu_cxx::numeric_traits<ValueType1>::is_signed
						&& !gnu_cxx::numeric_traits<ValueType2>::is_signed
						&& ptr_to_nonvolatile<Iter1>
						&& ptr_to_nonvolatile<Iter2>
						&& (is_same_v<Comp, ranges::less>
							|| is_same_v<Comp, ranges::greater>)
						&& is_same_v<Proj1, hamon::identity>
						&& is_same_v<Proj2, hamon::identity>);
				if constexpr (use_memcmp)
				{
					const auto d1 = last1 - first1;
					const auto d2 = last2 - first2;

					if (const auto len = std::min(d1, d2))
					{
						const auto c = std::memcmp(first1, first2, len);
						if constexpr (is_same_v<Comp, ranges::less>)
						{
							if (c < 0)
							{
								return true;
							}
							if (c > 0)
							{
								return false;
							}
						}
						else if constexpr (is_same_v<Comp, ranges::greater>)
						{
							if (c > 0)
							{
								return true;
							}
							if (c < 0)
							{
								return false;
							}
						}
					}

					return d1 < d2;
				}
			}
#endif

			for (; first1 != last1 && first2 != last2; ++first1, (void)++first2)
			{
				if (hamon::invoke(comp,
					hamon::invoke(proj1, *first1),
					hamon::invoke(proj2, *first2)))
				{
					return true;
				}

				if (hamon::invoke(comp,
					hamon::invoke(proj2, *first2),
					hamon::invoke(proj1, *first1)))
				{
					return false;
				}
			}

			return first1 == last1 && first2 != last2;
		}
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range1),
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range2),
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity,
		typename ProjectedIter1 = hamon::projected<ranges::iterator_t<Range1>, Proj1>,
		typename ProjectedIter2 = hamon::projected<ranges::iterator_t<Range2>, Proj2>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_strict_weak_order,
			ProjectedIter1,
			ProjectedIter2,
			Comp,
			ranges::less)
	>
	HAMON_CXX14_CONSTEXPR bool operator()(
		Range1&& r1, Range2&& r2,
		Comp comp = {},
		Proj1 proj1 = {}, Proj2 proj2 = {}) const
	{
		return (*this)(
			ranges::begin(r1), ranges::end(r1),
			ranges::begin(r2), ranges::end(r2),
			hamon::move(comp),
			hamon::move(proj1), hamon::move(proj2));
	}

private:
#if 0
	template <typename Iter, typename Ref = iter_reference_t<Iter>>
	static constexpr bool ptr_to_nonvolatile =
		is_pointer_v<Iter> && !is_volatile_v<remove_reference_t<Ref>>;
#endif
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR lexicographical_compare_fn lexicographical_compare{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_LEXICOGRAPHICAL_COMPARE_HPP
