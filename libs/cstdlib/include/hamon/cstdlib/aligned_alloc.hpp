/**
 *	@file	aligned_alloc.hpp
 *
 *	@brief	aligned_alloc の定義
 */

#ifndef HAMON_CSTDLIB_ALIGNED_ALLOC_HPP
#define HAMON_CSTDLIB_ALIGNED_ALLOC_HPP

#include <hamon/bit/has_single_bit.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>
#include <cstdlib>

namespace hamon
{

// MSVCでは aligned_alloc 関数がサポートされません。
// https://learn.microsoft.com/en-us/cpp/standard-library/cstdlib?view=msvc-170#remarks-6
// 代わりに _aligned_malloc 関数を使う必要があり、
// 解放するときには free ではなく _aligned_free を使わなければなりません。
//
// 全てのプラットフォームをサポートするため、
// hamon::aligned_alloc で確保した領域は、hamon::aligned_free で解放する必要があります。

inline void* aligned_alloc(hamon::size_t alignment, hamon::size_t size)
{
	HAMON_ASSERT(hamon::has_single_bit(alignment));
	HAMON_ASSERT(size != 0u);
#if defined(HAMON_STDLIB_DINKUMWARE)
	// alignment should be a power of 2
	// size should not be zero
	return ::_aligned_malloc(size, alignment);
#else
	// size should be an integral multiple of alignment
	hamon::size_t rounded_size = (size + alignment - 1) & ~(alignment - 1);
	return ::aligned_alloc(alignment, rounded_size);
#endif
}

inline void aligned_free(void* ptr)
{
#if defined(HAMON_STDLIB_DINKUMWARE)
	::_aligned_free(ptr);
#else
	::free(ptr);
#endif
}

}	// namespace hamon

#endif // HAMON_CSTDLIB_ALIGNED_ALLOC_HPP
