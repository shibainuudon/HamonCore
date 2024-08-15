/**
 *	@file	unit_test_memory_unique_ptr_hash.cpp
 *
 *	@brief	hash のテスト
 *
 *	template<class T, class D>
 *	struct hash<unique_ptr<T, D>>;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace unique_ptr_test
{

namespace hash_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

/*HAMON_CXX14_CONSTEXPR*/
bool test()
{
	// TODO
	return true;
}

#undef VERIFY

GTEST_TEST(UniquePtrTest, HashTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test());
}

}	// namespace hash_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
