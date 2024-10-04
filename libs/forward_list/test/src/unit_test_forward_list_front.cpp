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

#if !defined(HAMON_USE_STD_FORWARD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// MSVCでconstexprにすると内部コンパイラエラーになってしまう TODO
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             /**/
#endif

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
FORWARD_LIST_TEST_CONSTEXPR bool test()
{
	using ForwardList = hamon::forward_list<T>;
	using Reference = typename ForwardList::reference;
	using ConstReference = typename ForwardList::const_reference;

	{
		ForwardList v;
		ForwardList const cv;
		static_assert(hamon::is_same<decltype(v.front()), Reference>::value, "");
		static_assert(hamon::is_same<decltype(cv.front()), ConstReference>::value, "");
#if !defined(HAMON_USE_STD_FORWARD_LIST)
		static_assert( noexcept(v.front()), "");
		static_assert( noexcept(cv.front()), "");
#endif
	}
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
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<S1>());
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace front_test

}	// namespace hamon_forward_list_test
