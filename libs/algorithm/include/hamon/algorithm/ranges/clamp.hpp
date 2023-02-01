/**
 *	@file	clamp.hpp
 *
 *	@brief	ranges::clamp の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_CLAMP_HPP
#define HAMON_ALGORITHM_RANGES_CLAMP_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::clamp;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/indirect_strict_weak_order.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>

namespace hamon
{

namespace ranges
{

struct clamp_fn
{
	template <
		typename T,
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<T const*, Proj>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_strict_weak_order,
			ProjectedIter,
			Comp,
			ranges::less)
	>
	HAMON_CXX14_CONSTEXPR T const&
	operator()(T const& val, T const& lo, T const& hi,
		Comp comp = {}, Proj proj = {}) const
	{
		HAMON_ASSERT(!(hamon::invoke(comp,
			hamon::invoke(proj, hi),
			hamon::invoke(proj, lo))));

		auto&& proj_val = hamon::invoke(proj, val);

		return
			hamon::invoke(comp, proj_val, hamon::invoke(proj, lo)) ?
				lo :
			hamon::invoke(comp, hamon::invoke(proj, hi), proj_val) ?
				hi :
			val;
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR clamp_fn clamp{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_CLAMP_HPP
