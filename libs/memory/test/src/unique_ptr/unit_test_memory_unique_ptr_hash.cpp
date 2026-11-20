/**
 *	@file	unit_test_memory_unique_ptr_hash.cpp
 *
 *	@brief	hash のテスト
 *
 *	template<class T, class D>
 *	struct hash<unique_ptr<T, D>>;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{
namespace unique_ptr_test
{
namespace hash_test
{

template <typename T>
using invoke_hash = decltype(hamon::hash<T>{}(hamon::declval<T const&>()));

struct Deleter1
{
	using pointer = int*;
};

struct Deleter2
{
	struct pointer{};
};

struct Deleter3
{
	struct pointer
	{
		HAMON_CXX14_CONSTEXPR operator bool() const { return false; }
	};

	HAMON_CXX14_CONSTEXPR void operator()(pointer) const {}
};

}	// namespace hash_test
}	// namespace unique_ptr_test
}	// namespace hamon_memory_test

template <>
struct hamon::hash<hamon_memory_test::unique_ptr_test::hash_test::Deleter3::pointer>
{
	HAMON_CXX14_CONSTEXPR hamon::size_t
	operator()(hamon_memory_test::unique_ptr_test::hash_test::Deleter3::pointer) const
	{
		return 42;
	}
};

namespace hamon_memory_test
{
namespace unique_ptr_test
{
namespace hash_test
{
static_assert( hamon::is_detected<invoke_hash, hamon::unique_ptr<int>>::value, "");
static_assert( hamon::is_detected<invoke_hash, hamon::unique_ptr<int, Deleter1>>::value, "");
static_assert(!hamon::is_detected<invoke_hash, hamon::unique_ptr<int, Deleter2>>::value, "");
static_assert( hamon::is_detected<invoke_hash, hamon::unique_ptr<int, Deleter3>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// hash<D::pointer> が constexpr なら、
// hash<unique_ptr<T, D>> も constexpr にできる。
HAMON_CXX20_CONSTEXPR bool constexpr_test()
{
	using UP = hamon::unique_ptr<int, Deleter3>;
	using Hash = hamon::hash<UP>;

	UP up(Deleter3::pointer{});
	VERIFY(Hash{}(up) == 42);

	return true;
}

#undef VERIFY

GTEST_TEST(UniquePtrTest, HashTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(constexpr_test());

	{
		using T = int;
		using UP = hamon::unique_ptr<T>;
		using Hash = hamon::hash<UP>;
		using Hash2 = hamon::hash<T*>;

		T* p1 = new T;
		T* p2 = new T;
		UP up1{};
		UP up2{};
		UP up3(p1);
		UP up4(p2);

		EXPECT_TRUE(Hash{}(up1) == Hash{}(up2));
		EXPECT_TRUE(Hash{}(up1) != Hash{}(up3));
		EXPECT_TRUE(Hash{}(up1) == Hash2{}(nullptr));
		EXPECT_TRUE(Hash{}(up3) != Hash{}(up4));
		EXPECT_TRUE(Hash{}(up3) == Hash2{}(p1));
		EXPECT_TRUE(Hash{}(up4) == Hash2{}(p2));
	}
}

}	// namespace hash_test
}	// namespace unique_ptr_test
}	// namespace hamon_memory_test
