/**
 *	@file	sentinel_size.hpp
 *
 *	@brief	sentinel_size の定義
 */

#ifndef HAMON_RANGES_DETAIL_SENTINEL_SIZE_HPP
#define HAMON_RANGES_DETAIL_SENTINEL_SIZE_HPP

#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/detail/to_unsigned_like.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// [range.prim.size]/2.5

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept sentinel_size =
	requires(T&& t)
	{
		{ ranges::begin(t) } -> hamon::forward_iterator;
		{ ranges::end(t) } -> hamon::sized_sentinel_for<decltype(ranges::begin(t))>;
		detail::to_unsigned_like(ranges::end(t) - ranges::begin(t));
	};

#else

template <typename T>
struct sentinel_size_impl
{
private:
	template <typename U,
		typename I = decltype(ranges::begin(hamon::declval<U&>())),
		typename S = decltype(ranges::end(hamon::declval<U&>())),
		typename = decltype(detail::to_unsigned_like(hamon::declval<S>() - hamon::declval<I>())),
		typename = hamon::enable_if_t<
			hamon::forward_iterator<I> &&
			hamon::sized_sentinel_for<S, I>
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using sentinel_size = typename sentinel_size_impl<T>::type;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_SENTINEL_SIZE_HPP
