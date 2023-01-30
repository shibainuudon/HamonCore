/**
 *	@file	constrained_param.hpp
 *
 *	@brief	HAMON_CONSTRAINED_PARAM マクロの定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CONSTRAINED_PARAM_HPP
#define HAMON_CONCEPTS_DETAIL_CONSTRAINED_PARAM_HPP

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/preprocessor/facilities/expand.hpp>
#include <hamon/preprocessor/tuple/size.hpp>
#include <hamon/preprocessor/cat.hpp>
#include <hamon/config.hpp>

#define HAMON_CONSTRAINED_PARAM(C, ...)	\
	HAMON_PP_EXPAND_I(HAMON_PP_CAT(HAMON_CONSTRAINED_PARAM_, HAMON_PP_TUPLE_SIZE((__VA_ARGS__)))(C, __VA_ARGS__))

#define HAMON_CONSTRAINED_PARAM_D(C, ...)	\
	HAMON_PP_EXPAND_I(HAMON_PP_CAT(HAMON_CONSTRAINED_PARAM_D_, HAMON_PP_TUPLE_SIZE((__VA_ARGS__)))(C, __VA_ARGS__))

#if defined(HAMON_HAS_CXX20_CONCEPTS)

#define HAMON_CONSTRAINED_PARAM_1(C, T1)			C T1
#define HAMON_CONSTRAINED_PARAM_2(C, T1, T2)		C<T1> T2
#define HAMON_CONSTRAINED_PARAM_D_2(C, T1, D)		C T1 = D
#define HAMON_CONSTRAINED_PARAM_D_3(C, T1, T2, D)	C<T1> T2 = D
#define HAMON_CONSTRAINED_PARAM_D_4(C, T1, T2, T3, D)	C<T1, T2> T3 = D

#else

#define HAMON_CONSTRAINED_PARAM_1(C, T1)			typename T1, typename = hamon::enable_if_t<C<T1>::value>
#define HAMON_CONSTRAINED_PARAM_2(C, T1, T2)		typename T2, typename = hamon::enable_if_t<C<T2, T1>::value>
#define HAMON_CONSTRAINED_PARAM_D_2(C, T1, D)		typename T1 = D, typename = hamon::enable_if_t<C<T1>::value>
#define HAMON_CONSTRAINED_PARAM_D_3(C, T1, T2, D)	typename T2 = D, typename = hamon::enable_if_t<C<T2, T1>::value>
#define HAMON_CONSTRAINED_PARAM_D_4(C, T1, T2, T3, D)	typename T3 = D, typename = hamon::enable_if_t<C<T3, T2, T1>::value>

#endif

#endif // HAMON_CONCEPTS_DETAIL_CONSTRAINED_PARAM_HPP
