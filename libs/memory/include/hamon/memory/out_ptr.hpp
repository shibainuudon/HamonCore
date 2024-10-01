/**
 *	@file	out_ptr.hpp
 *
 *	@brief	out_ptr の定義
 */

#ifndef HAMON_MEMORY_OUT_PTR_HPP
#define HAMON_MEMORY_OUT_PTR_HPP

#include <hamon/memory/out_ptr_t.hpp>
#include <memory>

//#if defined(__cpp_lib_out_ptr) && (__cpp_lib_out_ptr >= 202311L)	// P2833R2 は Free standing 指定だけ
#if defined(__cpp_lib_out_ptr) && (__cpp_lib_out_ptr >= 202106L)

namespace hamon
{

using std::out_ptr;

}	// namespace hamon

#else

#include <hamon/memory/detail/pointer_of.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/utility/forward.hpp>

namespace hamon
{

// 20.3.4.2 Function template out_ptr[out.ptr]
template <typename Pointer = void, typename Smart, typename... Args,
	// [out.ptr]/1
	typename P = hamon::conditional_t<
		hamon::is_void<Pointer>::value,
		hamon::detail::POINTER_OF<Smart>,
		Pointer>
>
hamon::out_ptr_t<Smart, P, Args&&...>
out_ptr(Smart& s, Args&&... args)
{
	// [out.ptr]/2
	return hamon::out_ptr_t<Smart, P, Args&&...>(s, hamon::forward<Args>(args)...);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_OUT_PTR_HPP
