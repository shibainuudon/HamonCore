/**
 *	@file	allocation_result.hpp
 *
 *	@brief	allocation_result の定義
 */

#ifndef HAMON_MEMORY_ALLOCATION_RESULT_HPP
#define HAMON_MEMORY_ALLOCATION_RESULT_HPP

#include <memory>

#if defined(__cpp_lib_allocate_at_least) && (__cpp_lib_allocate_at_least >= 202302L)

namespace hamon
{

using std::allocation_result;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>

namespace hamon
{

template <typename Pointer, typename SizeType = hamon::size_t>
struct allocation_result
{
	Pointer ptr;
	SizeType count;
};

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_ALLOCATION_RESULT_HPP
