/**
 *	@file	scoped_allocator_adaptor_fwd.hpp
 *
 *	@brief	scoped_allocator_adaptor の前方宣言
 */

#ifndef HAMON_SCOPED_ALLOCATOR_SCOPED_ALLOCATOR_ADAPTOR_FWD_HPP
#define HAMON_SCOPED_ALLOCATOR_SCOPED_ALLOCATOR_ADAPTOR_FWD_HPP

namespace hamon
{

template <typename OuterAlloc, typename... InnerAllocs>
class scoped_allocator_adaptor;

}	// namespace hamon

#endif // HAMON_SCOPED_ALLOCATOR_SCOPED_ALLOCATOR_ADAPTOR_FWD_HPP
