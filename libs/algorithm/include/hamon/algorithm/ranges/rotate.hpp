/**
 *	@file	rotate.hpp
 *
 *	@brief	ranges::rotate の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_ROTATE_HPP
#define HAMON_ALGORITHM_RANGES_ROTATE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::rotate;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/swap_ranges.hpp>
#include <hamon/algorithm/ranges/move.hpp>
#include <hamon/algorithm/ranges/reverse.hpp>
#include <hamon/algorithm/ranges/move_backward.hpp>
#include <hamon/concepts/swap.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/permutable.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_subrange_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
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

struct rotate_fn
{
private:
	// if constexpr (hamon::random_access_iterator<Iter>)
	template <HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, Iter)>
	static HAMON_CXX14_CONSTEXPR ranges::subrange<Iter>
	impl(Iter first, Iter middle, Iter lasti,
		hamon::detail::overload_priority<2>)
	{
		auto n = lasti - first;
		auto k = middle - first;

		if (k == n - k)
		{
			ranges::swap_ranges(first, middle, middle, middle + k);
			return { std::move(middle), std::move(lasti) };
		}

		auto p = first;
		auto ret = first + (lasti - middle);

		for (;;)
		{
			if (k < n - k)
			{
				// TODO: is_pod is deprecated, but this condition is
				// consistent with the STL implementation.
				//if constexpr (__is_pod(hamon::iter_value_t<Iter>))
				//{
				//	if (k == 1)
				//	{
				//		auto t = std::move(*p);
				//		ranges::move(p + 1, p + n, p);
				//		*(p + n - 1) = std::move(t);
				//		return { std::move(ret), std::move(lasti) };
				//	}
				//}

				auto q = p + k;
				for (decltype(n) i = 0; i < n - k; ++i)
				{
					ranges::iter_swap(p, q);
					++p;
					++q;
				}

				n %= k;
				if (n == 0)
				{
					return { std::move(ret), std::move(lasti) };
				}

				ranges::swap(n, k);
				k = n - k;
			}
			else
			{
				k = n - k;
				// TODO: is_pod is deprecated, but this condition is
				// consistent with the STL implementation.
				//if constexpr (__is_pod(hamon::iter_value_t<Iter>))
				//{
				//	if (k == 1)
				//	{
				//		auto t = std::move(*(p + n - 1));
				//		ranges::move_backward(p, p + n - 1, p + n);
				//		*p = std::move(t);
				//		return { std::move(ret), std::move(lasti) };
				//	}
				//}

				auto q = p + n;
				p = q - k;
				for (decltype(n) i = 0; i < n - k; ++i)
				{
					--p;
					--q;
					ranges::iter_swap(p, q);
				}

				n %= k;
				if (n == 0)
				{
					return { std::move(ret), std::move(lasti) };
				}

				ranges::swap(n, k);
			}
		}
	}

	// else if constexpr (hamon::bidirectional_iterator<Iter>)
	template <HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, Iter)>
	static HAMON_CXX14_CONSTEXPR ranges::subrange<Iter>
	impl(Iter first, Iter middle, Iter lasti,
		hamon::detail::overload_priority<1>)
	{
		auto tail = lasti;

		ranges::reverse(first, middle);
		ranges::reverse(middle, tail);

		while (first != middle && middle != tail)
		{
			ranges::iter_swap(first, --tail);
			++first;
		}

		if (first == middle)
		{
			ranges::reverse(middle, tail);
			return { std::move(tail), std::move(lasti) };
		}
		else
		{
			ranges::reverse(first, middle);
			return { std::move(first), std::move(lasti) };
		}
	}

	// else
	template <typename Iter>
	static HAMON_CXX14_CONSTEXPR ranges::subrange<Iter>
	impl(Iter first, Iter middle, Iter lasti,
		hamon::detail::overload_priority<0>)
	{
		auto first2 = middle;
		do
		{
			ranges::iter_swap(first, first2);
			++first;
			++first2;
			if (first == middle)
			{
				middle = first2;
			}
		}
		while (first2 != lasti);

		auto ret = first;

		first2 = middle;

		while (first2 != lasti)
		{
			ranges::iter_swap(first, first2);
			++first;
			++first2;
			if (first == middle)
			{
				middle = first2;
			}
			else if (first2 == lasti)
			{
				first2 = middle;
			}
		}

		return { std::move(ret), std::move(lasti) };
	}

public:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::permutable, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent)
	>
	HAMON_CXX14_CONSTEXPR ranges::subrange<Iter>
	operator()(Iter first, Iter middle, Sent last) const
	{
		auto lasti = ranges::next(first, last);
		if (first == middle)
		{
			return { lasti, lasti };
		}

		if (last == middle)
		{
			return { std::move(first), std::move(lasti) };
		}

		return impl(
			std::move(first),
			std::move(middle),
			std::move(lasti),
			hamon::detail::overload_priority<2>{});
	}

	template <HAMON_CONSTRAINED_PARAM(ranges::forward_range, Range)>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, ranges::iterator_t<Range> middle) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::borrowed_subrange_t<Range>,
		hamon::permutable<ranges::iterator_t<Range>>)
	{
		return (*this)(
			ranges::begin(r),
			std::move(middle),
			ranges::end(r));
	}
};

#undef HAMON_RETURN_TYPE_REQUIRES_CLAUSES

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR rotate_fn rotate{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_ROTATE_HPP
