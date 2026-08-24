/**
 *	@file	unit_test_unordered_multiset_hash_function.cpp
 *
 *	@brief	hash_function のテスト
 *
 *	constexpr hasher hash_function() const;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multiset_test_helper.hpp"

namespace hamon_unordered_multiset_test
{

namespace hash_function_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key, TestHash<Key>>;
	using Hasher = typename Set::hasher;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().hash_function()), Hasher>::value, "");
	static_assert( noexcept(hamon::declval<Set const&>().hash_function()), "");

	Hasher h1{42};
	Hasher h2{43};
	{
		Set v{17, h1};
		VERIFY(v.hash_function() == h1);
		VERIFY(v.hash_function() != h2);
	}
	{
		Set v{17, h2};
		VERIFY(v.hash_function() != h1);
		VERIFY(v.hash_function() == h2);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, HashFunctionTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace hash_function_test

}	// namespace hamon_unordered_multiset_test
