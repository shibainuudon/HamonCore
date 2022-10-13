/**
 *	@file	is_aggregate.hpp
 *
 *	@brief	is_aggregate の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_AGGREGATE_HPP
#define HAMON_TYPE_TRAITS_IS_AGGREGATE_HPP

#include <hamon/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_aggregate) && (__cpp_lib_is_aggregate >= 201703)

namespace hamon
{

using std::is_aggregate;

}	// namespace hamon

#elif (defined(HAMON_MSVC) && HAMON_MSVC >= 1920) ||	\
	HAMON_HAS_BUILTIN(__is_aggregate)

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/remove_cv.hpp>

namespace hamon
{

/**
 *	@brief	型Tが集成体か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	remove_all_extents_t<T>した結果の型が、完全型であるか、
 *				void(cv修飾を含む)でなければならない。
 *
 *	is_aggregateは、型Tが集成体 (cv修飾を許容する) であればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *
 *	型Tが集成体であるための条件は以下である：
 *	・ユーザー定義されたコンストラクタ、explicitなコンストラクタ、継承コンストラクタを持たない
 *	・private／protectedな非静的メンバ変数を持たない
 *	・仮想関数を持たない
 *	・仮想基本クラス、private／protected基本クラスを持たない
 */
template <typename T>
struct is_aggregate
	: public hamon::bool_constant<__is_aggregate(hamon::remove_cv_t<T>)> {};

}	// namespace hamon

#else
#  define HAMON_NO_IS_AGGREGATE
#endif

#if !defined(HAMON_NO_IS_AGGREGATE)

#define HAMON_HAS_IS_AGGREGATE

namespace hamon
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_aggregate_v = is_aggregate<T>::value;
#endif

}	// namespace hamon

#endif

#endif // HAMON_TYPE_TRAITS_IS_AGGREGATE_HPP
