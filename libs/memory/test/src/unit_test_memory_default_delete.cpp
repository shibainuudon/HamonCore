/**
 *	@file	unit_test_memory_default_delete.cpp
 *
 *	@brief	default_delete のテスト
 */

#include <hamon/memory/default_delete.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace default_delete_test
{

struct A {};
struct B : A {};
struct C : A {};

static_assert( hamon::is_constructible<hamon::default_delete<A>, hamon::default_delete<A> const&>::value, "");
static_assert( hamon::is_constructible<hamon::default_delete<A>, hamon::default_delete<B> const&>::value, "");
static_assert( hamon::is_constructible<hamon::default_delete<A>, hamon::default_delete<C> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::default_delete<B>, hamon::default_delete<A> const&>::value, "");
static_assert( hamon::is_constructible<hamon::default_delete<B>, hamon::default_delete<B> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::default_delete<B>, hamon::default_delete<C> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::default_delete<C>, hamon::default_delete<A> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::default_delete<C>, hamon::default_delete<B> const&>::value, "");
static_assert( hamon::is_constructible<hamon::default_delete<C>, hamon::default_delete<C> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::default_delete<A>, hamon::default_delete<A[]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::default_delete<B>, hamon::default_delete<B[]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::default_delete<C>, hamon::default_delete<C[]> const&>::value, "");

static_assert( hamon::is_constructible<hamon::default_delete<A[]>, hamon::default_delete<A[]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::default_delete<A[]>, hamon::default_delete<B[]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::default_delete<A[]>, hamon::default_delete<C[]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::default_delete<B[]>, hamon::default_delete<A[]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::default_delete<B[]>, hamon::default_delete<B[]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::default_delete<B[]>, hamon::default_delete<C[]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::default_delete<C[]>, hamon::default_delete<A[]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::default_delete<C[]>, hamon::default_delete<B[]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::default_delete<C[]>, hamon::default_delete<C[]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::default_delete<A[]>, hamon::default_delete<A> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::default_delete<B[]>, hamon::default_delete<B> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::default_delete<C[]>, hamon::default_delete<C> const&>::value, "");

struct S
{
	bool* m_destructed;

	constexpr S(bool* p) : m_destructed(p) {}

	HAMON_CXX20_CONSTEXPR ~S() { *m_destructed = true; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

/*HAMON_CXX14_CONSTEXPR*/ bool test()
{
	{
		bool destructed = false;
		auto p = new S(&destructed);
		VERIFY(!destructed);

		hamon::default_delete<S> deleter;
		deleter(p);

		VERIFY( destructed);
	}
	{
		constexpr std::size_t num = 3;
		bool destructed[num] = {false, false, false};
		auto p = new S[num]{&destructed[0], &destructed[1], &destructed[2]};
		VERIFY(!destructed[0]);
		VERIFY(!destructed[1]);
		VERIFY(!destructed[2]);

		hamon::default_delete<S[]> deleter;
		deleter(p);

		VERIFY( destructed[0]);
		VERIFY( destructed[1]);
		VERIFY( destructed[2]);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, DefaultDeleteTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test());
}

}	// namespace default_delete_test

}	// namespace hamon_memory_test
