/**
 *	@file	allocator_traits.hpp
 *
 *	@brief	allocator_traits の定義
 */

#ifndef HAMON_MEMORY_ALLOCATOR_TRAITS_HPP
#define HAMON_MEMORY_ALLOCATOR_TRAITS_HPP

#include <hamon/memory/config.hpp>

#if defined(HAMON_USE_STD_ALLOCATOR_TRAITS)

namespace hamon
{

using std::allocator_traits;

}	// namespace hamon

#else

#include <hamon/detail/overload_priority.hpp>
#include <hamon/memory/allocation_result.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/destroy_at.hpp>
#include <hamon/memory/detail/replace_first_arg.hpp>
#include <hamon/memory/pointer_traits.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_empty.hpp>
#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4996)
HAMON_WARNING_DISABLE_CLANG("-Wdeprecated-declarations")

namespace hamon
{

namespace detail
{

// [allocator.traits.types]/1
template <typename Alloc, typename = void>
struct allocator_traits_pointer
{
	using value_type = typename Alloc::value_type;
	using type = value_type*;
};

template <typename Alloc>
struct allocator_traits_pointer<Alloc, hamon::void_t<typename Alloc::pointer>>
{
	using type = typename Alloc::pointer;
};

template <typename Alloc>
using allocator_traits_pointer_t = typename allocator_traits_pointer<Alloc>::type;

// [allocator.traits.types]/2
template <typename Alloc, typename = void>
struct allocator_traits_const_pointer
{
	using value_type = typename Alloc::value_type;
	using pointer = allocator_traits_pointer_t<Alloc>;
	using type = typename hamon::pointer_traits<pointer>::template rebind<value_type const>;
};

template <typename Alloc>
struct allocator_traits_const_pointer<Alloc, hamon::void_t<typename Alloc::const_pointer>>
{
	using type = typename Alloc::const_pointer;
};

template <typename Alloc>
using allocator_traits_const_pointer_t = typename allocator_traits_const_pointer<Alloc>::type;

// [allocator.traits.types]/3
template <typename Alloc, typename = void>
struct allocator_traits_void_pointer
{
	using pointer = allocator_traits_pointer_t<Alloc>;
	using type = typename hamon::pointer_traits<pointer>::template rebind<void>;
};

template <typename Alloc>
struct allocator_traits_void_pointer<Alloc, hamon::void_t<typename Alloc::void_pointer>>
{
	using type = typename Alloc::void_pointer;
};

template <typename Alloc>
using allocator_traits_void_pointer_t = typename allocator_traits_void_pointer<Alloc>::type;

// [allocator.traits.types]/4
template <typename Alloc, typename = void>
struct allocator_traits_const_void_pointer
{
	using pointer = allocator_traits_pointer_t<Alloc>;
	using type = typename hamon::pointer_traits<pointer>::template rebind<void const>;
};

template <typename Alloc>
struct allocator_traits_const_void_pointer<Alloc, hamon::void_t<typename Alloc::const_void_pointer>>
{
	using type = typename Alloc::const_void_pointer;
};

template <typename Alloc>
using allocator_traits_const_void_pointer_t = typename allocator_traits_const_void_pointer<Alloc>::type;

// [allocator.traits.types]/5
template <typename Alloc, typename = void>
struct allocator_traits_difference_type
{
	using pointer = allocator_traits_pointer_t<Alloc>;
	using type = typename hamon::pointer_traits<pointer>::difference_type;
};

template <typename Alloc>
struct allocator_traits_difference_type<Alloc, hamon::void_t<typename Alloc::difference_type>>
{
	using type = typename Alloc::difference_type;
};

template <typename Alloc>
using allocator_traits_difference_type_t = typename allocator_traits_difference_type<Alloc>::type;

// [allocator.traits.types]/6
template <typename Alloc, typename = void>
struct allocator_traits_size_type
{
	using difference_type = allocator_traits_difference_type_t<Alloc>;
	using type = hamon::make_unsigned_t<difference_type>;
};

template <typename Alloc>
struct allocator_traits_size_type<Alloc, hamon::void_t<typename Alloc::size_type>>
{
	using type = typename Alloc::size_type;
};

template <typename Alloc>
using allocator_traits_size_type_t = typename allocator_traits_size_type<Alloc>::type;

// [allocator.traits.types]/7
template <typename Alloc, typename = void>
struct allocator_traits_propagate_on_container_copy_assignment
{
	using type = hamon::false_type;
};

template <typename Alloc>
struct allocator_traits_propagate_on_container_copy_assignment<Alloc, hamon::void_t<typename Alloc::propagate_on_container_copy_assignment>>
{
	using type = typename Alloc::propagate_on_container_copy_assignment;
};

template <typename Alloc>
using allocator_traits_propagate_on_container_copy_assignment_t = typename allocator_traits_propagate_on_container_copy_assignment<Alloc>::type;

// [allocator.traits.types]/8
template <typename Alloc, typename = void>
struct allocator_traits_propagate_on_container_move_assignment
{
	using type = hamon::false_type;
};

template <typename Alloc>
struct allocator_traits_propagate_on_container_move_assignment<Alloc, hamon::void_t<typename Alloc::propagate_on_container_move_assignment>>
{
	using type = typename Alloc::propagate_on_container_move_assignment;
};

template <typename Alloc>
using allocator_traits_propagate_on_container_move_assignment_t = typename allocator_traits_propagate_on_container_move_assignment<Alloc>::type;

// [allocator.traits.types]/9
template <typename Alloc, typename = void>
struct allocator_traits_propagate_on_container_swap
{
	using type = hamon::false_type;
};

template <typename Alloc>
struct allocator_traits_propagate_on_container_swap<Alloc, hamon::void_t<typename Alloc::propagate_on_container_swap>>
{
	using type = typename Alloc::propagate_on_container_swap;
};

template <typename Alloc>
using allocator_traits_propagate_on_container_swap_t = typename allocator_traits_propagate_on_container_swap<Alloc>::type;

// [allocator.traits.types]/10
template <typename Alloc, typename = void>
struct allocator_traits_is_always_equal
{
	using type = typename hamon::is_empty<Alloc>::type;
};

template <typename Alloc>
struct allocator_traits_is_always_equal<Alloc, hamon::void_t<typename Alloc::is_always_equal>>
{
	using type = typename Alloc::is_always_equal;
};

template <typename Alloc>
using allocator_traits_is_always_equal_t = typename allocator_traits_is_always_equal<Alloc>::type;

// [allocator.traits.types]/11
template <typename Alloc, typename T, typename = void>
struct allocator_traits_rebind_alloc
{
	using type = typename hamon::detail::replace_first_arg<Alloc, T>::type;
};

template <typename Alloc, typename T>
struct allocator_traits_rebind_alloc<Alloc, T, hamon::void_t<typename Alloc::template rebind<T>::other>>
{
	using type = typename Alloc::template rebind<T>::other;
};

template <typename Alloc, typename T>
using allocator_traits_rebind_alloc_t = typename allocator_traits_rebind_alloc<Alloc, T>::type;

}	// namespace detail

// 20.2.9 Allocator traits[allocator.traits]

template <typename Alloc>
struct allocator_traits
{
	using allocator_type     = Alloc;

