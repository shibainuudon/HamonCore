/**
 *	@file	unique_copy.hpp
 *
 *	@brief	ranges::unique_copy の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_UNIQUE_COPY_HPP
#define HAMON_ALGORITHM_RANGES_UNIQUE_COPY_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::unique_copy;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_out_result.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/detail/and.hpp>
#include <hamon/concepts/detail/or.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/iterator/concepts/indirect_equivalence_relation.hpp>
#include <hamon/iterator/concepts/indirectly_copyable.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/indirectly_copyable_storable.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/preprocessor/punctuation/comma.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

template <typename Iter, typename Out>
using unique_copy_result = in_out_result<Iter, Out>;

struct unique_copy_fn
{
private:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::forward_iterator, Iter),
		typename Sent, typename Out, typename Proj, typename Comp
	>
	static HAMON_CXX14_CONSTEXPR unique_copy_result<Iter, Out>
	impl(Iter first, Sent last, Out result, Comp comp, Proj proj,
		hamon::detail::overload_priority<2>)
	{
		auto next_it = first;
		*result = *next_it;
		while (++next_it != last)
		{
			if (!hamon::invoke(comp,
				hamon::invoke(proj, *first),
				hamon::invoke(proj, *next_it)))
			{
				first = next_it;
				*++result = *first;
			}
		}

		return { next_it, hamon::move(++result) };
	}

	template <
		typename Iter, typename Sent,
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Out),
		typename Proj, typename Comp,
		typename = hamon::enable_if_t<
			hamon::same_as_t<
				hamon::iter_value_t<Iter>,
				hamon::iter_value_t<Out>
			>::value
		>
	>
	static HAMON_CXX14_CONSTEXPR unique_copy_result<Iter, Out>
	impl(Iter first, Sent last, Out result, Comp comp, Proj proj,
		hamon::detail::overload_priority<1>)
	{
		*result = *first;
		while (++first != last)
		{
			if (!hamon::invoke(comp,
				hamon::invoke(proj, *result),
				hamon::invoke(proj, *first)))
			{
				*++result = *first;
			}
		}

		return { hamon::move(first), hamon::move(++result) };
	}

	template <
		typename Iter, typename Sent, typename Out,
		typename Proj, typename Comp,
		typename = hamon::enable_if_t<
			hamon::indirectly_copyable_storable_t<Iter, Out>::value
		>
	>
	static HAMON_CXX14_CONSTEXPR unique_copy_result<Iter, Out>
	impl(Iter first, Sent last, Out result, Comp comp, Proj proj,
		hamon::detail::overload_priority<0>)
	{
		auto value = *first;
		*result = value;
		while (++first != last)
		{
			if (!(bool)hamon::invoke(comp,
				hamon::invoke(proj, *first),
				hamon::invoke(proj, value)))
			{
				value = *first;
				*++result = value;
			}
		}

		return { hamon::move(first), hamon::move(++result) };
	}

public:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<Iter, Proj>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_equivalence_relation,
			ProjectedIter,
			Comp,
			ranges::equal_to)
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Iter first, Sent last, Out result,
		Comp comp = {}, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		unique_copy_result<Iter HAMON_PP_COMMA() Out>,
		HAMON_CONCEPTS_AND(
			hamon::indirectly_copyable<Iter HAMON_PP_COMMA() Out>,
			HAMON_CONCEPTS_OR(
				hamon::forward_iterator<Iter>,
			HAMON_CONCEPTS_OR(
				HAMON_CONCEPTS_AND(
					hamon::input_iterator<Out>,
					hamon::same_as<
						hamon::iter_value_t<Iter> HAMON_PP_COMMA()
						hamon::iter_value_t<Out>>),
				hamon::indirectly_copyable_storable<Iter HAMON_PP_COMMA() Out>))))
	{
		if (first == last)
		{
			return { hamon::move(first), hamon::move(result) };
		}

		return impl(
			hamon::move(first),
			hamon::move(last),
			hamon::move(result),
			hamon::move(comp),
			hamon::move(proj),
			hamon::detail::overload_priority<2>{});
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::input_range, Range),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<ranges::iterator_t<Range>, Proj>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_equivalence_relation,
			ProjectedIter,
			Comp,
			ranges::equal_to)
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Range&& r, Out result, Comp comp = {}, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		unique_copy_result<ranges::borrowed_iterator_t<Range> HAMON_PP_COMMA() Out>,
		HAMON_CONCEPTS_AND(
			hamon::indirectly_copyable<ranges::iterator_t<Range> HAMON_PP_COMMA() Out>,
			HAMON_CONCEPTS_OR(
				hamon::forward_iterator<ranges::iterator_t<Range>>,
			HAMON_CONCEPTS_OR(
				HAMON_CONCEPTS_AND(
					hamon::input_iterator<Out>,
					hamon::same_as<
						hamon::iter_value_t<ranges::iterator_t<Range>> HAMON_PP_COMMA()
						hamon::iter_value_t<Out>>),
				hamon::indirectly_copyable_storable<ranges::iterator_t<Range> HAMON_PP_COMMA() Out>))))
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			hamon::move(result),
			hamon::move(comp),
			hamon::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR unique_copy_fn unique_copy{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_UNIQUE_COPY_HPP
