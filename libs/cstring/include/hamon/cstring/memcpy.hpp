/**
 *	@file	memcpy.hpp
 *
 *	@brief	memcpy 関数を定義
 */

#ifndef HAMON_CSTRING_MEMCPY_HPP
#define HAMON_CSTRING_MEMCPY_HPP

#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>
#include <cstring>

namespace hamon
{

namespace ct
{

/**
 *	constexpr版のmemcpy
 *	実行時のパフォーマンスはstd::memcpyより劣る可能性がある
 *	is_constant_evaluatedが使える場合は、実行時にはstd::memcpyを呼ぶ
 */
template <typename T>
inline HAMON_CXX14_CONSTEXPR
T* memcpy(T* dest, T const* src, std::size_t count) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return static_cast<T*>(std::memcpy(dest, src, count));
	}
#endif

	HAMON_ASSERT((count % sizeof(T)) == 0u);
	count /= sizeof(T);
	for (std::size_t i = 0; i < count; ++i)
	{
		dest[i] = src[i];
	}
	return dest;
}

}	// namespace ct

inline void* memcpy(void* dest, void const* src, std::size_t count) HAMON_NOEXCEPT
{
	return std::memcpy(dest, src, count);
}

}	// namespace hamon

#endif // HAMON_CSTRING_MEMCPY_HPP
