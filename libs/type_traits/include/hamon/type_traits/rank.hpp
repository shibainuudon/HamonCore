/**
 *	@file	rank.hpp
 *
 *	@brief	rank の定義
 */

#ifndef HAMON_TYPE_TRAITS_RANK_HPP
#define HAMON_TYPE_TRAITS_RANK_HPP

#include <hamon/type_traits/integral_constant.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	配列型の次元数を取得する。
 *
 *	@tparam		T
 *
 *	型Tが配列型である場合、配列の次元数となる整数値をメンバ定数valueの値として定義する。
 *	配列型でなければ0をメンバ定数valueの値として定義する。
 */
template <typename T>
struct rank
	: public hamon::integral_constant<
		hamon::size_t, std::rank<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
hamon::size_t rank_v = rank<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_RANK_HPP