	using value_type         = typename Alloc::value_type;

	using pointer            = hamon::detail::allocator_traits_pointer_t<Alloc>;
	using const_pointer      = hamon::detail::allocator_traits_const_pointer_t<Alloc>;
	using void_pointer       = hamon::detail::allocator_traits_void_pointer_t<Alloc>;
	using const_void_pointer = hamon::detail::allocator_traits_const_void_pointer_t<Alloc>;

	using difference_type    = hamon::detail::allocator_traits_difference_type_t<Alloc>;
	using size_type          = hamon::detail::allocator_traits_size_type_t<Alloc>;

	using propagate_on_container_copy_assignment = hamon::detail::allocator_traits_propagate_on_container_copy_assignment_t<Alloc>;
	using propagate_on_container_move_assignment = hamon::detail::allocator_traits_propagate_on_container_move_assignment_t<Alloc>;
	using propagate_on_container_swap            = hamon::detail::allocator_traits_propagate_on_container_swap_t<Alloc>;
	using is_always_equal                        = hamon::detail::allocator_traits_is_always_equal_t<Alloc>;

	template <typename T>
	using rebind_alloc = hamon::detail::allocator_traits_rebind_alloc_t<Alloc, T>;

	template <typename T>
	using rebind_traits = allocator_traits<rebind_alloc<T>>;

private:
	// [allocator.traits.members]/2
	template <typename A2>
	static HAMON_CXX11_CONSTEXPR auto
	allocate_hint_impl(A2& a, size_type n, const_void_pointer hint, hamon::detail::overload_priority<1>)
	->decltype(a.allocate(n, hint))
	{
		return a.allocate(n, hint);
	}

	template <typename A2>
	static HAMON_CXX11_CONSTEXPR pointer
	allocate_hint_impl(A2& a, size_type n, const_void_pointer, hamon::detail::overload_priority<0>)
	{
		return a.allocate(n);
	}

	// [allocator.traits.members]/3
	template <typename A2>
	static HAMON_CXX11_CONSTEXPR auto
	allocate_at_least_impl(A2& a, size_type n, hamon::detail::overload_priority<1>)
	->decltype(a.allocate_at_least(n))
	{
		return a.allocate_at_least(n);
	}

