/**
 *	@file	is_aggregate.hpp
 *
 *	@brief	is_aggregate の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_AGGREGATE_HPP
#define HAMON_TYPE_TRAITS_IS_AGGREGATE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

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
	: public hamon::bool_constant<
#if HAMON_HAS_BUILTIN(__is_aggregate) || defined(HAMON_MSVC)
		__is_aggregate(T)
#else
		// TODO
#endif
	>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_aggregate_v = is_aggregate<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_AGGREGATE_HPP
