/**
 *	@file	sentinel_size.hpp
 *
 *	@brief	sentinel_size の定義
 */

#ifndef HAMON_RANGES_DETAIL_SENTINEL_SIZE_HPP
#define HAMON_RANGES_DETAIL_SENTINEL_SIZE_HPP

#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept sentinel_size =
	requires(T&& t)
	{
		{ ranges::begin(std::forward<T>(t)) }
			-> hamon::forward_iterator;

		{ ranges::end(std::forward<T>(t)) }
			-> hamon::sized_sentinel_for<decltype(ranges::begin(std::forward<T>(t)))>;
	};

#else

template <typename T>
struct sentinel_size_impl
{
private:
	template <typename U,
		typename B = decltype(ranges::begin(std::declval<U&&>())),
		typename E = decltype(ranges::end(std::declval<U&&>()))
	>
	static auto test(int) -> hamon::conjunction<
		hamon::forward_iterator<B>,
		hamon::sized_sentinel_for<E, B>
	>;

	template <typename U>
	static auto test(...) -> std::false_type;

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
