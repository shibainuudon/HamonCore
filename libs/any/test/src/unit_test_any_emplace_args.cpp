/**
 *	@file	unit_test_any_emplace_args.cpp
 *
 *	@brief	emplace関数のテスト
 *
 *	template<class T, class... Args>
 *	decay_t<T>& emplace(Args&&... args);
 */

#include <hamon/any.hpp>
#include <hamon/utility/in_place_type.hpp>
#include <gtest/gtest.h>
#include <string>

namespace hamon_any_test
{

namespace emplace_args_test
{

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnCtor
{
	ThrowOnCtor(int)
	{
		throw 42;
	}
};
#endif

GTEST_TEST(AnyTest, EmplaceArgsTest)
{
	{
		hamon::any a{};
		EXPECT_FALSE(a.has_value());

		a.emplace<int>(43);
		EXPECT_TRUE(a.has_value());
		EXPECT_EQ(43, hamon::any_cast<int>(a));

		a.emplace<std::string>(4u, 'A');
		EXPECT_TRUE(a.has_value());
		EXPECT_EQ("AAAA", hamon::any_cast<std::string>(a));

#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW(a.emplace<ThrowOnCtor>(0), int);
		EXPECT_FALSE(a.has_value());
#endif
	}
}

}	// namespace emplace_args_test

}	// namespace hamon_any_test
