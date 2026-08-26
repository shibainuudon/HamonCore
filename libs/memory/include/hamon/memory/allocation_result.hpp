/**
 *	@file	allocation_result.hpp
 *
 *	@brief	allocation_result の定義
 */

#ifndef HAMON_MEMORY_ALLOCATION_RESULT_HPP
#define HAMON_MEMORY_ALLOCATION_RESULT_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename Pointer, typename SizeType = hamon::size_t>
struct allocation_result
{
	Pointer ptr;
	SizeType count;

#if defined(HAMON_APPLE_CLANG) && (HAMON_CXX_STANDARD >= 23)
	constexpr operator std::allocation_result<Pointer>() noexcept
	{
		return {ptr, count};
	}
#endif
};

}	// namespace hamon

#endif // HAMON_MEMORY_ALLOCATION_RESULT_HPP
