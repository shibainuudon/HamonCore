/**
 *	@file	search_n.hpp
 *
 *	@brief	ranges::search_n の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_SEARCH_N_HPP
#define HAMON_ALGORITHM_RANGES_SEARCH_N_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::search_n;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/find_if.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirectly_comparable.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_subrange_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

struct search_n_fn
{
private:
	template <typename T, typename Pred>
	struct value_comp_t
	{
		T    const& m_value;
		Pred const& m_pred;

		template <typename R>
		HAMON_CXX14_CONSTEXPR auto operator()(R&& arg) const
		->decltype(hamon::invoke(m_pred, std::forward<R>(arg), m_value))
		{
			return hamon::invoke(m_pred, std::forward<R>(arg), m_value);
		}
	};

	template <
		typename Iter,
		HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, Iter, Sent),
		typename Difference,
		typename ValueComp,
		typename Proj>
	static HAMON_CXX14_CONSTEXPR ranges::subrange<Iter>
	impl(Iter first, Sent last, Difference n,
		ValueComp const& value_comp, Proj proj,
		hamon::detail::overload_priority<1>)
	{
		auto tail_size = last - first;
		auto remainder = n;

		while (remainder <= tail_size)
		{
			auto f = first + remainder;
			auto r = remainder;
			while (value_comp(hamon::invoke(proj, *--f)))
			{
				if (--r == 0)
				{
					return { f, f + n };
				}
			}
			first += r;
			tail_size -= r;
		}

		auto i = first + tail_size;
		return { i, i };
	}

	template <
		typename Iter,
		typename Sent,
		typename Difference,
		typename ValueComp,
		typename Proj>
	static HAMON_CXX14_CONSTEXPR ranges::subrange<Iter>
	impl(Iter first, Sent last, Difference n,
		ValueComp const& value_comp, Proj proj,
		hamon::detail::overload_priority<0>)
	{
		first = ranges::find_if(first, last, value_comp, proj);
		while (first != last)
		{
			auto m = n;
			auto i = first;
			++i;
			while (i != last && m != 1 &&
				value_comp(hamon::invoke(proj, *i)))
			{
				++i;
				--m;
			}

			if (m == 1)
			{
				return { first, i };
			}

			if (i == last)
			{
				return { i, i };
			}

			first = ranges::find_if(++i, last, value_comp, proj);
		}

		return { first, first };
	}

public:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::forward_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename T,
		typename Pred = ranges::equal_to,
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Iter first, Sent last, hamon::iter_difference_t<Iter> n,
		T const& value, Pred pred = {}, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::subrange<Iter>,
		hamon::indirectly_comparable<Iter, T const*, Pred, Proj>)
	{
		if (n <= 0)
		{
			return { first, first };
		}

		value_comp_t<T, Pred> value_comp { value, pred };

		if (n == 1)
		{
			first = ranges::find_if(
				std::move(first),
				last,
				std::move(value_comp),
				std::move(proj));

			if (first == last)
			{
				return { first, first };
			}
			else
			{
				auto e = first;
				return { first, ++e };
			}
		}

		return impl(
			std::move(first),
			std::move(last),
			std::move(n),
			value_comp,
			std::move(proj),
			hamon::detail::overload_priority<1>{});
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::forward_range, Range),
		typename T,
		typename Pred = ranges::equal_to,
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Range&& r, ranges::range_difference_t<Range> n,
		T const& value, Pred pred = {}, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::borrowed_subrange_t<Range>,
		hamon::indirectly_comparable<
			ranges::iterator_t<Range>, T const*, Pred, Proj>)
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(n),
			value,
			std::move(pred),
			std::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR search_n_fn search_n{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_SEARCH_N_HPP
