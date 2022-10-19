/**
 *	@file	is_nothrow_invocable_r.hpp
 *
 *	@brief	is_nothrow_invocable_r の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_R_HPP
#define HAMON_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_R_HPP

#include <hamon/config.hpp>
#include <type_traits>

#if defined(HAMON_HAS_CXX11_NOEXCEPT)
#include <hamon/type_traits/is_invocable_r.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/functional/invoke.hpp>
#include <utility>
#else
#include <hamon/type_traits/is_invocable_r.hpp>
#endif

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)

namespace hamon
{

#if defined(__cpp_lib_is_invocable) && (__cpp_lib_is_invocable >= 201703)

using std::is_nothrow_invocable_r;

#else	// __cpp_lib_is_invocable

/**
 *	@brief	型Fnが、与えられた型の引数ArgsTypes...で関数呼び出し可能であり、
 *			その戻り値型がRに変換可能かつ、その際に例外を投げないかどうかを調べる。
 *
 *	@tparam		R
 *	@tparam		Fn
 *	@tparam		ArgTypes
 *
 *	@require	型R, FnおよびArgsTypes...パラメータパックの全ての型が、
 *				完全型であるか、void(cv修飾を含む)か、要素数不明の配列型であること。
 *
 *	型Fnに対して引数ArgsTypes...によるINVOKEコンセプトに従った呼び出しが可能であり、
 *	その結果となる戻り値の型がRに変換可能かつ、
 *	その呼び出し及び変換に際していかなる例外も投げない場合
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename R, typename Fn, typename... ArgTypes>
struct is_nothrow_invocable_r;

#if defined(HAMON_HAS_CXX11_NOEXCEPT)

namespace detail
{

template <bool, typename... Types>
struct is_nothrow_invocable_impl_2
	: public std::false_type
{};

template <typename... Types>
struct is_nothrow_invocable_impl_2<true, Types...>
	: public hamon::bool_constant<
		noexcept(hamon::invoke(std::declval<Types>()...))
	>
{};

template <typename R, typename Fn, typename... ArgTypes>
struct is_nothrow_invocable_impl
{
	using Result = hamon::invoke_result<Fn, ArgTypes...>;

	using type = typename is_nothrow_invocable_impl_2<
		detail::is_invocable_impl<Result, R>::value,
		Fn, ArgTypes...
	>::type;
};

}	// namespace detail

template <typename R, typename Fn, typename... ArgTypes>
struct is_nothrow_invocable_r
	: public detail::is_nothrow_invocable_impl<R, Fn, ArgTypes...>::type
{};

#else	// defined(HAMON_HAS_CXX11_NOEXCEPT)

template <typename R, typename Fn, typename... ArgTypes>
struct is_nothrow_invocable_r
	: public hamon::is_invocable_r<R, Fn, ArgTypes...>
{};

#endif	// defined(HAMON_HAS_CXX11_NOEXCEPT)

#endif	// __cpp_lib_is_invocable

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename R, typename Fn, typename... ArgTypes>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_nothrow_invocable_r_v = is_nothrow_invocable_r<R, Fn, ArgTypes...>::value;

#endif	// defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

}	// namespace hamon

HAMON_WARNING_POP()

#endif // HAMON_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_R_HPP
