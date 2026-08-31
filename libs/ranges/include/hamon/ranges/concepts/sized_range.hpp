/**
 *	@file	sized_range.hpp
 *
 *	@brief	sized_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_SIZED_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_SIZED_RANGE_HPP

#include <hamon/ranges/concepts/approximately_sized_range.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace ranges
{

// 25.4.4 Sized ranges[range.sized]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL sized_range =
	ranges::approximately_sized_range<T> &&
	requires(T& t) { ranges::size(t); };

#else

namespace detail
{

template <typename T>
struct sized_range_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<ranges::approximately_sized_range<U>>,
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
HAMON_CONCEPT_OR_BOOL sized_range =
	ranges::detail::sized_range_impl<T>::type::value;

#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_SIZED_RANGE_HPP
