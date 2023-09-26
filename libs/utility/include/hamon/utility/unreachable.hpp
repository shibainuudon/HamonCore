/**
 *	@file	unreachable.hpp
 *
 *	@brief	unreachable を定義
 */

#ifndef HAMON_UTILITY_UNREACHABLE_HPP
#define HAMON_UTILITY_UNREACHABLE_HPP

#include <utility>

#if defined(__cpp_lib_unreachable) && (__cpp_lib_unreachable >= 202202L)

namespace hamon
{

using std::unreachable;

}	// namespace hamon

#else

#include <hamon/cstdlib/abort.hpp>
#include <hamon/config.hpp>

namespace hamon
{

HAMON_NORETURN inline void unreachable() HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_unreachable)
	__builtin_unreachable();
#elif defined(HAMON_MSVC)
	__assume(false);
#endif

	hamon::abort();
}

}	// namespace hamon

#endif

#endif // HAMON_UTILITY_UNREACHABLE_HPP
