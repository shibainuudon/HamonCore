﻿/**
 *	@file	transform.hpp
 *
 *	@brief	ranges::transform の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_TRANSFORM_HPP
#define HAMON_ALGORITHM_RANGES_TRANSFORM_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::transform;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_out_result.hpp>
#include <hamon/algorithm/ranges/in_in_out_result.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/iterator/concepts/indirectly_writable.hpp>
#include <hamon/iterator/indirect_result_t.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/preprocessor/punctuation/comma.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

template <typename Iter, typename Out>
using unary_transform_result = in_out_result<Iter, Out>;

template <typename Iter1, typename Iter2, typename Out>
using binary_transform_result = in_in_out_result<Iter1, Iter2, Out>;

struct transform_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out),
		HAMON_CONSTRAINED_PARAM(hamon::copy_constructible, F),
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Iter first1, Sent last1, Out result, F op, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		unary_transform_result<Iter HAMON_PP_COMMA() Out>,
		hamon::indirectly_writable<Out,
			hamon::indirect_result_t<F&,
				hamon::projected<Iter, Proj>>>)
	{
		for (; first1 != last1; ++first1, (void)++result)
		{
			*result = hamon::invoke(op, hamon::invoke(proj, *first1));
		}

		return { hamon::move(first1), hamon::move(result) };
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out),
		HAMON_CONSTRAINED_PARAM(hamon::copy_constructible, F),
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, Out result, F op, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		unary_transform_result<
			ranges::borrowed_iterator_t<Range> HAMON_PP_COMMA() Out>,
		hamon::indirectly_writable<Out,
			hamon::indirect_result_t<F&,
				hamon::projected<ranges::iterator_t<Range>, Proj>>>)
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			hamon::move(result),
			hamon::move(op),
			hamon::move(proj));
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter1),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter1, Sent1),
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter2),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter2, Sent2),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out),
		HAMON_CONSTRAINED_PARAM(hamon::copy_constructible, F),
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Out result, F binary_op,
		Proj1 proj1 = {}, Proj2 proj2 = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		binary_transform_result<Iter1 HAMON_PP_COMMA() Iter2 HAMON_PP_COMMA() Out>,
		hamon::indirectly_writable<Out,
			hamon::indirect_result_t<F&,
				hamon::projected<Iter1, Proj1>,
				hamon::projected<Iter2, Proj2>>>)
	{
		for (; first1 != last1 && first2 != last2;
			++first1, (void)++first2, ++result)
		{
			*result = hamon::invoke(binary_op,
				hamon::invoke(proj1, *first1),
				hamon::invoke(proj2, *first2));
		}

		return { hamon::move(first1), hamon::move(first2), hamon::move(result) };
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range1),
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range2),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out),
		HAMON_CONSTRAINED_PARAM(hamon::copy_constructible, F),
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Range1&& r1, Range2&& r2, Out result, F binary_op,
		Proj1 proj1 = {}, Proj2 proj2 = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		binary_transform_result<
			ranges::borrowed_iterator_t<Range1> HAMON_PP_COMMA()
			ranges::borrowed_iterator_t<Range2> HAMON_PP_COMMA()
			Out>,
		hamon::indirectly_writable<Out,
			hamon::indirect_result_t<F&,
				hamon::projected<ranges::iterator_t<Range1>, Proj1>,
				hamon::projected<ranges::iterator_t<Range2>, Proj2>>>)
	{
		return (*this)(
			ranges::begin(r1), ranges::end(r1),
			ranges::begin(r2), ranges::end(r2),
			hamon::move(result), hamon::move(binary_op),
			hamon::move(proj1), hamon::move(proj2));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR transform_fn transform{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_TRANSFORM_HPP
