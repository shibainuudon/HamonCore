/**
 *	@file	inout_ptr.hpp
 *
 *	@brief	inout_ptr の定義
 */

#ifndef HAMON_MEMORY_INOUT_PTR_HPP
#define HAMON_MEMORY_INOUT_PTR_HPP

#include <hamon/memory/inout_ptr_t.hpp>
#include <hamon/memory/detail/pointer_of.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/utility/forward.hpp>

namespace hamon
{

// 20.3.4.4 Function template inout_ptr[inout.ptr]
template <typename Pointer = void, typename Smart, typename... Args,
	// [inout.ptr]/1
	typename P = hamon::conditional_t<
		hamon::is_void<Pointer>::value,
		hamon::detail::POINTER_OF<Smart>,
		Pointer>
>
hamon::inout_ptr_t<Smart, P, Args&&...>
inout_ptr(Smart& s, Args&&... args)
{
	// [inout.ptr]/2
	return hamon::inout_ptr_t<Smart, P, Args&&...>(s, hamon::forward<Args>(args)...);
}

}	// namespace hamon

#endif // HAMON_MEMORY_INOUT_PTR_HPP
