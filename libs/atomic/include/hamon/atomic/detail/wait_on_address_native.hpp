/**
 *	@file	wait_on_address_native.hpp
 *
 *	@brief	wait_on_address_native, wake_by_address_single_native, wake_by_address_all_native の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_WAIT_ON_ADDRESS_NATIVE_HPP
#define HAMON_ATOMIC_DETAIL_WAIT_ON_ADDRESS_NATIVE_HPP

#include <hamon/bit/bit_cast.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/make_uint_n.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_PLATFORM_LINUX)
#include <sys/syscall.h>
#include <linux/futex.h>
#elif defined(HAMON_PLATFORM_MACOS)
#include <os/os_sync_wait_on_address.h>
#elif defined(HAMON_PLATFORM_WIN32)
#include <hamon/detail/windows.hpp>		// WaitOnAddress, WakeByAddressSingle, WakeByAddressAll
#pragma comment(lib, "Synchronization.lib")
#endif

namespace hamon
{
namespace detail
{

/**
 *	プラットフォーム固有の待機/起床関数に関する定義
 *	新たなプラットフォームに対応する場合、以下の物を定義する必要がある。
 *	(定義しない場合でも、効率的な待機ができないだけでコンパイルエラーにはならない)
 *
 *	has_native_wait:
 *		プラットフォーム固有の待機/起床関数が有るかどうか。
 *		この値がfalseの場合、atomic_waitはビジーループになる。
 *
 *	is_native_waitable<T>:
 *		プラットフォーム固有の待機/起床関数が、型Tを引数に呼び出し可能かどうか。
 *		is_native_waitable<T>::valueがtrueの場合、プラットフォーム固有の関数を直接呼び出す。
 *		falseの場合、native_wait_t 型を引数に間接的に関数を呼び出す。
 *
 *	native_wait_t:
 *		プラットフォーム固有の待機/起床関数に渡すことが可能な型。
 *
 *	=== has_native_wait が true の場合、以下の3つの関数を定義する必要がある。 ===
 * 
 *	wait_on_address_native:
 *		プラットフォーム固有の待機関数。起床されるまで待機する。
 *
 *	wake_by_address_single_native:
 *		プラットフォーム固有の起床関数。待機しているスレッドを一つ起床させる。
 *
 *	wake_by_address_all_native:
 *		プラットフォーム固有の起床関数。待機しているスレッドを全て起床させる。
 */

template <typename T>
void wait_on_address_native(T* ptr, T val);

template <typename T>
void wake_by_address_single_native(T* ptr);

template <typename T>
void wake_by_address_all_native(T* ptr);

#if defined(HAMON_PLATFORM_LINUX)

constexpr bool has_native_wait = true;

template <typename T>
struct is_native_waitable
	: public hamon::bool_constant<
		sizeof(T) == 4
	>
{};

using native_wait_t = int;

inline void futex(int* uaddr, int op, int val)
{
	syscall(SYS_futex, uaddr, op, val, NULL, NULL, 0);
}

template <typename T>
void wait_on_address_native(T* ptr, T val)
{
	static_assert(hamon::detail::is_native_waitable<T>::value, "");
	hamon::detail::futex(reinterpret_cast<int*>(ptr), FUTEX_WAIT_PRIVATE, hamon::bit_cast<int>(val));
}

template <typename T>
void wake_by_address_single_native(T* ptr)
{
	static_assert(hamon::detail::is_native_waitable<T>::value, "");
	hamon::detail::futex(reinterpret_cast<int*>(ptr), FUTEX_WAKE_PRIVATE, 1);
}

template <typename T>
void wake_by_address_all_native(T* ptr)
{
	static_assert(hamon::detail::is_native_waitable<T>::value, "");
	hamon::detail::futex(reinterpret_cast<int*>(ptr), FUTEX_WAKE_PRIVATE, hamon::numeric_limits<int>::max());
}

#elif defined(HAMON_PLATFORM_MACOS)

constexpr bool has_native_wait = true;

template <typename T>
struct is_native_waitable
	: public hamon::bool_constant<
		sizeof(T) == 4 ||
		sizeof(T) == 8
	>
{};

using native_wait_t = int;

template <typename T>
void wait_on_address_native(T* ptr, T val)
{
	static_assert(hamon::detail::is_native_waitable<T>::value, "");
	using U = hamon::make_uint_n_t<sizeof(T) * 8>;
	os_sync_wait_on_address(ptr, hamon::bit_cast<U>(val), sizeof(T), OS_SYNC_WAIT_ON_ADDRESS_NONE);
}

template <typename T>
void wake_by_address_single_native(T* ptr)
{
	static_assert(hamon::detail::is_native_waitable<T>::value, "");
	os_sync_wake_by_address_any(ptr, sizeof(T), OS_SYNC_WAKE_BY_ADDRESS_NONE);
}

template <typename T>
void wake_by_address_all_native(T* ptr)
{
	static_assert(hamon::detail::is_native_waitable<T>::value, "");
	os_sync_wake_by_address_all(ptr, sizeof(T), OS_SYNC_WAKE_BY_ADDRESS_NONE);
}

#elif defined(HAMON_PLATFORM_WIN32)

constexpr bool has_native_wait = true;

template <typename T>
struct is_native_waitable
	: public hamon::bool_constant<
		sizeof(T) == 1 ||
		sizeof(T) == 2 ||
		sizeof(T) == 4 ||
		sizeof(T) == 8
	>
{};

using native_wait_t = int;

template <typename T>
void wait_on_address_native(T* ptr, T val)
{
	static_assert(hamon::detail::is_native_waitable<T>::value, "");
	WaitOnAddress(ptr, hamon::addressof(val), sizeof(T), INFINITE);
}

template <typename T>
void wake_by_address_single_native(T* ptr)
{
	static_assert(hamon::detail::is_native_waitable<T>::value, "");
	WakeByAddressSingle(ptr);
}

template <typename T>
void wake_by_address_all_native(T* ptr)
{
	static_assert(hamon::detail::is_native_waitable<T>::value, "");
	WakeByAddressAll(ptr);
}

#else

constexpr bool has_native_wait = false;

template <typename T>
struct is_native_waitable
	: public hamon::false_type
{};

using native_wait_t = int;

#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_WAIT_ON_ADDRESS_NATIVE_HPP
