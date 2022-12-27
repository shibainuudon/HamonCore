/**
 *	@file	is_invocable.hpp
 *
 *	@brief	is_invocable の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_INVOCABLE_HPP
#define HAMON_TYPE_TRAITS_IS_INVOCABLE_HPP

#include <hamon/functional/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_invocable) && (__cpp_lib_is_invocable >= 201703) && \
	defined(HAMON_USE_STD_REFERENCE_WRAPPER)

namespace hamon
{

using std::is_invocable;

}	// namespace hamon

#else

#include <hamon/type_traits/is_invocable_r.hpp>

namespace hamon
{

/**
 *	@brief	型Fnが、与えられた型の引数ArgsTypes...で関数呼び出し可能かどうかを調べる。
 *
 *	@tparam		Fn
 *	@tparam		ArgTypes
 *
 *	@require	型FnおよびArgsTypes...パラメータパックの全ての型が、
 *				完全型であるか、void(cv修飾を含む)か、要素数不明の配列型であること。
 *
 *	型Fnに対して引数ArgsTypes...によるINVOKEコンセプトに従った呼び出しが可能であれば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename Fn, typename... ArgTypes>
struct is_invocable
	: public hamon::is_invocable_r<void, Fn, ArgTypes...>
{};

}	// namespace hamon

#endif

#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

namespace hamon
{

template <typename Fn, typename... ArgTypes>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_invocable_v = is_invocable<Fn, ArgTypes...>::value;

}	// namespace hamon

#endif

#endif // HAMON_TYPE_TRAITS_IS_INVOCABLE_HPP
