/**
 *	@file	unit_test_forward_list_max_size.cpp
 *
 *	@brief	max_size のテスト
 *
 *	size_type max_size() const noexcept;
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace max_size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using ForwardList = hamon::forward_list<T>;
	using SizeType = typename ForwardList::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<ForwardList const&>().max_size()), SizeType>::value, "");
	static_assert(noexcept(hamon::declval<ForwardList const&>().max_size()), "");

	{
		ForwardList const v;
		auto n = v.max_size();
		VERIFY(n > 0);
	}
	{
		ForwardList const v{1,2,3};
		auto n = v.max_size();
		VERIFY(n > 0);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, MaxSizeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace max_size_test

}	// namespace hamon_forward_list_test
