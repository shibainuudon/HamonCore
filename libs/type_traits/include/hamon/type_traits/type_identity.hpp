/**
 *	@file	type_identity.hpp
 *
 *	@brief	type_identity
 */

#ifndef HAMON_TYPE_TRAITS_TYPE_IDENTITY_HPP
#define HAMON_TYPE_TRAITS_TYPE_IDENTITY_HPP

namespace hamon
{

// 21.3.8.7 Other transformations[meta.trans.other]

/**
 *	@brief		type_identity
 *
 *	@tparam		T
 *
 *	type_identityは型Tをメンバ型typeとして定義する。
 */
template <typename T>
struct type_identity
{
	using type = T;
};

/**
 *	@brief	type_identityのエイリアステンプレート
 */
template <typename T>
using type_identity_t = typename type_identity<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_TYPE_IDENTITY_HPP
