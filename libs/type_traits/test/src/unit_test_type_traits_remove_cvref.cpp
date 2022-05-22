/**
 *	@file	unit_test_type_traits_remove_cvref.cpp
 *
 *	@brief	remove_cvref のテスト
 */

#include <hamon/type_traits/remove_cvref.hpp>
#include <type_traits>

namespace hamon_type_traits_test
{

namespace remove_cvref_test
{

#define HAMON_REMOVE_CVREF_TEST_IMPL(T1, T2)	\
	static_assert(std::is_same<hamon::remove_cvref<T1>::type, T2>::value, #T1 ", " #T2);	\
	static_assert(std::is_same<hamon::remove_cvref_t<T1>,     T2>::value, #T1 ", " #T2)

#define HAMON_REMOVE_CVREF_TEST(T)	\
	HAMON_REMOVE_CVREF_TEST_IMPL(               T, T);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const          T, T);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(      volatile T, T);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const volatile T, T);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(               T&, T);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const          T&, T);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(      volatile T&, T);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const volatile T&, T);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(               T&&, T);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const          T&&, T);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(      volatile T&&, T);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const volatile T&&, T);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(               T*,                T*);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const          T*, const          T*);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(      volatile T*,       volatile T*);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const volatile T*, const volatile T*);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(               T*&,                T*);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const          T*&, const          T*);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(      volatile T*&,       volatile T*);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const volatile T*&, const volatile T*);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(               T*&&,                T*);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const          T*&&, const          T*);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(      volatile T*&&,       volatile T*);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const volatile T*&&, const volatile T*);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(               T[2],                T[2]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const          T[3],                T[3]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(      volatile T[4],                T[4]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const volatile T[5],                T[5]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(               T[],                 T[]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const          T[],                 T[]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(      volatile T[],                 T[]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const volatile T[],                 T[]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(               T(*)[2],                T(*)[2]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const          T(*)[3], const          T(*)[3]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(      volatile T(*)[4],       volatile T(*)[4]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const volatile T(*)[5], const volatile T(*)[5]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(               T(&)[2],                T[2]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const          T(&)[3],                T[3]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(      volatile T(&)[4],                T[4]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const volatile T(&)[5],                T[5]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(               T(&)[],                 T[]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const          T(&)[],                 T[]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(      volatile T(&)[],                 T[]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const volatile T(&)[],                 T[]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(               T(&&)[2],               T[2]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const          T(&&)[3],               T[3]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(      volatile T(&&)[4],               T[4]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const volatile T(&&)[5],               T[5]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(               T(&&)[],                T[]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const          T(&&)[],                T[]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(      volatile T(&&)[],                T[]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(const volatile T(&&)[],                T[]);	\
	HAMON_REMOVE_CVREF_TEST_IMPL(T(T), T(T));	\
	HAMON_REMOVE_CVREF_TEST_IMPL(T(void), T(void));	\
	HAMON_REMOVE_CVREF_TEST_IMPL(void(T), void(T));	\
	HAMON_REMOVE_CVREF_TEST_IMPL(T(T, T), T(T, T))

HAMON_REMOVE_CVREF_TEST(int);
HAMON_REMOVE_CVREF_TEST(float);

struct S {};
HAMON_REMOVE_CVREF_TEST(S);

#undef HAMON_REMOVE_CVREF_TEST
#undef HAMON_REMOVE_CVREF_TEST_IMPL

}	// namespace remove_cvref_test

}	// namespace hamon_type_traits_test
