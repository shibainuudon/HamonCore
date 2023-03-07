/**
 *	@file	alignment_of.hpp
 *
 *	@brief	alignment_of の定義
 */

#ifndef HAMON_TYPE_TRAITS_ALIGNMENT_OF_HPP
#define HAMON_TYPE_TRAITS_ALIGNMENT_OF_HPP

#include <hamon/type_traits/integral_constant.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief		型Tのアラインメントを取得する
 *
 *	@tparam		T	取得する型
 *
 *	@require	型Tに対してalignof(T)が有効であること。
 *
 *	alignof(T)で得られたsize_t型の値を、メンバ定数valueとして定義する。
 *	Tが配列型の場合、要素の型のアラインメントを取得します。
 *	Tが参照型の場合、参照している型のアラインメントを取得します。
 */
template <typename T>
struct alignment_of
	: public hamon::integral_constant<
		hamon::size_t, std::alignment_of<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
hamon::size_t alignment_of_v = alignment_of<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_ALIGNMENT_OF_HPP
