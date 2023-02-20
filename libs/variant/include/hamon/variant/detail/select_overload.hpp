/**
 *	@file	select_overload.hpp
 *
 *	@brief	select_overload の定義
 */

#ifndef HAMON_VARIANT_DETAIL_SELECT_OVERLOAD_HPP
#define HAMON_VARIANT_DETAIL_SELECT_OVERLOAD_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/integral_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/index_sequence_for.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace variant_detail
{

struct select_overload_impl
{
private:
	/*
	[variant.ctor]/14

	Let Tj be a type that is determined as follows:
	build an imaginary function FUN(Ti) for each alternative type Ti
	for which Ti x[] = {std​::​forward<T>(t)}; is well-formed for some invented variable x.
	The overload FUN(Tj) selected by overload resolution for the expression
	FUN(std​::​forward<T>(​t)) defines the alternative Tj
	which is the type of the contained value after construction.
	*/

	template <typename T>
	struct Arr { T m_x[1]; };

	template <hamon::size_t I, typename T, typename Ti, typename = void>
	struct FUN
	{
		void operator()();
	};

	template <hamon::size_t I, typename T, typename Ti>
	struct FUN<I, T, Ti, hamon::void_t<decltype(Arr<Ti>{ { hamon::declval<T>() }})>>
	{
		auto operator()(Ti)
			-> hamon::integral_constant<hamon::size_t, I>;
	};

	template <typename Is, typename T, typename... Types>
	struct all_overloads
	{
		void operator()();
	};

#if defined(HAMON_HAS_CXX17_VARIADIC_USING)
	template <hamon::size_t... Is, typename T, typename... Ti>
	struct all_overloads<hamon::index_sequence<Is...>, T, Ti...>
		: public FUN<Is, T, Ti>...
	{
		using FUN<Is, T, Ti>::operator()...;
	};

#else
	template <hamon::size_t I0, hamon::size_t... Is, typename T, typename T0, typename... Ti>
	struct all_overloads<hamon::index_sequence<I0, Is...>, T, T0, Ti...>
		: public FUN<I0, T, T0>
		, public all_overloads<hamon::index_sequence<Is...>, T, Ti...>
	{
		using FUN<I0, T, T0>::operator();
		using all_overloads<hamon::index_sequence<Is...>, T, Ti...>::operator();
	};

#endif

public:
	template <typename T, typename... Types>
	using make_all_overloads =
		all_overloads<hamon::index_sequence_for<Types...>, T, Types...>;
};

template <typename T, typename... Types>
using select_overload =
	decltype(select_overload_impl::make_all_overloads<T, Types...>{}(hamon::declval<T>()));

}	// namespace variant_detail

}	// namespace hamon

#endif // HAMON_VARIANT_DETAIL_SELECT_OVERLOAD_HPP
