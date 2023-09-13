/**
 *	@file	unit_test_any_emplace_init_list_args.cpp
 *
 *	@brief	emplace関数のテスト
 *
 *	template<class T, class U, class... Args>
 *	decay_t<T>& emplace(initializer_list<U> il, Args&&... args);
 */

#include <hamon/any.hpp>
#include <hamon/utility/in_place_type.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>

namespace hamon_any_test
{

namespace emplace_init_list_args_test
{

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnCtor
{
	ThrowOnCtor(std::initializer_list<int>, int)
	{
		throw 42;
	}
};
#endif

GTEST_TEST(AnyTest, EmplaceInitListArgsTest)
{
	{
		hamon::any a{};
		EXPECT_FALSE(a.has_value());

		std::allocator<int> alloc;
		a.emplace<hamon::vector<int>>({3, 1, 4, 1}, alloc);
		EXPECT_TRUE(a.has_value());
		auto const& vec = hamon::any_cast<hamon::vector<int> const&>(a);
		EXPECT_EQ(3, vec[0]);
		EXPECT_EQ(1, vec[1]);
		EXPECT_EQ(4, vec[2]);
		EXPECT_EQ(1, vec[3]);

#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW(a.emplace<ThrowOnCtor>({1, 2, 3}, 0), int);
		EXPECT_FALSE(a.has_value());
#endif
	}
}

}	// namespace emplace_init_list_args_test

}	// namespace hamon_any_test
