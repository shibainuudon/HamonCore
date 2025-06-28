/**
 *	@file	scoped_allocator_adaptor.hpp
 *
 *	@brief	scoped_allocator_adaptor の定義
 */

#ifndef HAMON_SCOPED_ALLOCATOR_SCOPED_ALLOCATOR_ADAPTOR_HPP
#define HAMON_SCOPED_ALLOCATOR_SCOPED_ALLOCATOR_ADAPTOR_HPP

#include <hamon/scoped_allocator/config.hpp>

#if defined(HAMON_USE_STD_SCOPED_ALLOCATOR)

#include <scoped_allocator>

namespace hamon
{

using std::scoped_allocator_adaptor;

}	// namespace hamon

#else

#include <hamon/scoped_allocator/scoped_allocator_adaptor_fwd.hpp>
#include <hamon/scoped_allocator/detail/scoped_allocator_base.hpp>
#include <hamon/scoped_allocator/detail/outermost.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/uses_allocator_construction_args.hpp>
#include <hamon/tuple/apply.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename OuterAlloc, typename... InnerAllocs>
class scoped_allocator_adaptor : public hamon::detail::scoped_allocator_base<OuterAlloc, InnerAllocs...>
{
private:
	using Base = hamon::detail::scoped_allocator_base<OuterAlloc, InnerAllocs...>;

	using OuterTraits = hamon::allocator_traits<OuterAlloc>;

public:
	using outer_allocator_type = typename Base::outer_allocator_type;
	using inner_allocator_type = typename Base::inner_allocator_type;	// [allocator.adaptor.types]/1

	using value_type           = typename OuterTraits::value_type;
	using size_type            = typename OuterTraits::size_type;
	using difference_type      = typename OuterTraits::difference_type;
	using pointer              = typename OuterTraits::pointer;
	using const_pointer        = typename OuterTraits::const_pointer;
	using void_pointer         = typename OuterTraits::void_pointer;
	using const_void_pointer   = typename OuterTraits::const_void_pointer;

	// [allocator.adaptor.types]/2
	using propagate_on_container_copy_assignment = hamon::conjunction<
		typename hamon::allocator_traits<OuterAlloc>::propagate_on_container_copy_assignment,
		typename hamon::allocator_traits<InnerAllocs>::propagate_on_container_copy_assignment...
	>;

	// [allocator.adaptor.types]/3
	using propagate_on_container_move_assignment = hamon::conjunction<
		typename hamon::allocator_traits<OuterAlloc>::propagate_on_container_move_assignment,
		typename hamon::allocator_traits<InnerAllocs>::propagate_on_container_move_assignment...
	>;

	// [allocator.adaptor.types]/4
	using propagate_on_container_swap = hamon::conjunction<
		typename hamon::allocator_traits<OuterAlloc>::propagate_on_container_swap,
		typename hamon::allocator_traits<InnerAllocs>::propagate_on_container_swap...
	>;

	// [allocator.adaptor.types]/5
	using is_always_equal = hamon::conjunction<
		typename hamon::allocator_traits<OuterAlloc>::is_always_equal,
		typename hamon::allocator_traits<InnerAllocs>::is_always_equal...
	>;

	template <typename Tp>
	struct rebind
	{
		using other = scoped_allocator_adaptor<
			typename OuterTraits::template rebind_alloc<Tp>,
			InnerAllocs...>;
	};

	HAMON_CXX11_CONSTEXPR
	scoped_allocator_adaptor()
		// [allocator.adaptor.cnstr]/1
		: Base()
	{}

	template <typename OuterA2,
		// [allocator.adaptor.cnstr]/2
		typename = hamon::enable_if_t<
			hamon::is_constructible<OuterAlloc, OuterA2>::value>>
	HAMON_CXX11_CONSTEXPR
	scoped_allocator_adaptor(OuterA2&& outerAlloc, InnerAllocs const&... innerAllocs) HAMON_NOEXCEPT
		: Base(hamon::forward<OuterA2>(outerAlloc), innerAllocs...)
	{}

	HAMON_CXX11_CONSTEXPR
	scoped_allocator_adaptor(scoped_allocator_adaptor const& other) HAMON_NOEXCEPT
		: Base(other)
	{}

	HAMON_CXX11_CONSTEXPR
	scoped_allocator_adaptor(scoped_allocator_adaptor&& other) HAMON_NOEXCEPT
		: Base(hamon::move(other))
	{}

	template <typename OuterA2,
		// [allocator.adaptor.cnstr]/6
		typename = hamon::enable_if_t<
			hamon::is_constructible<OuterAlloc, OuterA2 const&>::value>>
	HAMON_CXX11_CONSTEXPR
	scoped_allocator_adaptor(scoped_allocator_adaptor<OuterA2, InnerAllocs...> const& other) HAMON_NOEXCEPT
		: Base(other.outer_allocator(), other.inner_allocator())
	{}

