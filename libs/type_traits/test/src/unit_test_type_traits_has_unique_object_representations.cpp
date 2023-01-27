/**
 *	@file	unit_test_type_traits_has_unique_object_representations.cpp
 *
 *	@brief	has_unique_object_representations のテスト
 */

#include <hamon/type_traits/has_unique_object_representations.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_HAS_UNIQUE_OBJECT_REPRESENTATIONS)

namespace hamon_type_traits_test
{

namespace has_unique_object_representations_test
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST_IMPL(b, T)	\
	static_assert(hamon::has_unique_object_representations_v<T>      == b, #T);	\
	static_assert(hamon::has_unique_object_representations<T>::value == b, #T);	\
	static_assert(hamon::has_unique_object_representations<T>()      == b, #T)

#else

#define HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST_IMPL(b, T)	\
	static_assert(hamon::has_unique_object_representations<T>::value == b, #T);	\
	static_assert(hamon::has_unique_object_representations<T>()      == b, #T)

#endif

#define HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(b, T)	\
	HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST_IMPL(b,                T);	\
	HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST_IMPL(b, const          T);	\
	HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST_IMPL(b,       volatile T);	\
	HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST_IMPL(b, const volatile T)

class Empty
{
};

class NotEmpty
{
	virtual ~NotEmpty();
};

union EmptyUnion {};

struct NonEmptyUnion { int x; unsigned y; };

struct bit_zero
{
	int : 0;
};

class Abstract
{
	virtual ~Abstract() = 0;
};

struct A
{
	~A();
	unsigned foo;
};

struct B
{
	char bar;
	int foo;
};

HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(false, void);
HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(false, Empty);
HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(false, EmptyUnion);
HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(false, NotEmpty);
HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(false, bit_zero);
HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(false, Abstract);
HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(false, B);

HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(true, unsigned);
HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(true, NonEmptyUnion);
HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(true, char[3]);
HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(true, char[]);

#undef HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST_IMPL
#undef HAMON_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST

}	// namespace has_unique_object_representations_test

}	// namespace hamon_type_traits_test

#else
#pragma message("hamon doesn't have has_unique_object_representations")
#endif
