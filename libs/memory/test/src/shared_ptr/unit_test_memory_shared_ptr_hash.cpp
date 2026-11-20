/**
 *	@file	unit_test_memory_shared_ptr_hash.cpp
 *
 *	@brief	hash のテスト
 *
 *	template<class T> struct hash<shared_ptr<T>>;
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/functional/hash.hpp>
#include <gtest/gtest.h>

namespace hamon_memory_test
{
namespace shared_ptr_test
{
namespace hash_test
{

GTEST_TEST(SharedPtrTest, HashTest)
{
	using T = int;
	using SP = hamon::shared_ptr<T>;
	using Hash = hamon::hash<SP>;
	using Hash2 = hamon::hash<T*>;

	T* p1 = new T;
	T* p2 = new T;
	SP sp1{};
	SP sp2{};
	SP sp3(p1);
	SP sp4(p2);
	SP sp5(sp3);

	EXPECT_TRUE(Hash{}(sp1) == Hash{}(sp2));
	EXPECT_TRUE(Hash{}(sp1) != Hash{}(sp3));
	EXPECT_TRUE(Hash{}(sp1) == Hash2{}(nullptr));

	EXPECT_TRUE(Hash{}(sp3) != Hash{}(sp4));
	EXPECT_TRUE(Hash{}(sp3) == Hash{}(sp5));
	EXPECT_TRUE(Hash{}(sp3) == Hash2{}(p1));
	EXPECT_TRUE(Hash{}(sp3) != Hash2{}(p2));

	EXPECT_TRUE(Hash{}(sp4) != Hash2{}(p1));
	EXPECT_TRUE(Hash{}(sp4) == Hash2{}(p2));
}

}	// namespace hash_test
}	// namespace shared_ptr_test
}	// namespace hamon_memory_test
