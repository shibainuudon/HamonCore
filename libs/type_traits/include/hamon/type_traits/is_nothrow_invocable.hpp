/**
 *	@file	is_nothrow_invocable.hpp
 *
 *	@brief	is_nothrow_invocable の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_HPP
#define HAMON_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_HPP

#include <hamon/type_traits/is_nothrow_invocable_r.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

#if defined(__cpp_lib_is_invocable) && (__cpp_lib_is_invocable >= 201703)

using std::is_nothrow_invocable;

#else	// __cpp_lib_is_invocable

/**
 *	@brief	型Fnが、与えられた型の引数ArgsTypes...で関数呼び出し可能であり、
 *			その呼び出しに際して例外を投げないかどうかを調べる。
 *
 *	@tparam		Fn
 *	@tparam		ArgTypes
 *
 *	@require	型FnおよびArgsTypes...パラメータパックの全ての型が、
 *				完全型であるか、void(cv修飾を含む)か、要素数不明の配列型であること。
 *
 *	型Fnに対して引数ArgsTypes...によるINVOKEコンセプトに従った呼び出しが可能であり、
 *	いかなる例外も投げない場合true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename Fn, typename... ArgTypes>
struct is_nothrow_invocable
	: public hamon::is_nothrow_invocable_r<void, Fn, ArgTypes...>
{};

#endif	// __cpp_lib_is_invocable

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename Fn, typename... ArgTypes>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_nothrow_invocable_v = is_nothrow_invocable<Fn, ArgTypes...>::value;

#endif	// defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_HPP
