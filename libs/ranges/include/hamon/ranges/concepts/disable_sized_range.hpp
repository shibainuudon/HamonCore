/**
 *	@file	disable_sized_range.hpp
 *
 *	@brief	disable_sized_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_DISABLE_SIZED_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_DISABLE_SIZED_RANGE_HPP

#include <hamon/ranges/config.hpp>

namespace hamon
{
namespace ranges
{

#if defined(HAMON_USE_STD_RANGES)

using std::ranges::disable_sized_range;

#elif defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool disable_sized_range = false;

#else

template <typename T>
struct disable_sized_range
{
	HAMON_STATIC_CONSTEXPR bool value = false;
};

#endif

}	// namespace ranges
}	// namespace hamon

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_RANGES_DISABLE_SIZED_RANGE(...)	\
	::hamon::ranges::disable_sized_range<__VA_ARGS__>

#define HAMON_RANGES_SPECIALIZE_DISABLE_SIZED_RANGE(Value, ...)		\
	HAMON_INLINE_VAR HAMON_CONSTEXPR								\
	bool disable_sized_range<__VA_ARGS__> = Value

#else

#define HAMON_RANGES_DISABLE_SIZED_RANGE(...)	\
	::hamon::ranges::disable_sized_range<__VA_ARGS__>::value

#define HAMON_RANGES_SPECIALIZE_DISABLE_SIZED_RANGE(Value, ...)		\
	struct disable_sized_range<__VA_ARGS__>							\
	{	                                                            \
		HAMON_STATIC_CONSTEXPR bool value = Value;	                \
	}

#endif

#endif // HAMON_RANGES_CONCEPTS_DISABLE_SIZED_RANGE_HPP
