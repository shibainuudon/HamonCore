/**
 *	@file	scoped_allocator_base.hpp
 *
 *	@brief	scoped_allocator_base の定義
 */

#ifndef HAMON_SCOPED_ALLOCATOR_DETAIL_SCOPED_ALLOCATOR_BASE_HPP
#define HAMON_SCOPED_ALLOCATOR_DETAIL_SCOPED_ALLOCATOR_BASE_HPP

#include <hamon/scoped_allocator/scoped_allocator_adaptor_fwd.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename OuterAlloc, typename... InnerAllocs>
class scoped_allocator_base : public OuterAlloc
{
protected:
	using outer_allocator_type = OuterAlloc;
	using inner_allocator_type = hamon::scoped_allocator_adaptor<InnerAllocs...>;	// [allocator.adaptor.types]/1

private:
	inner_allocator_type	inner;

protected:
	HAMON_CXX11_CONSTEXPR
	scoped_allocator_base() HAMON_NOEXCEPT {}

	template <typename OuterA2>
	HAMON_CXX11_CONSTEXPR
	scoped_allocator_base(OuterA2&& outerAlloc, InnerAllocs const&... innerAllocs) HAMON_NOEXCEPT
		: OuterAlloc(hamon::forward<OuterA2>(outerAlloc))
		, inner(innerAllocs...)
	{}

	HAMON_CXX14_CONSTEXPR inner_allocator_type& inner_allocator() HAMON_NOEXCEPT
	{
		// [allocator.adaptor.members]/2
		return inner;
	}

	HAMON_CXX11_CONSTEXPR inner_allocator_type const& inner_allocator() const HAMON_NOEXCEPT
	{
		// [allocator.adaptor.members]/2
		return inner;
	}

	HAMON_CXX14_CONSTEXPR outer_allocator_type& outer_allocator() HAMON_NOEXCEPT
	{
		// [allocator.adaptor.members]/3
		return static_cast<outer_allocator_type&>(*this);
	}

	HAMON_CXX11_CONSTEXPR outer_allocator_type const& outer_allocator() const HAMON_NOEXCEPT
	{
		// [allocator.adaptor.members]/4
		return static_cast<outer_allocator_type const&>(*this);
	}

	HAMON_CXX11_CONSTEXPR hamon::scoped_allocator_adaptor<OuterAlloc, InnerAllocs...>
	select_on_container_copy_construction() const HAMON_NOEXCEPT
	{
		// [allocator.adaptor.members]/11
		return hamon::scoped_allocator_adaptor<OuterAlloc, InnerAllocs...>(
			hamon::allocator_traits<outer_allocator_type>::select_on_container_copy_construction(outer_allocator()),
			hamon::allocator_traits<inner_allocator_type>::select_on_container_copy_construction(inner_allocator()));
	}
};

template <typename OuterAlloc>
class scoped_allocator_base<OuterAlloc> : public OuterAlloc
{
protected:
	using outer_allocator_type = OuterAlloc;
	using inner_allocator_type = hamon::scoped_allocator_adaptor<OuterAlloc>;	// [allocator.adaptor.types]/1

	HAMON_CXX11_CONSTEXPR
	scoped_allocator_base() HAMON_NOEXCEPT {}

	template <typename OuterA2>
	HAMON_CXX11_CONSTEXPR
	scoped_allocator_base(OuterA2&& outerAlloc) HAMON_NOEXCEPT
		: OuterAlloc(hamon::forward<OuterA2>(outerAlloc))
	{}

	HAMON_CXX14_CONSTEXPR inner_allocator_type& inner_allocator() HAMON_NOEXCEPT
	{
		// [allocator.adaptor.members]/2
		return static_cast<inner_allocator_type&>(*this);
	}

	HAMON_CXX11_CONSTEXPR inner_allocator_type const& inner_allocator() const HAMON_NOEXCEPT
	{
		// [allocator.adaptor.members]/2
		return static_cast<inner_allocator_type const&>(*this);
	}

	HAMON_CXX14_CONSTEXPR outer_allocator_type& outer_allocator() HAMON_NOEXCEPT
	{
		// [allocator.adaptor.members]/3
		return static_cast<outer_allocator_type&>(*this);
	}

	HAMON_CXX11_CONSTEXPR outer_allocator_type const& outer_allocator() const HAMON_NOEXCEPT
	{
		// [allocator.adaptor.members]/4
		return static_cast<outer_allocator_type const&>(*this);
	}

	HAMON_CXX11_CONSTEXPR hamon::scoped_allocator_adaptor<OuterAlloc>
	select_on_container_copy_construction() const HAMON_NOEXCEPT
	{
		// [allocator.adaptor.members]/11
		return hamon::scoped_allocator_adaptor<OuterAlloc>(
			hamon::allocator_traits<outer_allocator_type>::select_on_container_copy_construction(outer_allocator()));
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_SCOPED_ALLOCATOR_DETAIL_SCOPED_ALLOCATOR_BASE_HPP
