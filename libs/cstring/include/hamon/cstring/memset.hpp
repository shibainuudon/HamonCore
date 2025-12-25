/**
 *	@file	memset.hpp
 *
 *	@brief	memset 関数を定義
 */

#ifndef HAMON_CSTRING_MEMSET_HPP
#define HAMON_CSTRING_MEMSET_HPP

#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>
#include <cstring>

namespace hamon
{

namespace ct
{

/**
 *	constexpr版のmemset
 *	実行時のパフォーマンスはstd::memsetより劣る可能性がある
 *	is_constant_evaluatedが使える場合は、実行時にはstd::memsetを呼ぶ
 */
inline HAMON_CXX14_CONSTEXPR
char* memset(char* dest, char ch, std::size_t count) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return static_cast<char*>(std::memset(dest, ch, count));
	}
#endif

	for (std::size_t i = 0; i < count; ++i)
	{
		dest[i] = ch;
	}
	return dest;
}

}	// namespace ct

inline void* memset(void* dest, int ch, std::size_t count) HAMON_NOEXCEPT
{
	return std::memset(dest, ch, count);
}

}	// namespace hamon

#endif // HAMON_CSTRING_MEMSET_HPP
