/**
 *	@file	unit_test_memory_to_address.cpp
 *
 *	@brief	to_address のテスト
 */

#include <hamon/memory/to_address.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <memory>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace to_address_test
{

class P1
{
public:
	using element_type = int;

	explicit HAMON_CONSTEXPR P1(int* p)
		: p_(p) { }

	HAMON_CONSTEXPR int* operator->() const noexcept
	{
		return p_;
	}

private:
	int* p_;
};

class P2
{
public:
	using element_type = int;

	explicit HAMON_CONSTEXPR P2(int* p)
		: p_(p) { }

	HAMON_CONSTEXPR P1 operator->() const noexcept
	{
		return p_;
	}

private:
	P1 p_;
};

class P3
{
public:
	explicit HAMON_CONSTEXPR P3(int* p)
		: p_(p) { }

	HAMON_CONSTEXPR int* get() const noexcept
	{
		return p_;
	}

private:
	int* p_;
};

class P4
{
public:
	explicit HAMON_CONSTEXPR P4(int* p)
		: p_(p) { }

	HAMON_CONSTEXPR int* operator->() const noexcept
	{
		return nullptr;
	}

	HAMON_CONSTEXPR int* get() const noexcept
	{
		return p_;
	}

private:
	int* p_;
};

}	// namespace to_address_test

}	// namespace hamon_memory_test

namespace std
{

template<>
struct pointer_traits<hamon_memory_test::to_address_test::P3>
{
	static HAMON_CONSTEXPR int*
	to_address(const hamon_memory_test::to_address_test::P3& p) noexcept
	{
		return p.get();
	}
};

template<>
struct pointer_traits<hamon_memory_test::to_address_test::P4>
{
	static HAMON_CONSTEXPR int*
	to_address(const hamon_memory_test::to_address_test::P4& p) noexcept
	{
		return p.get();
	}
};

}	// namespace std

namespace hamon_memory_test
{

namespace to_address_test
{

HAMON_CXX14_CONSTEXPR bool test1()
{
	int i = 0;
	int* p = &i;
	return (hamon::to_address(p) == &i);
}
HAMON_CXX14_CONSTEXPR bool test2()
{
	int i = 0;
	P1 p(&i);
	return (hamon::to_address(p) == &i);
}
HAMON_CXX14_CONSTEXPR bool test3()
{
	int i = 0;
	P2 p(&i);
	return (hamon::to_address(p) == &i);
}
HAMON_CXX14_CONSTEXPR bool test4()
{
	int i = 0;
	P3 p(&i);
	return (hamon::to_address(p) == &i);
}
HAMON_CXX14_CONSTEXPR bool test5()
{
	int i = 0;
	P4 p(&i);
	return (hamon::to_address(p) == &i);
}

GTEST_TEST(MemoryTest, ToAddressTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test3());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test4());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test5());
}

}	// namespace to_address_test

}	// namespace hamon_memory_test
