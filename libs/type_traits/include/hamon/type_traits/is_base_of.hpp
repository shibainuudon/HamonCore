/**
 *	@file	is_base_of.hpp
 *
 *	@brief	is_base_of の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_BASE_OF_HPP
#define HAMON_TYPE_TRAITS_IS_BASE_OF_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.7 Relationships between types[meta.rel]

/**
 *	@brief	型Baseが型Derivedの基底クラスか調べる。
 *
 *	@tparam		Base
 *	@tparam		Derived
 *
 *	@require	BaseとDerivedが非共用体のクラスであり、異なる型である場合(cv修飾は無視される)、
 *				Derivedは完全型でなければならない。
 *
 *	is_base_ofは、型Baseが型Derivedの基底クラス (cv修飾は無視される) である、もしくは2つが同じクラス型ならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	派生時のprivate、protected指定は、派生関係の判定に影響しない。
 */
template <typename Base, typename Derived>
struct is_base_of
	: public hamon::bool_constant<
#if HAMON_HAS_BUILTIN(__is_base_of) || defined(HAMON_MSVC)
		__is_base_of(Base, Derived)
#else
		// TODO
#endif
	>
{};

template <typename Base, typename Derived>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_base_of_v = is_base_of<Base, Derived>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_BASE_OF_HPP
