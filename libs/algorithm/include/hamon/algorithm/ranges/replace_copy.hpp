/**
 *	@file	replace_copy.hpp
 *
 *	@brief	ranges::replace_copy の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_REPLACE_COPY_HPP
#define HAMON_ALGORITHM_RANGES_REPLACE_COPY_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::replace_copy;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_out_result.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/iterator/concepts/indirectly_copyable.hpp>
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

template <typename Iter, typename Out>
using replace_copy_result = in_out_result<Iter, Out>;

struct replace_copy_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename T1,
		typename T2,
		HAMON_CONSTRAINED_PARAM(hamon::output_iterator, T2 const&, Out),
		typename Proj = hamon::identity
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<hamon::conjunction<
			hamon::indirectly_copyable<Iter, Out>,
			hamon::indirect_binary_predicate<
				ranges::equal_to,
				hamon::projected<Iter, Proj>,
				T1 const*>
		>::value>
	>
#else
	>
	requires
		hamon::indirectly_copyable<Iter, Out> &&
		hamon::indirect_binary_predicate<
			ranges::equal_to,
			hamon::projected<Iter, Proj>,
			T1 const*>
#endif
	HAMON_CXX14_CONSTEXPR replace_copy_result<Iter, Out>
	operator()(
		Iter first, Sent last,
		Out result,
		T1 const& old_value,
		T2 const& new_value,
		Proj proj = {}) const
	{
		for (; first != last; ++first, (void)++result)
		{
			if (hamon::invoke(proj, *first) == old_value)
			{
				*result = new_value;
			}
			else
			{
				*result = *first;
			}
		}

		return { std::move(first), std::move(result) };
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range),
		typename T1,
		typename T2,
		HAMON_CONSTRAINED_PARAM(hamon::output_iterator, T2 const&, Out),
		typename Proj = hamon::identity
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<hamon::conjunction<
			hamon::indirectly_copyable<ranges::iterator_t<Range>, Out>,
			hamon::indirect_binary_predicate<
				ranges::equal_to,
				hamon::projected<ranges::iterator_t<Range>, Proj>,
				T1 const*>
		>::value>
	>
#else
	>
	requires
		hamon::indirectly_copyable<ranges::iterator_t<Range>, Out> &&
		hamon::indirect_binary_predicate<
			ranges::equal_to,
			hamon::projected<ranges::iterator_t<Range>, Proj>,
			T1 const*>
#endif
	HAMON_CXX14_CONSTEXPR
	replace_copy_result<ranges::borrowed_iterator_t<Range>, Out>
	operator()(
		Range&& r,
		Out result,
		T1 const& old_value,
		T2 const& new_value,
		Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(result),
			old_value,
			new_value,
			std::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR replace_copy_fn replace_copy{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_REPLACE_COPY_HPP
