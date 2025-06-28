/**
 *	@file	scoped_allocator_adaptor_fwd.hpp
 *
 *	@brief	scoped_allocator_adaptor の前方宣言
 */

#ifndef HAMON_SCOPED_ALLOCATOR_SCOPED_ALLOCATOR_ADAPTOR_FWD_HPP
#define HAMON_SCOPED_ALLOCATOR_SCOPED_ALLOCATOR_ADAPTOR_FWD_HPP

#include <hamon/scoped_allocator/config.hpp>

#if defined(HAMON_USE_STD_SCOPED_ALLOCATOR)

#include <scoped_allocator>

namespace hamon
{

using std::scoped_allocator_adaptor;

}	// namespace hamon

#else

namespace hamon
{

template <typename OuterAlloc, typename... InnerAllocs>
class scoped_allocator_adaptor;

}	// namespace hamon

#endif

#endif // HAMON_SCOPED_ALLOCATOR_SCOPED_ALLOCATOR_ADAPTOR_FWD_HPP
