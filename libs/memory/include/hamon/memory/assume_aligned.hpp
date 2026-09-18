/**
 *	@file	assume_aligned.hpp
 *
 *	@brief	assume_aligned の定義
 */

#ifndef HAMON_MEMORY_ASSUME_ALIGNED_HPP
#define HAMON_MEMORY_ASSUME_ALIGNED_HPP

#include <hamon/bit/has_single_bit.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/uintptr_t.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 20.2.5 Pointer alignment[ptr.align]

template <hamon::size_t N, typename T>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T*
assume_aligned(T* ptr) HAMON_NOEXCEPT
{
	// [ptr.align]/5
	static_assert(hamon::has_single_bit(N), "");

	// [ptr.align]/7

	if (hamon::is_constant_evaluated())
	{
		return ptr;
	}

#if HAMON_HAS_BUILTIN(__builtin_assume_aligned)
	return reinterpret_cast<T*>(__builtin_assume_aligned(ptr, N));
#elif defined(HAMON_MSVC)
	if ((reinterpret_cast<hamon::uintptr_t>(ptr) & ((1 << N) - 1)) == 0)
	{
		return ptr;
	}
	else
	{
		__assume(0);
	}
#else
	return ptr;
#endif
}

}	// namespace hamon

#endif // HAMON_MEMORY_ASSUME_ALIGNED_HPP
