/**
 *	@file	allocator_arg_t.hpp
 *
 *	@brief	allocator_arg_t の定義
 */

#ifndef HAMON_MEMORY_ALLOCATOR_ARG_T_HPP
#define HAMON_MEMORY_ALLOCATOR_ARG_T_HPP

#include <hamon/config.hpp>
#include <memory>

#if HAMON_CXX_STANDARD >= 17

namespace hamon
{

using std::allocator_arg_t;
using std::allocator_arg;

}	// namespace hamon

#else


namespace hamon
{

struct allocator_arg_t
{
	explicit allocator_arg_t() = default;
};

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR allocator_arg_t allocator_arg{};

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_ALLOCATOR_ARG_T_HPP
