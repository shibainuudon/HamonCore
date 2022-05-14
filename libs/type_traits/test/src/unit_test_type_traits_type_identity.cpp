/**
 *	@file	unit_test_type_traits_type_identity.cpp
 *
 *	@brief	type_identity のテスト
 */

#include <hamon/type_traits/type_identity.hpp>
#include <type_traits>

#define HAMON_TYPE_IDENTITY_TEST_IMPL(T)	\
	static_assert(std::is_same<hamon::type_identity<T>::type, T>::value, "");	\
	static_assert(std::is_same<hamon::type_identity_t<T>, T>::value, "");	\
	/**/

#define HAMON_TYPE_IDENTITY_TEST_IMPL_CV(T)	\
	HAMON_TYPE_IDENTITY_TEST_IMPL(T);	\
	HAMON_TYPE_IDENTITY_TEST_IMPL(const T);	\
	HAMON_TYPE_IDENTITY_TEST_IMPL(volatile T);	\
	HAMON_TYPE_IDENTITY_TEST_IMPL(const volatile T);	\
	/**/

#define HAMON_TYPE_IDENTITY_TEST(T)	\
	HAMON_TYPE_IDENTITY_TEST_IMPL_CV(T);	\
	HAMON_TYPE_IDENTITY_TEST_IMPL_CV(T&);	\
	HAMON_TYPE_IDENTITY_TEST_IMPL_CV(T&&);	\
	HAMON_TYPE_IDENTITY_TEST_IMPL_CV(T*);	\
	HAMON_TYPE_IDENTITY_TEST_IMPL_CV(T[2]);	\
	HAMON_TYPE_IDENTITY_TEST_IMPL_CV(T[]);	\
	HAMON_TYPE_IDENTITY_TEST_IMPL_CV(T(&)[2]);	\
	HAMON_TYPE_IDENTITY_TEST_IMPL_CV(T(&&)[2]);	\
	/**/

HAMON_TYPE_IDENTITY_TEST(int);
HAMON_TYPE_IDENTITY_TEST(char);
HAMON_TYPE_IDENTITY_TEST(float);
HAMON_TYPE_IDENTITY_TEST(void*);
HAMON_TYPE_IDENTITY_TEST_IMPL_CV(void);

#undef HAMON_TYPE_IDENTITY_TEST_IMPL
#undef HAMON_TYPE_IDENTITY_TEST_IMPL_CV
#undef HAMON_TYPE_IDENTITY_TEST
