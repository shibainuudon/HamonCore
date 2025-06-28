/**
 *	@file	outermost.hpp
 *
 *	@brief	outermost の定義
 */

#ifndef HAMON_SCOPED_ALLOCATOR_DETAIL_OUTERMOST_HPP
#define HAMON_SCOPED_ALLOCATOR_DETAIL_OUTERMOST_HPP

#include <hamon/memory/allocator_traits.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

// [allocator.adaptor.members]/1

template <typename Alloc, typename = void>
struct outermost_impl
{
	HAMON_CXX11_CONSTEXPR Alloc& operator()(Alloc& x) const HAMON_NOEXCEPT { return x; }
};

template <typename Alloc>
struct outermost_impl<Alloc, hamon::void_t<decltype(hamon::declval<Alloc&>().outer_allocator())>>
{
private:
	using OuterAlloc = decltype(hamon::declval<Alloc&>().outer_allocator());

public:
	HAMON_CXX11_CONSTEXPR auto operator()(Alloc& x) const
	->decltype(outermost_impl<OuterAlloc>{}(x.outer_allocator()))
	{
		return outermost_impl<OuterAlloc>{}(x.outer_allocator());
	}
};

template <typename Alloc>
HAMON_CXX11_CONSTEXPR auto outermost(Alloc& x)
->decltype(outermost_impl<Alloc>{}(x))
{
	return outermost_impl<Alloc>{}(x);
}

template <typename Alloc>
using outermost_alloc_traits =
	hamon::allocator_traits<hamon::remove_reference_t<decltype(hamon::detail::outermost(hamon::declval<Alloc&>()))>>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_SCOPED_ALLOCATOR_DETAIL_OUTERMOST_HPP
