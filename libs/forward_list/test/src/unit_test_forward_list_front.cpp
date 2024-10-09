/**
 *	@file	unit_test_forward_list_front.cpp
 *
 *	@brief	front のテスト
 *
 *	reference front();
 *	const_reference front() const;
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace front_test
{

struct S1
{
	int value;
};

HAMON_CXX11_CONSTEXPR bool
operator==(S1 const& lhs, S1 const& rhs)
{
	return lhs.value == rhs.value;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using ForwardList = hamon::forward_list<T>;
	using Reference = typename ForwardList::reference;
	using ConstReference = typename ForwardList::const_reference;

	static_assert(hamon::is_same<decltype(hamon::declval<ForwardList&>().front()), Reference>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<ForwardList const&>().front()), ConstReference>::value, "");

#if 0
	static_assert(!noexcept(hamon::declval<ForwardList&>().front()), "");
	static_assert(!noexcept(hamon::declval<ForwardList const&>().front()), "");
#endif

	{
		ForwardList v{T{1},T{2},T{3}};
		VERIFY(v.front() == T{1});

		v.front() = T{42};

		VERIFY(*v.begin() == T{42});
	}
	{
		ForwardList const v{T{10},T{20},T{30}};
		VERIFY(v.front() == T{10});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, FrontTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
}

}	// namespace front_test

}	// namespace hamon_forward_list_test