	template <typename A2>
	static HAMON_CXX11_CONSTEXPR hamon::allocation_result<pointer, size_type>
	allocate_at_least_impl(A2& a, size_type n, hamon::detail::overload_priority<0>)
	{
		return {a.allocate(n), n};
	}

	// [allocator.traits.members]/6
	template <typename A2, typename T, typename... Args>
	static HAMON_CXX14_CONSTEXPR auto
	construct_impl(hamon::detail::overload_priority<1>, A2& a, T* p, Args&&... args)
	->decltype(a.construct(p, hamon::forward<Args>(args)...))
	{
		return a.construct(p, hamon::forward<Args>(args)...);
	}

	template <typename A2, typename T, typename... Args>
	static HAMON_CXX14_CONSTEXPR auto
	construct_impl(hamon::detail::overload_priority<0>, A2&, T* p, Args&&... args)
	->decltype(hamon::construct_at(p, hamon::forward<Args>(args)...))
	{
		return hamon::construct_at(p, hamon::forward<Args>(args)...);
	}

	// [allocator.traits.members]/7
	template <typename A2, typename T>
	static HAMON_CXX14_CONSTEXPR auto
	destroy_impl(A2& a, T* p, hamon::detail::overload_priority<1>)
	->decltype(a.destroy(p))
	{
		return a.destroy(p);
	}

	template <typename A2, typename T>
	static HAMON_CXX14_CONSTEXPR auto
	destroy_impl(A2&, T* p, hamon::detail::overload_priority<0>)
	->decltype(hamon::destroy_at(p))
	{
		return hamon::destroy_at(p);
	}

	// [allocator.traits.members]/8
	template <typename A2>
	static HAMON_CXX11_CONSTEXPR auto
	max_size_impl(A2 const& a, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
	->decltype(a.max_size())
	{
		return a.max_size();
	}

	template <typename A2>
	static HAMON_CXX11_CONSTEXPR size_type
	max_size_impl(A2 const&, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
	{
		return hamon::numeric_limits<size_type>::max() / sizeof(value_type);
	}

	// [allocator.traits.members]/9
	template <typename A2>
	static HAMON_CXX11_CONSTEXPR auto
	select_on_container_copy_construction_impl(A2 const& rhs, hamon::detail::overload_priority<1>)
	->decltype(rhs.select_on_container_copy_construction())
	{
		return rhs.select_on_container_copy_construction();
	}

	template <typename A2>
	static HAMON_CXX11_CONSTEXPR A2
	select_on_container_copy_construction_impl(A2 const& rhs, hamon::detail::overload_priority<0>)
	{
		return rhs;
	}

public:
	HAMON_NODISCARD static HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	pointer allocate(Alloc& a, size_type n)
	{
		// [allocator.traits.members]/1
		return a.allocate(n);
	}

	HAMON_NODISCARD static HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	pointer allocate(Alloc& a, size_type n, const_void_pointer hint)
	{
		return allocate_hint_impl(a, n, hint, hamon::detail::overload_priority<1>{});
	}

	HAMON_NODISCARD static HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	hamon::allocation_result<pointer, size_type>
	allocate_at_least(Alloc& a, size_type n)
	{
		return allocate_at_least_impl(a, n, hamon::detail::overload_priority<1>{});
	}

	static HAMON_CXX14_CONSTEXPR void
	deallocate(Alloc& a, pointer p, size_type n)
	{
		// [allocator.traits.members]/4
		a.deallocate(p, n);
	}

	template <typename T, typename... Args>
	static HAMON_CXX14_CONSTEXPR auto
	construct(Alloc& a, T* p, Args&&... args)
	->decltype(construct_impl(hamon::detail::overload_priority<1>{}, a, p, hamon::forward<Args>(args)...))
	{
		return construct_impl(hamon::detail::overload_priority<1>{}, a, p, hamon::forward<Args>(args)...);
	}

	template <typename T>
	static HAMON_CXX14_CONSTEXPR auto
	destroy(Alloc& a, T* p)
	->decltype(destroy_impl(a, p, hamon::detail::overload_priority<1>{}))
	{
		return destroy_impl(a, p, hamon::detail::overload_priority<1>{});
	}

	HAMON_NODISCARD static HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	size_type max_size(Alloc const& a) HAMON_NOEXCEPT
	{
		return max_size_impl(a, hamon::detail::overload_priority<1>{});
	}

	HAMON_NODISCARD static HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	Alloc select_on_container_copy_construction(Alloc const& rhs)
	{
		return select_on_container_copy_construction_impl(rhs, hamon::detail::overload_priority<1>{});
	}
};

}	// namespace hamon

HAMON_WARNING_POP()

#endif

#endif // HAMON_MEMORY_ALLOCATOR_TRAITS_HPP
