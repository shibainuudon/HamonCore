/**
 *	@file	type_identity.hpp
 *
 *	@brief	type_identity
 */

#ifndef HAMON_TYPE_TRAITS_TYPE_IDENTITY_HPP
#define HAMON_TYPE_TRAITS_TYPE_IDENTITY_HPP

#include <type_traits>

namespace hamon
{

#if defined(__cpp_lib_type_identity) && (__cpp_lib_type_identity >= 201806)

using std::type_identity;

#else

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

#endif

/**
 *	@brief	type_identityのエイリアステンプレート
 */
template <typename T>
using type_identity_t = typename type_identity<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_TYPE_IDENTITY_HPP
