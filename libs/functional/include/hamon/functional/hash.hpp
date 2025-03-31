/**
 *	@file	hash.hpp
 *
 *	@brief	hash クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_HASH_HPP
#define HAMON_FUNCTIONAL_HASH_HPP

#include <hamon/functional/detail/disabled_hash.hpp>
#include <hamon/functional/hash_combine.hpp>
#include <hamon/array.hpp>
#include <hamon/bit/bit_cast.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/cstdint/uintptr_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/limits.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/is_enum.hpp>
#include <hamon/type_traits/is_floating_point.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_volatile.hpp>
#include <hamon/type_traits/underlying_type.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.10.19 Class template hash[unord.hash]

template <typename T>
struct hash;

namespace detail
{

// hash_array
template <typename T>
HAMON_CXX11_CONSTEXPR hamon::size_t
hash_array_impl(hamon::size_t seed, T const* p, hamon::size_t n) HAMON_NOEXCEPT
{
	return n == 0 ? seed :
		hamon::detail::hash_array_impl(
			hamon::hash_combine(seed, hamon::hash<T>{}(*p)), p + 1, n - 1);
}

template <typename T, hamon::size_t N>
HAMON_CXX11_CONSTEXPR hamon::size_t
hash_array(hamon::array<T, N> const& v, hamon::size_t n) HAMON_NOEXCEPT
{
	return hamon::detail::hash_array_impl(0, v.data(), n);
}

template <typename T, hamon::size_t N>
HAMON_CXX11_CONSTEXPR hamon::size_t
hash_array(hamon::array<T, N> const& v) HAMON_NOEXCEPT
{
	return hamon::detail::hash_array(v, v.size());
}

// hash_integral
template <typename T, bool = (sizeof(T) <= sizeof(hamon::size_t))>
struct hash_integral_impl
{
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	invoke(T v) HAMON_NOEXCEPT
	{
		return static_cast<hamon::size_t>(v);
	}
};

template <typename T>
struct hash_integral_impl<T, false>
{
	static_assert(sizeof(T) <= sizeof(hamon::size_t) * 2, "");

	static HAMON_CXX11_CONSTEXPR hamon::size_t
	invoke(T v) HAMON_NOEXCEPT
	{
		return hamon::hash_combine(
			static_cast<hamon::size_t>(v),
			static_cast<hamon::size_t>(v >> hamon::bitsof<hamon::size_t>()));
	}
};

template <typename T>
HAMON_CXX11_CONSTEXPR hamon::size_t
hash_integral(T v) HAMON_NOEXCEPT
{
	static_assert(hamon::is_integral<T>::value, "");
	return hamon::detail::hash_integral_impl<T>::invoke(v);
}

// hash_float
template <typename T, hamon::size_t = hamon::numeric_limits<T>::digits>
struct hash_float_impl
{
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	invoke(T v) HAMON_NOEXCEPT
	{
		using type = hamon::array<unsigned char, sizeof(T)>;
		return hamon::detail::hash_array(hamon::bit_cast<type>(v));
	}
};

template <typename T>
struct hash_float_impl<T, 64>
{
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	invoke(T v) HAMON_NOEXCEPT
	{
		using type = hamon::array<unsigned char, sizeof(T)>;
		// long double が 拡張倍精度(80bit) の場合、パディングが入る
		return hamon::detail::hash_array(hamon::bit_cast<type>(v), 10);
	}
};

template <typename T>
HAMON_CXX11_CONSTEXPR hamon::size_t
hash_float(T v) HAMON_NOEXCEPT
{
	static_assert(hamon::is_floating_point<T>::value, "");
	// +0.0 と -0.0 は同じハッシュ値を返す
	return hamon::detail::hash_float_impl<T>::invoke(v == T(0) ? 0 : v);
}

// do_hash
template <typename T, typename = hamon::enable_if_t<hamon::is_enum<T>::value>>
HAMON_CXX11_CONSTEXPR hamon::size_t
do_hash_impl(T v, hamon::detail::overload_priority<2>) HAMON_NOEXCEPT
{
	return hamon::detail::hash_integral(
		static_cast<hamon::underlying_type_t<T>>(v));
}

template <typename T, typename = hamon::enable_if_t<hamon::is_integral<T>::value>>
HAMON_CXX11_CONSTEXPR hamon::size_t
do_hash_impl(T v, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
{
	return hamon::detail::hash_integral(v);
}

template <typename T, typename = hamon::enable_if_t<hamon::is_floating_point<T>::value>>
HAMON_CXX11_CONSTEXPR hamon::size_t
do_hash_impl(T v, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
{
	return hamon::detail::hash_float(v);
}

template <typename T>
HAMON_CXX11_CONSTEXPR hamon::size_t
do_hash(T v) HAMON_NOEXCEPT
{
	return hamon::detail::do_hash_impl(v, hamon::detail::overload_priority<2>{});
}

// hash_impl
template <typename T, bool =
	!hamon::is_const<T>::value && !hamon::is_volatile<T>::value &&
	(hamon::is_enum<T>::value ||
	 hamon::is_integral<T>::value ||
	 hamon::is_floating_point<T>::value)>
struct hash_impl
{
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(T v) const HAMON_NOEXCEPT
	{
		return hamon::detail::do_hash(v);
	}
};

template <typename T>
struct hash_impl<T, false>
	: hamon::detail::disabled_hash
{};

}	// namespace detail

template <typename T>
struct hash : public hamon::detail::hash_impl<T>
{};

template <typename T>
struct hash<T*>
{
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(T* v) const HAMON_NOEXCEPT
	{
		using type = hamon::array<unsigned char, sizeof(T*)>;
		return hamon::detail::hash_array(hamon::bit_cast<type>(v));
	}
};

template <>
struct hash<hamon::nullptr_t>
{
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(hamon::nullptr_t) const HAMON_NOEXCEPT
	{
		return hamon::hash<void*>{}(nullptr);
	}
};

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_HASH_HPP
