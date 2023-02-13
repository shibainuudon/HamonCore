/**
 *	@file	for_each_n.hpp
 *
 *	@brief	ranges::for_each_n の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FOR_EACH_N_HPP
#define HAMON_ALGORITHM_RANGES_FOR_EACH_N_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::for_each_n;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_fun_result.hpp>
#include <hamon/algorithm/ranges/for_each.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/indirectly_unary_invocable.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

template <typename Iter, typename F>
using for_each_n_result = in_fun_result<Iter, F>;

struct for_each_n_fn
{
private:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, Iter),
		typename Difference,
		typename Proj,
		typename Fun
	>
	static HAMON_CXX14_CONSTEXPR for_each_n_result<Iter, Fun>
	impl(Iter first, Difference n, Fun f, Proj proj, hamon::detail::overload_priority<1>)
	{
		if (n <= 0)
		{
			return { std::move(first), std::move(f) };
		}

		auto last = first + n;
		return ranges::for_each(
			std::move(first), std::move(last),
			std::move(f), std::move(proj));
	}

	template <
		typename Iter,
		typename Difference,
		typename Proj,
		typename Fun
	>
	static HAMON_CXX14_CONSTEXPR for_each_n_result<Iter, Fun>
	impl(Iter first, Difference n, Fun f, Proj proj, hamon::detail::overload_priority<0>)
	{
		while (n-- > 0)
		{
			hamon::invoke(f, hamon::invoke(proj, *first));
			++first;
		}

		return { std::move(first), std::move(f) };
	}

public:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<Iter, Proj>,
		HAMON_CONSTRAINED_PARAM(
			hamon::indirectly_unary_invocable,
			ProjectedIter,
			Fun)
	>
	HAMON_CXX14_CONSTEXPR for_each_n_result<Iter, Fun> operator()(
		Iter first, hamon::iter_difference_t<Iter> n,
		Fun f, Proj proj = {}) const
	{
		return impl(first, n, f, proj, hamon::detail::overload_priority<1>{});
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR for_each_n_fn for_each_n{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_FOR_EACH_N_HPP
