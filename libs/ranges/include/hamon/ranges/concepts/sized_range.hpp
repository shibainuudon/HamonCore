/**
 *	@file	sized_range.hpp
 *
 *	@brief	sized_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_SIZED_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_SIZED_RANGE_HPP

#include <hamon/ranges/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES)
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#endif

namespace hamon
{
namespace ranges
{

// [range.sized]/1

#if defined(HAMON_USE_STD_RANGES)

using std::ranges::sized_range;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept sized_range =
	ranges::range<T> &&
	requires(T& t) { ranges::size(t); };

#else

namespace detail
{

template <typename T>
struct sized_range_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<ranges::range<U>::value>,
		typename = decltype(ranges::size(hamon::declval<U&>()))
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using sized_range = typename ranges::detail::sized_range_impl<T>::type;

#endif

template <typename T>
using sized_range_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::ranges::sized_range<T>>;
#else
	hamon::ranges::sized_range<T>;
#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_SIZED_RANGE_HPP
