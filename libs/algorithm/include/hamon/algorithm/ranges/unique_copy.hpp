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
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
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
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#define HAMON_RETURN_TYPE_REQUIRES_CLAUSES(T, ...)	\
	-> T requires __VA_ARGS__
#else
#define HAMON_RETURN_TYPE_REQUIRES_CLAUSES(T, ...)	\
	-> hamon::enable_if_t<__VA_ARGS__::value, T>
#endif

template <typename Iter, typename Out>
using unique_copy_result = in_out_result<Iter, Out>;

namespace detail
{

template <typename Iter, typename Out>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
concept unique_copyable =
	hamon::indirectly_copyable<Iter, Out> &&
	(hamon::forward_iterator<Iter> ||
		(hamon::input_iterator<Out> &&
		hamon::same_as<hamon::iter_value_t<Iter>, hamon::iter_value_t<Out>>) ||
		hamon::indirectly_copyable_storable<Iter, Out>);
#else
using unique_copyable = hamon::conjunction<
	hamon::indirectly_copyable<Iter, Out>,
	hamon::disjunction<
		hamon::forward_iterator<Iter>,
		hamon::conjunction<
			hamon::input_iterator<Out>,
			hamon::same_as<
				hamon::iter_value_t<Iter>,
				hamon::iter_value_t<Out>
			>
		>,
		hamon::indirectly_copyable_storable<Iter, Out>
	>
>;
#endif
}	// namespace detail

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

		return { next_it, std::move(++result) };
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

		return { std::move(first), std::move(++result) };
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

		return { std::move(first), std::move(++result) };
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
	HAMON_CXX14_CONSTEXPR auto
	operator()(Iter first, Sent last, Out result,
		Comp comp = {}, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		unique_copy_result<Iter HAMON_PP_COMMA() Out>,
		detail::unique_copyable<Iter, Out>)
	{
		if (first == last)
		{
			return { std::move(first), std::move(result) };
		}

		return impl(
			std::move(first),
			std::move(last),
			std::move(result),
			std::move(comp),
			std::move(proj),
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
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, Out result, Comp comp = {}, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		unique_copy_result<ranges::borrowed_iterator_t<Range> HAMON_PP_COMMA() Out>,
		detail::unique_copyable<ranges::iterator_t<Range>, Out>)
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(result),
			std::move(comp),
			std::move(proj));
	}
};

#undef HAMON_RETURN_TYPE_REQUIRES_CLAUSES

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR unique_copy_fn unique_copy{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_UNIQUE_COPY_HPP
