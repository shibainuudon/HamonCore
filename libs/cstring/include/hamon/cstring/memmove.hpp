/**
 *	@file	memmove.hpp
 *
 *	@brief	memmove 関数を定義
 */

#ifndef HAMON_CSTRING_MEMMOVE_HPP
#define HAMON_CSTRING_MEMMOVE_HPP

#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>
#include <cstring>

namespace hamon
{

namespace ct
{

/**
 *	constexpr版のmemmove
 *	実行時のパフォーマンスはstd::memmoveより劣る可能性がある
 *	is_constant_evaluatedが使える場合は、実行時にはstd::memmoveを呼ぶ
 *
 *	destとsrcが同じ配列の要素を指していない場合constexprにできない。
 *	その場合はmemcpyを使ってください。
 */
template <typename T>
inline HAMON_CXX14_CONSTEXPR
T* memmove(T* dest, T const* src, std::size_t count) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return static_cast<T*>(std::memmove(dest, src, count));
	}
#endif

	HAMON_ASSERT((count % sizeof(T)) == 0u);
	count /= sizeof(T);

	if (dest < src)
	{
		for (std::size_t i = 0; i < count; ++i)
		{
			dest[i] = src[i];
		}
	}
	else
	{
		for (std::size_t i = count; i > 0; --i)
		{
			dest[i - 1] = src[i - 1];
		}
	}
	return dest;
}

}	// namespace ct

inline void* memmove(void* dest, void const* src, std::size_t count) HAMON_NOEXCEPT
{
	return std::memmove(dest, src, count);
}

}	// namespace hamon

#endif // HAMON_CSTRING_MEMMOVE_HPP
