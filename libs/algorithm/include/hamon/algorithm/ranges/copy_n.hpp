/**
 *	@file	copy_n.hpp
 *
 *	@brief	ranges::copy_n の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_COPY_N_HPP
#define HAMON_ALGORITHM_RANGES_COPY_N_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::copy_n;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_out_result.hpp>
#include <hamon/algorithm/ranges/copy.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/iterator/concepts/indirectly_copyable.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

template <typename Iter, typename Out>
using copy_n_result = in_out_result<Iter, Out>;

struct copy_n_fn
{
private:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, Iter),
		typename Difference, typename Out
	>
	static HAMON_CXX14_CONSTEXPR copy_n_result<Iter, Out>
	impl(Iter first, Difference n, Out result,
		hamon::detail::overload_priority<1>)
	{
		if (n > 0)
		{
			return ranges::copy(first, first + n, std::move(result));
		}

		return { std::move(first), std::move(result) };
	}

	template <typename Iter, typename Difference, typename Out>
	static HAMON_CXX14_CONSTEXPR copy_n_result<Iter, Out>
	impl(Iter first, Difference n, Out result,
		hamon::detail::overload_priority<0>)
	{
		for (; n > 0; --n, (void)++result, (void)++first)
		{
			*result = *first;
		}

		return { std::move(first), std::move(result) };
	}

public:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out)
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<
			hamon::indirectly_copyable<Iter, Out>::value
		>
	>
#else
	>
	requires hamon::indirectly_copyable<Iter, Out>
#endif
	HAMON_CXX14_CONSTEXPR copy_n_result<Iter, Out>
	operator()(Iter first, hamon::iter_difference_t<Iter> n, Out result) const
	{
		return impl(
			std::move(first),
			std::move(n),
			std::move(result),
			hamon::detail::overload_priority<1>{});
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR copy_n_fn copy_n{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_COPY_N_HPP
