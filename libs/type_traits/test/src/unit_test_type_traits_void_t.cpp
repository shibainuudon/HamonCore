/**
 *	@file	unit_test_type_traits_void_t.cpp
 *
 *	@brief	void_t のテスト
 */

#include <hamon/type_traits/void_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_type_traits_test
{

namespace void_t_test
{

// 型Tが ::type メンバを持っているかを取得する、has_type_memberを定義します
template <typename, typename = hamon::void_t<>>
struct has_type_member : hamon::false_type {};
 
template <typename T>
struct has_type_member<T, hamon::void_t<typename T::type>> : hamon::true_type {};

struct A
{
};

struct B
{
	using type = int;
};

static_assert(!has_type_member<A>::value, "");
static_assert( has_type_member<B>::value, "");

// 型Tが f1 メンバ関数を持っているか取得する
struct C
{
	int f1();
};

struct D
{
	int f2();
};

template <typename, typename = hamon::void_t<>>
struct has_f1_memfun : hamon::false_type {};

template <typename T>
struct has_f1_memfun<T, hamon::void_t<decltype(hamon::declval<T>().f1())>> : hamon::true_type {};

static_assert( has_f1_memfun<C>::value, "");
static_assert(!has_f1_memfun<D>::value, "");

// 型Tが f(int, float) メンバ関数を持っているか取得する
struct E
{
	void f(int);
};

struct F
{
	void f(int, float);
};

template <typename, typename = hamon::void_t<>>
struct has_f_memfun : hamon::false_type {};

template <typename T>
struct has_f_memfun<T, hamon::void_t<
	decltype(hamon::declval<T>().f(hamon::declval<int>(), hamon::declval<float>()))>> : hamon::true_type {};

static_assert(!has_f_memfun<E>::value, "");
static_assert( has_f_memfun<F>::value, "");

// 型Tが fun(int, T, char) と呼び出せるか取得する
struct G
{
};

struct H
{
};

int fun(int, const G&, char);

template <typename, typename = hamon::void_t<>>
struct fun_callable : hamon::false_type {};

template <typename T>
struct fun_callable<T, hamon::void_t<
	decltype(fun(hamon::declval<int>(), hamon::declval<T>(), hamon::declval<char>()))>> : hamon::true_type {};

static_assert( fun_callable<G>::value, "");
static_assert(!fun_callable<H>::value, "");
static_assert(!fun_callable<int>::value, "");

}	// namespace void_t_test

}	// namespace hamon_type_traits_test
