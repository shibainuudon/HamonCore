/**
 *	@file	unit_test_forward_list_reverse.cpp
 *
 *	@brief	reverse のテスト
 *
 *	void reverse() noexcept;
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace reverse_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using ForwardList = hamon::forward_list<T>;

	{
		ForwardList v;
		static_assert(hamon::is_same<decltype(v.reverse()), void>::value, "");
		static_assert(noexcept(v.reverse()), "");
	}
	{
		ForwardList v;
		v.reverse();
		VERIFY(v.empty());
	}
	{
		ForwardList v{3};
		v.reverse();

		auto it = v.begin();
		VERIFY(*it++ == T{3});
		VERIFY(it == v.end());
	}
	{
		ForwardList v{1,2};
		v.reverse();

		auto it = v.begin();
		VERIFY(*it++ == T{2});
		VERIFY(*it++ == T{1});
		VERIFY(it == v.end());
	}
	{
		ForwardList v{2,1};
		v.reverse();

		auto it = v.begin();
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{2});
		VERIFY(it == v.end());
	}
	{
		ForwardList v{1,2,3};
		v.reverse();

		auto it = v.begin();
		VERIFY(*it++ == T{3});
		VERIFY(*it++ == T{2});
		VERIFY(*it++ == T{1});
		VERIFY(it == v.end());
	}
	{
		ForwardList v{8,7,5,9,0,1,3,2,6,4};
		v.reverse();

		auto it = v.begin();
		VERIFY(*it++ == T{4});
		VERIFY(*it++ == T{6});
		VERIFY(*it++ == T{2});
		VERIFY(*it++ == T{3});
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{0});
		VERIFY(*it++ == T{9});
		VERIFY(*it++ == T{5});
		VERIFY(*it++ == T{7});
		VERIFY(*it++ == T{8});
		VERIFY(it == v.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, ReverseTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace reverse_test

}	// namespace hamon_forward_list_test
