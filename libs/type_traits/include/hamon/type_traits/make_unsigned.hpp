/**
 *	@file	make_unsigned.hpp
 *
 *	@brief	make_unsigned の定義
 */

#ifndef HAMON_TYPE_TRAITS_MAKE_UNSIGNED_HPP
#define HAMON_TYPE_TRAITS_MAKE_UNSIGNED_HPP

#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/copy_cv.hpp>
#include <hamon/type_traits/is_enum.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/cstdint/uint8_t.hpp>
#include <hamon/cstdint/uint16_t.hpp>
#include <hamon/cstdint/uint32_t.hpp>
#include <hamon/cstdint/uint64_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
struct make_unsigned_impl2
{
private:
	struct incomplete;
public:
	using type =
		hamon::conditional_t<sizeof(T) == 1, hamon::uint8_t,
		hamon::conditional_t<sizeof(T) == 2, hamon::uint16_t,
		hamon::conditional_t<sizeof(T) == 4, hamon::uint32_t,
		hamon::conditional_t<sizeof(T) == 8, hamon::uint64_t,
#if defined(HAMON_HAS_INT128)
		hamon::conditional_t<sizeof(T) == 16, __uint128_t,
#endif
		incomplete
#if defined(HAMON_HAS_INT128)
	>
#endif
	>>>>;
};

template <> struct make_unsigned_impl2<bool> {};
template <> struct make_unsigned_impl2<char>               { using type = unsigned char; };
template <> struct make_unsigned_impl2<signed   char>      { using type = unsigned char; };
template <> struct make_unsigned_impl2<unsigned char>      { using type = unsigned char; };
template <> struct make_unsigned_impl2<signed   short>     { using type = unsigned short; };
template <> struct make_unsigned_impl2<unsigned short>     { using type = unsigned short; };
template <> struct make_unsigned_impl2<signed   int>       { using type = unsigned int; };
template <> struct make_unsigned_impl2<unsigned int>       { using type = unsigned int; };
template <> struct make_unsigned_impl2<signed   long>      { using type = unsigned long; };
template <> struct make_unsigned_impl2<unsigned long>      { using type = unsigned long; };
template <> struct make_unsigned_impl2<signed   long long> { using type = unsigned long long; };
template <> struct make_unsigned_impl2<unsigned long long> { using type = unsigned long long; };

#if defined(HAMON_HAS_INT128)
template <> struct make_unsigned_impl2<__int128_t>  { using type = __uint128_t; };
template <> struct make_unsigned_impl2<__uint128_t> { using type = __uint128_t; };
#endif

template <typename T, bool = hamon::is_integral<T>::value || hamon::is_enum<T>::value>
struct make_unsigned_impl : public make_unsigned_impl2<T> {};

template <typename T>
struct make_unsigned_impl<T, false> {};

}	// namespace detail

// 21.3.8.4 Sign modifications[meta.trans.sign]

/**
 *	@brief	整数型を符号なしにする。
 *
 *	@tparam		T
 *
 *	@require	型Tが、整数型もしくは列挙型(cv修飾を許容する)であること。ただしboolは許可されない。
 *
 *	make_unsignedは、型Tに対応する符号なし整数型を、メンバ型typeとして定義する。
 *	型Tがcv修飾されていた場合は、メンバ型typeにも同じcv修飾が付加される。
 */
template <typename T>
struct make_unsigned
{
	using type = hamon::copy_cv_t<
		typename hamon::detail::make_unsigned_impl<hamon::remove_cv_t<T>>::type,
		T>;
};

template <typename T>
using make_unsigned_t = typename make_unsigned<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_MAKE_UNSIGNED_HPP
