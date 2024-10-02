/**
 *	@file	remove.hpp
 *
 *	@brief	ranges::remove の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_REMOVE_HPP
#define HAMON_ALGORITHM_RANGES_REMOVE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

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
#include <hamon/concepts/detail/and.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/iterator/concepts/permutable.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_binary_predicate.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/iterator/projected_value_t.hpp>
#include <hamon/preprocessor/punctuation/comma.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_subrange_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

// 27.7.8 Remove[alg.remove]

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
			return hamon::forward<U>(arg) == m_value;
		}
	};

public:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::permutable, I),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, I, S),
		typename Proj = hamon::identity,
		typename T = hamon::projected_value_t<I, Proj>
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		I first, S last, T const& value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::subrange<I>,
		hamon::indirect_binary_predicate<
			ranges::equal_to,
			hamon::projected<I, Proj>,
			T const*>)
	{
		auto pred = Pred<T>{value};
		return ranges::remove_if(
			first, last,
			hamon::move(pred),
			hamon::move(proj));
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::forward_range, R),
		typename Proj = hamon::identity,
		typename T = hamon::projected_value_t<ranges::iterator_t<R>, Proj>
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(R&& r, T const& value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::borrowed_subrange_t<R>,
		HAMON_CONCEPTS_AND(
			hamon::permutable<ranges::iterator_t<R>>,
			hamon::indirect_binary_predicate<
				ranges::equal_to HAMON_PP_COMMA()
				hamon::projected<ranges::iterator_t<R> HAMON_PP_COMMA() Proj> HAMON_PP_COMMA()
				T const*>))
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			value, hamon::move(proj));
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
