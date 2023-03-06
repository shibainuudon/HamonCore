/**
 *	@file	range.hpp
 *
 *	@brief	range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_RANGE_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon
{
namespace ranges
{

using std::ranges::range;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <utility>

namespace hamon
{
namespace ranges
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept range =
	requires(T& t)
	{
		ranges::begin(t);
		ranges::end(t);
	};

#else

namespace detail
{

template <typename T>
struct range_impl
{
private:
	template <typename U,
		typename = decltype(ranges::begin(std::declval<U&>())),
		typename = decltype(ranges::end(std::declval<U&>()))
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using range = typename ranges::detail::range_impl<T>::type;

#endif

}	// namespace ranges
}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{
namespace ranges
{

template <typename T>
using range_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::ranges::range<T>>;
#else
	hamon::ranges::range<T>;
#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_RANGE_HPP
