/**
 *	@file	is_nothrow_convertible.hpp
 *
 *	@brief	is_nothrow_convertible
 */

#ifndef HAMON_TYPE_TRAITS_IS_NOTHROW_CONVERTIBLE_HPP
#define HAMON_TYPE_TRAITS_IS_NOTHROW_CONVERTIBLE_HPP

#include <hamon/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_nothrow_convertible) && (__cpp_lib_is_nothrow_convertible >= 201806)

namespace hamon
{

using std::is_nothrow_convertible;

}	// namespace hamon

#else

#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <utility>

namespace hamon
{

/**
 *	@brief		型Fromから型Toに例外を投げずに暗黙的に変換可能か調べる。
 *
 *	@tparam		From	変換元の型
 *	@tparam		To		変換先の型
 *
 *	@require	型Fromと型Toは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_nothrow_convertibleは、型Fromから型Toに例外を投げずに暗黙的に変換可能であればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *
 *	return文による型変換、および非explicitなコンストラクタによる型変換は、暗黙的に変換可能であるとみなされる。
 *	explicitなコンストラクタによる明示的な型変換は、暗黙的に変換可能であるとは見なされない。
 */
template <typename From, typename To>
struct is_nothrow_convertible;

namespace detail
{

template <typename T>
static void test_noexcept(T) noexcept;

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-int-conversion")

template <typename From, typename To>
static hamon::bool_constant<noexcept(test_noexcept<To>(std::declval<From>()))>
is_nothrow_convertible_test();

HAMON_WARNING_POP()

template <typename From, typename To>
struct is_nothrow_convertible_helper : decltype(is_nothrow_convertible_test<From, To>())
{};

}	// namespace detail

template <typename From, typename To>
struct is_nothrow_convertible :
	hamon::disjunction<
		hamon::conjunction<
			hamon::is_void<To>,
			hamon::is_void<From>
		>,
		hamon::conjunction<
			hamon::is_convertible<From, To>,
			detail::is_nothrow_convertible_helper<From, To>
		>
	>
{};

}	// namespace hamon

#endif

namespace hamon
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename From, typename To>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_nothrow_convertible_v = is_nothrow_convertible<From, To>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_NOTHROW_CONVERTIBLE_HPP
