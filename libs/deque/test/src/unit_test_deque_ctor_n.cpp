/**
 *	@file	unit_test_deque_ctor_n.cpp
 *
 *	@brief	要素数を引数に取るコンストラクタのテスト
 *
 *	explicit deque(size_type n, const Allocator& = Allocator());
 */

#include <hamon/deque.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace ctor_n_test
{

struct S1
{
	int value;
};

HAMON_CXX11_CONSTEXPR bool operator==(S1 const& lhs, S1 const& rhs)
{
	return lhs.value == rhs.value;
}

struct S2
{
	int value;
	HAMON_CXX11_CONSTEXPR S2() : value(42) {}
};

HAMON_CXX11_CONSTEXPR bool operator==(S2 const& lhs, S2 const& rhs)
{
	return lhs.value == rhs.value;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Allocator = hamon::allocator<T>;
	using Deque = hamon::deque<T, Allocator>;
	using SizeType = typename Deque::size_type;

	static_assert( hamon::is_constructible<Deque, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Deque, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Deque, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Deque, SizeType, Allocator const&>::value, "");

	{
		Allocator alloc;
		Deque v(3, alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(v.size() == 3);
		VERIFY(!v.empty());
		VERIFY(v[0] == T{});
		VERIFY(v[1] == T{});
		VERIFY(v[2] == T{});
	}
	{
		Deque v(2);
		VERIFY(v.size() == 2);
		VERIFY(!v.empty());
		VERIFY(v[0] == T{});
		VERIFY(v[1] == T{});
	}

	return true;
}

#undef VERIFY

struct S3
{
	static int default_ctor_count;
	static int copy_ctor_count;
	static int move_ctor_count;
	static int copy_assign_count;
	static int move_assign_count;
	static int dtor_count;

	S3() noexcept
	{
		++default_ctor_count;
	}

	S3(S3 const&) noexcept
	{
		++copy_ctor_count;
	}

	S3(S3&&) noexcept
	{
		++move_ctor_count;
	}

	S3& operator=(S3 const&) noexcept
	{
		++copy_assign_count;
		return *this;
	}

	S3& operator=(S3&&) noexcept
	{
		++move_assign_count;
		return *this;
	}

	~S3() noexcept
	{
		++dtor_count;
	}

	static void Reset()
	{
		default_ctor_count = 0;
		copy_ctor_count = 0;
		move_ctor_count = 0;
		copy_assign_count = 0;
		move_assign_count = 0;
		dtor_count = 0;
	}
};

int S3::default_ctor_count = 0;
int S3::copy_ctor_count = 0;
int S3::move_ctor_count = 0;
int S3::copy_assign_count = 0;
int S3::move_assign_count = 0;
int S3::dtor_count = 0;

GTEST_TEST(DequeTest, CtorNTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());

	S3::Reset();
	{
		hamon::deque<S3> d(3);
		EXPECT_EQ(3, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(0, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(0, S3::dtor_count);
	}
	EXPECT_EQ(3, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(0, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(3, S3::dtor_count);

	S3::Reset();
	{
		hamon::deque<S3> d(100);
		EXPECT_EQ(100, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(0, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(0, S3::dtor_count);
	}
	EXPECT_EQ(100, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(0, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(100, S3::dtor_count);
}

}	// namespace ctor_n_test

}	// namespace hamon_deque_test
