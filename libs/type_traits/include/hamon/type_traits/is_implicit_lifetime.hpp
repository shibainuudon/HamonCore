/**
 *	@file	is_implicit_lifetime.hpp
 *
 *	@brief	is_implicit_lifetime の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_IMPLICIT_LIFETIME_HPP
#define HAMON_TYPE_TRAITS_IS_IMPLICIT_LIFETIME_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/is_aggregate.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_class.hpp>
#include <hamon/type_traits/is_destructible.hpp>
#include <hamon/type_traits/is_scalar.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_move_constructible.hpp>
#include <hamon/type_traits/is_trivially_default_constructible.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

#if defined(__cpp_lib_is_implicit_lifetime) && (__cpp_lib_is_implicit_lifetime >= 202302L)

#define HAMON_USE_STD_IS_IMPLICIT_LIFETIME

using std::is_implicit_lifetime;

#else

/**
 *	@brief		型Tが implicit-lifetime type かを調べる
 *
 *	@tparam		T	チェックする型
 *
 *	implicit-lifetime types とは次のいずれかに該当する型である
 *	1. スカラ型
 *	2. 配列型
 *	3. implicit-lifetime class types
 *	4. 1～3のCV修飾された型
 *
 *	implicit-lifetime class types とは次のいずれかに該当する型である
 *	1. デストラクタがユーザー定義されていない集成体型
 *	2. 資格のある(eligible)トリビアルコンストラクタを少なくとも１つ持ち、トリビアルで削除されていないデストラクタを持つ型
 */
template <typename T>
struct is_implicit_lifetime
#if HAMON_HAS_BUILTIN(__builtin_is_implicit_lifetime)
	: public hamon::bool_constant<__builtin_is_implicit_lifetime(T)> {};
#else
	: public hamon::disjunction<
	hamon::is_scalar<T>,
	hamon::is_array<T>,
	// implicit-lifetime class types
	// 正確な判定はコンパイラマジックでなければ不可能だが、できるだけ頑張る。
	hamon::conjunction<
		hamon::is_class<T>,
		hamon::disjunction<
			hamon::conjunction<
				hamon::is_aggregate<T>,
				hamon::disjunction<
					hamon::is_trivially_destructible<T>,
					hamon::negation<hamon::is_destructible<T>>>>,
			hamon::conjunction<
				hamon::disjunction<
					hamon::is_trivially_default_constructible<T>,
					hamon::is_trivially_copy_constructible<T>,
					hamon::is_trivially_move_constructible<T>
				>,
				hamon::is_trivially_destructible<T>>>>>{};
#endif

#endif

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_implicit_lifetime_v  = is_implicit_lifetime<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_IMPLICIT_LIFETIME_HPP
