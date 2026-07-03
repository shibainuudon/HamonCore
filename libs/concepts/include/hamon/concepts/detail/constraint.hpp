/**
 *	@file	constraint.hpp
 *
 *	@brief	HAMON_CONSTRAINT マクロの定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CONSTRAINT_HPP
#define HAMON_CONCEPTS_DETAIL_CONSTRAINT_HPP

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/preprocessor/facilities/expand.hpp>
#include <hamon/preprocessor/tuple/size.hpp>
#include <hamon/preprocessor/cat.hpp>
#include <hamon/config.hpp>

#define HAMON_CONSTRAINT(C, ...)	\
	HAMON_PP_EXPAND_I(HAMON_PP_CAT(HAMON_CONSTRAINT_, HAMON_PP_TUPLE_SIZE((__VA_ARGS__)))(C, __VA_ARGS__))

#define HAMON_CONSTRAINT_D(C, ...)	\
	HAMON_PP_EXPAND_I(HAMON_PP_CAT(HAMON_CONSTRAINT_D_, HAMON_PP_TUPLE_SIZE((__VA_ARGS__)))(C, __VA_ARGS__))

#if defined(HAMON_HAS_CXX20_CONCEPTS)

#define HAMON_CONSTRAINT_1(C, T1)					C T1
#define HAMON_CONSTRAINT_2(C, T1, T2)				C<T1> T2
#define HAMON_CONSTRAINT_3(C, T1, T2, T3)			C<T1, T2> T3
#define HAMON_CONSTRAINT_4(C, T1, T2, T3, T4)		C<T1, T2, T3> T4
#define HAMON_CONSTRAINT_5(C, T1, T2, T3, T4, T5)	C<T1, T2, T3, T4> T5
#define HAMON_CONSTRAINT_D_2(C, T1, D)				C T1 = D
#define HAMON_CONSTRAINT_D_3(C, T1, T2, D)			C<T1> T2 = D
#define HAMON_CONSTRAINT_D_4(C, T1, T2, T3, D)		C<T1, T2> T3 = D

#else

#define HAMON_CONSTRAINT_1(C, T1)					typename T1, typename = hamon::enable_if_t<C<T1>>
#define HAMON_CONSTRAINT_2(C, T1, T2)				typename T2, typename = hamon::enable_if_t<C<T2, T1>>
#define HAMON_CONSTRAINT_3(C, T1, T2, T3)			typename T3, typename = hamon::enable_if_t<C<T3, T1, T2>>
#define HAMON_CONSTRAINT_4(C, T1, T2, T3, T4)		typename T4, typename = hamon::enable_if_t<C<T4, T1, T2, T3>>
#define HAMON_CONSTRAINT_5(C, T1, T2, T3, T4, T5)	typename T5, typename = hamon::enable_if_t<C<T5, T1, T2, T3, T4>>
#define HAMON_CONSTRAINT_D_2(C, T1, D)				typename T1 = D, typename = hamon::enable_if_t<C<T1>>
#define HAMON_CONSTRAINT_D_3(C, T1, T2, D)			typename T2 = D, typename = hamon::enable_if_t<C<T2, T1>>
#define HAMON_CONSTRAINT_D_4(C, T1, T2, T3, D)		typename T3 = D, typename = hamon::enable_if_t<C<T3, T1, T2>>

#endif

#endif // HAMON_CONCEPTS_DETAIL_CONSTRAINT_HPP
