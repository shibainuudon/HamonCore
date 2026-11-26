/**
 *	@file	assert.hpp
 *
 *	@brief	HAMON_ASSERT の定義
 */

#ifndef HAMON_DETAIL_ASSERT_HPP
#define HAMON_DETAIL_ASSERT_HPP

#include <hamon/config.hpp>
#include <cstdio>	// puts
#include <cstdlib>	// abort

namespace hamon
{
namespace detail
{

inline void
assertion_hander(char const* str)
{
	std::puts(str);
	std::abort();
}

}	// namespace detail
}	// namespace hamon

#if defined(NDEBUG)

#define HAMON_ASSERT(...)    ((void)0)

#else

#define HAMON_ASSERT(...)                                                   \
	(static_cast<bool>(__VA_ARGS__) ? (void)0 :                            \
		hamon::detail::assertion_hander(                                    \
			__FILE__ "(" HAMON_STRINGIZE(__LINE__) "): Assertion failed:\n" \
			HAMON_STRINGIZE(__VA_ARGS__) "\n"))

#endif

#endif // HAMON_DETAIL_ASSERT_HPP
