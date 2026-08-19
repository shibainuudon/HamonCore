/**
 *	@file	underlying_type.hpp
 *
 *	@brief	underlying_type の定義
 */

#ifndef HAMON_TYPE_TRAITS_UNDERLYING_TYPE_HPP
#define HAMON_TYPE_TRAITS_UNDERLYING_TYPE_HPP

#include <hamon/type_traits/is_enum.hpp>

namespace hamon
{

// 21.3.8.7 Other transformations[meta.trans.other]

namespace detail
{

template <typename T, bool = hamon::is_enum_v<T>>
struct underlying_type_impl
{
	using type = __underlying_type(T);
};

template <typename T>
struct underlying_type_impl<T, false>
{
};

}	// namespace detail

/**
 *	@brief		enumの基底型を取得する
 *
 *	@tparam		T
 *
 *	@require	型Tが列挙型であること。
 *
 *	underlying_typeは、列挙型Tの基底型を、メンバ型typeとして定義する。
 */
template <typename T>
struct underlying_type
	: public detail::underlying_type_impl<T>
{};

/**
 *	@brief	underlying_typeのエイリアステンプレート
 */
template <typename T>
using underlying_type_t = typename underlying_type<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_UNDERLYING_TYPE_HPP
