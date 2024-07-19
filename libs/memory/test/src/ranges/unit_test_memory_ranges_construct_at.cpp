/**
 *	@file	unit_test_memory_ranges_construct_at.cpp
 *
 *	@brief	ranges::construct_at のテスト
 */

#include <hamon/memory/ranges/construct_at.hpp>
#include <hamon/memory/ranges/destroy_at.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace ranges_construct_at_test
{

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC)
#define MEMORY_TEST_CONSTEXPR				constexpr
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#else
#define MEMORY_TEST_CONSTEXPR
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#endif

struct S
{
	int x;
	float y;
	double z;

	static int construct_count;
	static int destruct_count;

	S() : x{}, y{}, z{}
	{
		++construct_count;
	}

	S(int x_, float y_, double z_)
		: x{ x_ }, y{ y_ }, z{ z_ }
	{
		++construct_count;
	}

	~S()
	{
		++destruct_count;
	}
};

int S::construct_count = 0;
int S::destruct_count  = 0;

struct S2
{
	int x;
	float y;
	double z;

	constexpr S2(int x_, float y_, double z_)
		: x(x_), y(y_), z(z_) {}
};

template <typename Void, typename T, typename... Args>
struct invocable_construct_at_impl
	: public hamon::false_type {};

template <typename T, typename... Args>
struct invocable_construct_at_impl<
	hamon::void_t<decltype(hamon::ranges::construct_at(hamon::declval<T*>(), hamon::declval<Args>()...))>, T, Args...>
	: public hamon::true_type {};

template <typename T, typename... Args>
using invocable_construct_at = invocable_construct_at_impl<void, T, Args...>;

static_assert( invocable_construct_at<S>::value, "");
static_assert(!invocable_construct_at<S, int>::value, "");
static_assert(!invocable_construct_at<S, int, float>::value, "");
static_assert( invocable_construct_at<S, int, float, double>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

MEMORY_TEST_CONSTEXPR bool constexpr_test()
{
	std::allocator<S2> alloc;
	S2* buf = alloc.allocate(1);
	auto p = hamon::ranges::construct_at(buf, 42, 1.5f, -2.5);
	VERIFY(p->x == 42);
	VERIFY(p->y == 1.5f);
	VERIFY(p->z == -2.5);
	hamon::ranges::destroy_at(p);
	alloc.deallocate(p, 1);
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, RangesConstructAtTest)
{
	S::construct_count = 0;
	S::destruct_count  = 0;
	{
		alignas(S) unsigned char buf[sizeof(S)];
		EXPECT_EQ(0, S::construct_count);
		EXPECT_EQ(0, S::destruct_count);
		S* ptr = hamon::ranges::construct_at(reinterpret_cast<S*>(buf));
		EXPECT_EQ(0,    ptr->x);
		EXPECT_EQ(0.0f, ptr->y);
		EXPECT_EQ(0.0,  ptr->z);
		EXPECT_EQ(1, S::construct_count);
		EXPECT_EQ(0, S::destruct_count);
		hamon::ranges::destroy_at(ptr);
		EXPECT_EQ(1, S::construct_count);
		EXPECT_EQ(1, S::destruct_count);
	}
	EXPECT_EQ(1, S::construct_count);
	EXPECT_EQ(1, S::destruct_count);

	S::construct_count = 0;
	S::destruct_count  = 0;
	{
		alignas(S) unsigned char buf[sizeof(S)];
		EXPECT_EQ(0, S::construct_count);
		EXPECT_EQ(0, S::destruct_count);
		S* ptr = hamon::ranges::construct_at(reinterpret_cast<S*>(buf), 1, 0.5f, -2.5);
		EXPECT_EQ(1,    ptr->x);
		EXPECT_EQ(0.5f, ptr->y);
		EXPECT_EQ(-2.5, ptr->z);
		EXPECT_EQ(1, S::construct_count);
		EXPECT_EQ(0, S::destruct_count);
		hamon::ranges::destroy_at(ptr);
		EXPECT_EQ(1, S::construct_count);
		EXPECT_EQ(1, S::destruct_count);
	}
	EXPECT_EQ(1, S::construct_count);
	EXPECT_EQ(1, S::destruct_count);

	{
		int x = {};
		hamon::ranges::construct_at(&x, 17);
		EXPECT_EQ(x, 17);
		hamon::ranges::destroy_at(&x);
	}

	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(constexpr_test());
}

#undef MEMORY_TEST_CONSTEXPR
#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace ranges_construct_at_test

}	// namespace hamon_memory_test
