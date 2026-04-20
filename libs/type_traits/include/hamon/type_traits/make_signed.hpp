/**
 *	@file	make_signed.hpp
 *
 *	@brief	make_signed の定義
 */

#ifndef HAMON_TYPE_TRAITS_MAKE_SIGNED_HPP
#define HAMON_TYPE_TRAITS_MAKE_SIGNED_HPP

#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/copy_cv.hpp>
#include <hamon/type_traits/is_enum.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/cstdint/int8_t.hpp>
#include <hamon/cstdint/int16_t.hpp>
#include <hamon/cstdint/int32_t.hpp>
#include <hamon/cstdint/int64_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
struct make_signed_impl2
{
private:
	struct incomplete;
public:
	using type =
		hamon::conditional_t<sizeof(T) == 1, hamon::int8_t,
		hamon::conditional_t<sizeof(T) == 2, hamon::int16_t,
		hamon::conditional_t<sizeof(T) == 4, hamon::int32_t,
		hamon::conditional_t<sizeof(T) == 8, hamon::int64_t,
#if defined(HAMON_HAS_INT128)
		hamon::conditional_t<sizeof(T) == 16, __int128_t,
#endif
		incomplete
#if defined(HAMON_HAS_INT128)
	>
#endif
	>>>>;
};

template <> struct make_signed_impl2<bool> {};
template <> struct make_signed_impl2<char>               { using type = signed char; };
template <> struct make_signed_impl2<signed   char>      { using type = signed char; };
template <> struct make_signed_impl2<unsigned char>      { using type = signed char; };
template <> struct make_signed_impl2<signed   short>     { using type = signed short; };
template <> struct make_signed_impl2<unsigned short>     { using type = signed short; };
template <> struct make_signed_impl2<signed   int>       { using type = signed int; };
template <> struct make_signed_impl2<unsigned int>       { using type = signed int; };
template <> struct make_signed_impl2<signed   long>      { using type = signed long; };
template <> struct make_signed_impl2<unsigned long>      { using type = signed long; };
template <> struct make_signed_impl2<signed   long long> { using type = signed long long; };
template <> struct make_signed_impl2<unsigned long long> { using type = signed long long; };

#if defined(HAMON_HAS_INT128)
template <> struct make_signed_impl2<__int128_t>  { using type = __int128_t; };
template <> struct make_signed_impl2<__uint128_t> { using type = __int128_t; };
#endif

template <typename T, bool = hamon::is_integral<T>::value || hamon::is_enum<T>::value>
struct make_signed_impl : public make_signed_impl2<T> {};

template <typename T>
struct make_signed_impl<T, false> {};

}	// namespace detail

/**
 *	@brief	整数型を符号付きにする。
 *
 *	@tparam		T
 *
 *	@require	型Tが、整数型もしくは列挙型(cv修飾を許容する)であること。ただしboolは許可されない。
 *
 *	make_signedは、型Tに対応する符号付き整数型を、メンバ型typeとして定義する。
 *	型Tがcv修飾されていた場合は、メンバ型typeにも同じcv修飾が付加される。
 */
template <typename T>
struct make_signed
{
	using type = hamon::copy_cv_t<
		typename hamon::detail::make_signed_impl<hamon::remove_cv_t<T>>::type,
		T>;
};

template <typename T>
using make_signed_t = typename make_signed<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_MAKE_SIGNED_HPP
