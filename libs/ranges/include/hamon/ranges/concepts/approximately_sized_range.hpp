/**
 *	@file	approximately_sized_range.hpp
 *
 *	@brief	approximately_sized_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_APPROXIMATELY_SIZED_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_APPROXIMATELY_SIZED_RANGE_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES) && \
	defined(__cpp_lib_ranges_reserve_hint) && (__cpp_lib_ranges_reserve_hint >= 202502L)

namespace hamon
{
namespace ranges
{

using std::ranges::approximately_sized_range;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/reserve_hint.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace ranges
{

// 25.4.3 Approximately sized ranges[range.approximately.sized]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL approximately_sized_range =
	ranges::range<T> &&
	requires(T& t) { ranges::reserve_hint(t); };

#else

namespace detail
{

template <typename T>
struct approximately_sized_range_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<ranges::range<U>::value>,
		typename = decltype(ranges::reserve_hint(hamon::declval<U&>()))
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
HAMON_CONCEPT_OR_BOOL approximately_sized_range =
	ranges::detail::approximately_sized_range_impl<T>::type::value;

#endif

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_CONCEPTS_APPROXIMATELY_SIZED_RANGE_HPP
