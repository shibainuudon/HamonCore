/**
 *	@file	enable_borrowed_range.hpp
 *
 *	@brief	enable_borrowed_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_ENABLE_BORROWED_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_ENABLE_BORROWED_RANGE_HPP

#include <hamon/ranges/config.hpp>

namespace hamon
{
namespace ranges
{

#if defined(HAMON_USE_STD_RANGES)

using std::ranges::enable_borrowed_range;

#elif defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool enable_borrowed_range = false;

#else

template <typename T>
struct enable_borrowed_range
{
	HAMON_STATIC_CONSTEXPR bool value = false;
};

#endif

}	// namespace ranges
}	// namespace hamon

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_RANGES_ENABLE_BORROWED_RANGE(...)	\
	::hamon::ranges::enable_borrowed_range<__VA_ARGS__>

#define HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(Value, ...)	\
	HAMON_INLINE_VAR HAMON_CONSTEXPR								\
	bool enable_borrowed_range<__VA_ARGS__> = Value

#else

#define HAMON_RANGES_ENABLE_BORROWED_RANGE(...)	\
	::hamon::ranges::enable_borrowed_range<__VA_ARGS__>::value

#define HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(Value, ...)	\
	struct enable_borrowed_range<__VA_ARGS__>	                    \
	{	                                                            \
		HAMON_STATIC_CONSTEXPR bool value = Value;	                \
	}

#endif

#endif // HAMON_RANGES_CONCEPTS_ENABLE_BORROWED_RANGE_HPP
