/**
 *	@file	replace.hpp
 *
 *	@brief	ranges::replace の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_REPLACE_HPP
#define HAMON_ALGORITHM_RANGES_REPLACE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::replace;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirectly_writable.hpp>
#include <hamon/iterator/concepts/indirect_binary_predicate.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

struct replace_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename T1,
		typename T2,
		typename Proj = hamon::identity
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<hamon::conjunction<
			hamon::indirectly_writable<Iter, T2 const&>,
			hamon::indirect_binary_predicate<
				ranges::equal_to, hamon::projected<Iter, Proj>, T1 const*>
		>::value>
	>
#else
	>
	requires
		hamon::indirectly_writable<Iter, T2 const&> &&
		hamon::indirect_binary_predicate<
			ranges::equal_to, hamon::projected<Iter, Proj>, T1 const*>
#endif
	HAMON_CXX14_CONSTEXPR Iter
	operator()(
		Iter first, Sent last,
		T1 const& old_value,
		T2 const& new_value,
		Proj proj = {}) const
	{
		for (; first != last; ++first)
		{
			if (hamon::invoke(proj, *first) == old_value)
			{
				*first = new_value;
			}
		}

		return first;
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range),
		typename T1,
		typename T2,
		typename Proj = hamon::identity
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<hamon::conjunction<
			hamon::indirectly_writable<ranges::iterator_t<Range>, T2 const&>,
			hamon::indirect_binary_predicate<
				ranges::equal_to,
				hamon::projected<ranges::iterator_t<Range>, Proj>,
				T1 const*>
		>::value>
	>
#else
	>
	requires
		hamon::indirectly_writable<ranges::iterator_t<Range>, T2 const&> &&
		hamon::indirect_binary_predicate<
			ranges::equal_to,
			hamon::projected<ranges::iterator_t<Range>, Proj>,
			T1 const*>
#endif
	HAMON_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(
		Range&& r,
		T1 const& old_value,
		T2 const& new_value,
		Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			old_value, new_value, std::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR replace_fn replace{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_REPLACE_HPP
