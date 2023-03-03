/**
 *	@file	conjunction.hpp
 *
 *	@brief	conjunction
 */

#ifndef HAMON_TYPE_TRAITS_CONJUNCTION_HPP
#define HAMON_TYPE_TRAITS_CONJUNCTION_HPP

#include <type_traits>

#if defined(__cpp_lib_logical_traits) && (__cpp_lib_logical_traits >= 201510)

namespace hamon
{

using std::conjunction;

}	// namespace hamon

#else

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>

namespace hamon
{

/**
 *	@brief		コンパイル時の論理AND
 *
 *	@tparam		B
 *
 *	conjunction<B1, ..., Bn> は最初にBi::value == false となるBiから派生する。
 *	もし全てのBiにおいて Bi::value != false ならBnから派生する。
 *	sizeof...(B) == 0 のときは、true_typeから派生する。
 *
 *	conjunctionはショート・サーキットされる：もしBi::value == falseとなったら、
 *	それ以降のBiはインスタンス化されない。
 *
 *	備考：
 *	Bは必ずしもtrue_typeまたはfalse_typeから派生している必要はない。
 *	B::valueを持っていて、B::valueがboolに変換可能であれば良い。
 *	例)
 *	conjunction<integral_constant<int, 2>, integral_constant<int, 4>>::value
 *	は 4 になる。
 */
template <typename... B>
struct conjunction;

namespace detail
{

template <typename...>
struct conjunction_impl;

template <>
struct conjunction_impl<>
	: public hamon::true_type
{};

template <typename B0>
struct conjunction_impl<B0>
	: public B0
{};

template <typename B0, typename... Bn>
struct conjunction_impl<B0, Bn...>
	: public hamon::conditional_t<
		static_cast<bool>(B0::value),
		conjunction_impl<Bn...>,
		B0
	>
{};

}	// namespace detail

template <typename... B>
struct conjunction
	: public detail::conjunction_impl<B...>
{};

}	// namespace hamon

#endif

#include <hamon/config.hpp>

namespace hamon
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename... B>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool conjunction_v = conjunction<B...>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_CONJUNCTION_HPP
