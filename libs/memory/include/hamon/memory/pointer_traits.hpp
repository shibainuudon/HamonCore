/**
 *	@file	pointer_traits.hpp
 *
 *	@brief	pointer_traits の定義
 */

#ifndef HAMON_MEMORY_POINTER_TRAITS_HPP
#define HAMON_MEMORY_POINTER_TRAITS_HPP

#include <hamon/config.hpp>
#include <memory>

#if defined(__cpp_lib_constexpr_memory) && (__cpp_lib_constexpr_memory >= 201811L) &&	\
	0	// 標準ライブラリが、"LWG3545: std::pointer_traits should be SFINAE-friendly" を実装しているかどうか判定するのが難しいので、常に自前の実装を使う

#define HAMON_USE_STD_POINTER_TRAITS
#define HAMON_POINTER_TRAITS_NAMESPACE std

namespace hamon
{

using std::pointer_traits;

}	// namespace hamon

#else

#include <hamon/memory/addressof.hpp>
#include <hamon/memory/detail/ptr_traits_elem.hpp>
#include <hamon/memory/detail/ptr_traits_diff.hpp>
#include <hamon/memory/detail/ptr_traits_rebind.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>

#define HAMON_POINTER_TRAITS_NAMESPACE hamon

namespace hamon
{

// 20.2.3 Pointer traits[pointer.traits]

template <typename Ptr, typename E, typename = void>
struct pointer_traits_pointer_to
{
	// [pointer.traits.functions]/4
};

template <typename Ptr, typename E>
struct pointer_traits_pointer_to<Ptr, E,
	hamon::void_t<decltype(Ptr::pointer_to(hamon::declval<E&>()))>>
{
	static Ptr pointer_to(E& r)
		HAMON_NOEXCEPT_IF_EXPR(Ptr::pointer_to(r))	// noexcept as an extension
	{
		// [pointer.traits.functions]/3
		return Ptr::pointer_to(r);
	}
};

template <typename Ptr, typename = void>
struct pointer_traits_impl
{
	// [pointer.traits.types]/2
};

template <typename Ptr>
struct pointer_traits_impl<Ptr,
	hamon::void_t<typename hamon::detail::ptr_traits_elem<Ptr>::type>>
	: public pointer_traits_pointer_to<Ptr, typename hamon::detail::ptr_traits_elem<Ptr>::type>
{
	using pointer = Ptr;	// [pointer.traits.types]/3
	using element_type = typename hamon::detail::ptr_traits_elem<Ptr>::type;	// [pointer.traits.types]/4
	using difference_type = typename hamon::detail::ptr_traits_diff<Ptr>::type;	// [pointer.traits.types]/5

	template <typename U>
	using rebind = typename hamon::detail::ptr_traits_rebind<Ptr, U>::type;		// [pointer.traits.types]/6
};

template <typename Ptr>
struct pointer_traits
	: public pointer_traits_impl<Ptr>
{};

template <typename T>
struct pointer_traits<T*>
{
	using pointer         = T*;
	using element_type    = T;
	using difference_type = hamon::ptrdiff_t;

	template <typename U>
	using rebind = U*;

private:
	// [pointer.traits.functions]/4
	struct nat;

public:
	static constexpr pointer
	pointer_to(hamon::conditional_t<hamon::is_void<element_type>::value, nat, element_type>& r) noexcept
	{
		// [pointer.traits.functions]/3
		return hamon::addressof(r);
	}
};

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_POINTER_TRAITS_HPP
