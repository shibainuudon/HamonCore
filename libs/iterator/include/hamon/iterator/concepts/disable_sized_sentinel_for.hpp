/**
 *	@file	disable_sized_sentinel_for.hpp
 *
 *	@brief	disable_sized_sentinel_for の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DISABLE_SIZED_SENTINEL_FOR_HPP
#define HAMON_ITERATOR_CONCEPTS_DISABLE_SIZED_SENTINEL_FOR_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

#define HAMON_DISABLE_SIZED_SENTINEL_FOR_NAMESPACE std

using std::disable_sized_sentinel_for;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

#define HAMON_DISABLE_SIZED_SENTINEL_FOR_NAMESPACE hamon

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename Sent, typename Iter>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool disable_sized_sentinel_for = false;

#else

template <typename Sent, typename Iter>
struct disable_sized_sentinel_for
{
	HAMON_STATIC_CONSTEXPR bool value = false;
};

#endif

}	// namespace hamon

#endif

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_DISABLE_SIZED_SENTINEL_FOR(...)	\
	::hamon::disable_sized_sentinel_for<__VA_ARGS__>

#define HAMON_SPECIALIZE_DISABLE_SIZED_SENTINEL_FOR(Value, ...)	\
	HAMON_INLINE_VAR HAMON_CONSTEXPR							\
	bool disable_sized_sentinel_for<__VA_ARGS__> = Value

#else

#define HAMON_DISABLE_SIZED_SENTINEL_FOR(...)	\
	::hamon::disable_sized_sentinel_for<__VA_ARGS__>::value

#define HAMON_SPECIALIZE_DISABLE_SIZED_SENTINEL_FOR(Value, ...)	\
	struct disable_sized_sentinel_for<__VA_ARGS__>	    \
	{	                                                \
		HAMON_STATIC_CONSTEXPR bool value = Value;	    \
	}

#endif

#endif // HAMON_ITERATOR_CONCEPTS_DISABLE_SIZED_SENTINEL_FOR_HPP
