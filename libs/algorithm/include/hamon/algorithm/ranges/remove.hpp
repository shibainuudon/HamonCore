/**
 *	@file	remove.hpp
 *
 *	@brief	ranges::remove の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_REMOVE_HPP
#define HAMON_ALGORITHM_RANGES_REMOVE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::remove;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/remove_if.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/iterator/concepts/permutable.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_binary_predicate.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_subrange_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

struct remove_fn
{
private:
	template <typename T>
	struct Pred
	{
		T const& m_value;

		template <typename U>
		constexpr bool operator()(U&& arg) const
		{
			return std::forward<U>(arg) == m_value;
		}
	};

public:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::permutable, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename T,
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Iter first, Sent last, T const& value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::subrange<Iter>,
		hamon::indirect_binary_predicate<
			ranges::equal_to,
			hamon::projected<Iter, Proj>,
			T const*>)
	{
		auto pred = Pred<T>{value};
		return ranges::remove_if(
			first, last,
			std::move(pred),
			std::move(proj));
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::forward_range, Range),
		typename T,
		typename Proj = hamon::identity,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::permutable, Dummy, ranges::iterator_t<Range>)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, T const& value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::borrowed_subrange_t<Range>,
		hamon::indirect_binary_predicate<
			ranges::equal_to,
			hamon::projected<ranges::iterator_t<Range>, Proj>,
			T const*>)
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			value, std::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR remove_fn remove{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_REMOVE_HPP
