/**
 *	@file	assume_aligned.hpp
 *
 *	@brief	assume_aligned の定義
 */

#ifndef HAMON_MEMORY_ASSUME_ALIGNED_HPP
#define HAMON_MEMORY_ASSUME_ALIGNED_HPP

#include <memory>

#if defined(__cpp_lib_assume_aligned) && (__cpp_lib_assume_aligned >= 201811L)

namespace hamon
{

using std::assume_aligned;

}	// namespace hamon

#else

#include <hamon/bit/has_single_bit.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 20.2.5 Pointer alignment[ptr.align]

template <hamon::size_t N, typename T>
HAMON_NODISCARD constexpr T*
assume_aligned(T* ptr) HAMON_NOEXCEPT
{
	// [ptr.align]/5
	static_assert(hamon::has_single_bit(N), "");

#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (hamon::is_constant_evaluated())
	{
		return ptr;
	}
#endif

	// [ptr.align]/7
	return static_cast<T*>(__builtin_assume_aligned(ptr, N));
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_ASSUME_ALIGNED_HPP
