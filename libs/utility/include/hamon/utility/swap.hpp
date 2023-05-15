/**
 *	@file	swap.hpp
 *
 *	@brief	swap を定義
 */

#ifndef HAMON_UTILITY_SWAP_HPP
#define HAMON_UTILITY_SWAP_HPP

#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 20)

#include <utility>

namespace hamon
{

using std::swap;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
struct is_swappable;
template <typename T>
struct is_nothrow_swappable;

}	// namespace hamon

// 22.2.2 swap[utility.swap]

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

template <typename T,
	// [utility.swap]/1
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::is_move_constructible<T>,
		hamon::is_move_assignable<T>
	>::value>
>
inline HAMON_CXX14_CONSTEXPR void
swap(T& a, T& b)
HAMON_NOEXCEPT_IF((hamon::conjunction<	// [utility.swap]/4
	hamon::is_nothrow_move_constructible<T>,
	hamon::is_nothrow_move_assignable<T>
>::value))
{
	// [utility.swap]/3
	T t(hamon::move(a));
	a = hamon::move(b);
	b = hamon::move(t);
}

HAMON_WARNING_POP()

template <typename T, hamon::size_t N,
	// [utility.swap]/5
	typename = hamon::enable_if_t<hamon::detail::is_swappable<T>::value>
>
inline HAMON_CXX14_CONSTEXPR void
swap(T (&a)[N], T (&b)[N])
HAMON_NOEXCEPT_IF((hamon::detail::is_nothrow_swappable<T>::value))
{
	// [utility.swap]/7
	for (hamon::size_t i = 0; i != N; ++i)
	{
		swap(a[i], b[i]);
	}
}

}	// namespace hamon

#include <hamon/utility/detail/is_swappable.hpp>

#endif

#endif // HAMON_UTILITY_SWAP_HPP
