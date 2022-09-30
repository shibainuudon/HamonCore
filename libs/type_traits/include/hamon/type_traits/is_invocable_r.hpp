/**
 *	@file	is_invocable_r.hpp
 *
 *	@brief	is_invocable_r の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_INVOCABLE_R_HPP
#define HAMON_TYPE_TRAITS_IS_INVOCABLE_R_HPP

#include <type_traits>

#if defined(__cpp_lib_is_invocable) && (__cpp_lib_is_invocable >= 201703)

namespace hamon
{

using std::is_invocable_r;

}	// namespace hamon

#else

#include <hamon/type_traits/detail/is_invocable_impl.hpp>
#include <hamon/type_traits/invoke_result.hpp>

namespace hamon
{

/**
 *	@brief	型Fnが、与えられた型の引数ArgsTypes...で関数呼び出し可能であり、
 *			その戻り値型がRに変換可能かどうかを調べる。
 *
 *	@tparam		R
 *	@tparam		Fn
 *	@tparam		ArgTypes
 *
 *	@require	型R, FnおよびArgsTypes...パラメータパックの全ての型が、
 *				完全型であるか、void(cv修飾を含む)か、要素数不明の配列型であること。
 *
 *	型Fnに対して引数ArgsTypes...によるINVOKEコンセプトに従った呼び出しが可能であり、
 *	その結果となる戻り値の型がRに変換可能であればtrue_typeから派生し、そうでなければfalse_typeから派生する。
 */

template <typename R, typename Fn, typename... ArgTypes>
struct is_invocable_r
	: public detail::is_invocable_impl<
		hamon::invoke_result<Fn, ArgTypes...>, R
	>::type
{};

}	// namespace hamon

#endif

#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

namespace hamon
{

template <typename R, typename Fn, typename... ArgTypes>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_invocable_r_v = is_invocable_r<R, Fn, ArgTypes...>::value;

}	// namespace hamon

#endif

#endif // HAMON_TYPE_TRAITS_IS_INVOCABLE_R_HPP