	template <typename OuterA2,
		// [allocator.adaptor.cnstr]/8
		typename = hamon::enable_if_t<
			hamon::is_constructible<OuterAlloc, OuterA2>::value>>
	HAMON_CXX11_CONSTEXPR
	scoped_allocator_adaptor(scoped_allocator_adaptor<OuterA2, InnerAllocs...>&& other) HAMON_NOEXCEPT
		: Base(hamon::move(other.outer_allocator()), hamon::move(other.inner_allocator()))
	{}

	scoped_allocator_adaptor& operator=(scoped_allocator_adaptor const&) = default;
	scoped_allocator_adaptor& operator=(scoped_allocator_adaptor&&) = default;

//	~scoped_allocator_adaptor();

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR inner_allocator_type&		// nodiscard as an extension
	inner_allocator() HAMON_NOEXCEPT
	{
		return Base::inner_allocator();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR inner_allocator_type const&	// nodiscard as an extension
	inner_allocator() const HAMON_NOEXCEPT
	{
		return Base::inner_allocator();
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR outer_allocator_type&		// nodiscard as an extension
	outer_allocator() HAMON_NOEXCEPT
	{
		return Base::outer_allocator();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR outer_allocator_type const&	// nodiscard as an extension
	outer_allocator() const HAMON_NOEXCEPT
	{
		return Base::outer_allocator();
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR pointer	// nodiscard as an extension
	allocate(size_type n)
	{
		// [allocator.adaptor.members]/5
		return hamon::allocator_traits<OuterAlloc>::allocate(outer_allocator(), n);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR pointer	// nodiscard as an extension
	allocate(size_type n, const_void_pointer hint)
	{
		// [allocator.adaptor.members]/6
		return hamon::allocator_traits<OuterAlloc>::allocate(outer_allocator(), n, hint);
	}

	HAMON_CXX14_CONSTEXPR void deallocate(pointer p, size_type n)
	{
		// [allocator.adaptor.members]/7
		hamon::allocator_traits<OuterAlloc>::deallocate(outer_allocator(), p, n);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	max_size() const
	{
		// [allocator.adaptor.members]/8
		return hamon::allocator_traits<OuterAlloc>::max_size(outer_allocator());
	}

private:
	template <typename T>
	struct construct_fn
	{
		T* m_p;
		scoped_allocator_adaptor* m_this;

		template <typename... NewArgs>
		HAMON_CXX14_CONSTEXPR void operator()(NewArgs&&... newargs) const
		{
			hamon::detail::outermost_alloc_traits<scoped_allocator_adaptor>::construct(
				hamon::detail::outermost(*m_this), m_p, hamon::forward<decltype(newargs)>(newargs)...);
		}
	};

public:
	template <typename T, typename... Args>
	HAMON_CXX14_CONSTEXPR void construct(T* p, Args&&... args)
	{
		// [allocator.adaptor.members]/9
		hamon::apply(
			construct_fn<T>{p, this},
			hamon::uses_allocator_construction_args<T>(inner_allocator(), hamon::forward<Args>(args)...));
	}

	template <typename T>
	HAMON_CXX14_CONSTEXPR void destroy(T* p)
	{
		// [allocator.adaptor.members]/10
		hamon::detail::outermost_alloc_traits<scoped_allocator_adaptor>::destroy(
			hamon::detail::outermost(*this), p);
	}

	HAMON_CXX11_CONSTEXPR scoped_allocator_adaptor
	select_on_container_copy_construction() const
	{
		return Base::select_on_container_copy_construction();
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename OuterAlloc, typename... InnerAllocs>
scoped_allocator_adaptor(OuterAlloc, InnerAllocs...)
->scoped_allocator_adaptor<OuterAlloc, InnerAllocs...>;

#endif

template <typename OuterA1, typename OuterA2>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool	// nodiscard as an extension
operator==(
	scoped_allocator_adaptor<OuterA1> const& a,
	scoped_allocator_adaptor<OuterA2> const& b) HAMON_NOEXCEPT
{
	// [scoped.adaptor.operators]/1
	return a.outer_allocator() == b.outer_allocator();
}

template <typename OuterA1, typename OuterA2, typename InnerAlloc, typename... InnerAllocs>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool	// nodiscard as an extension
operator==(
	scoped_allocator_adaptor<OuterA1, InnerAlloc, InnerAllocs...> const& a,
	scoped_allocator_adaptor<OuterA2, InnerAlloc, InnerAllocs...> const& b) HAMON_NOEXCEPT
{
	// [scoped.adaptor.operators]/1
	return a.outer_allocator() == b.outer_allocator() &&
		a.inner_allocator() == b.inner_allocator();
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename OuterA1, typename OuterA2, typename... InnerAllocs>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool
operator!=(
	scoped_allocator_adaptor<OuterA1, InnerAllocs...> const& a,
	scoped_allocator_adaptor<OuterA2, InnerAllocs...> const& b) HAMON_NOEXCEPT
{
	return !(a == b);
}

#endif

}	// namespace hamon

#endif

#endif // HAMON_SCOPED_ALLOCATOR_SCOPED_ALLOCATOR_ADAPTOR_HPP
