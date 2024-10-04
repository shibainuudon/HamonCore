/**
 *	@file	unit_test_forward_list_push_front.cpp
 *
 *	@brief	push_front のテスト
 *
 *	void push_front(const T& x);
 *	void push_front(T&& x);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace push_front_test
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

	static_assert(hamon::is_same<
		decltype(hamon::declval<ForwardList&>().push_front(hamon::declval<T const&>())),
		void
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<ForwardList&>().push_front(hamon::declval<T&&>())),
		void
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<ForwardList&>().push_front(hamon::declval<T const&>())), "");
	static_assert(!noexcept(
		hamon::declval<ForwardList&>().push_front(hamon::declval<T&&>())), "");

	{
		ForwardList v;
		VERIFY(v.empty());

		T const x(T{10});
		v.push_front(x);
		VERIFY(!v.empty());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}

		v.push_front(T{20});
		VERIFY(!v.empty());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}

		v.push_front(x);
		VERIFY(!v.empty());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}

		v.push_front(T{30});
		VERIFY(!v.empty());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{30});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, PushFrontTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
}

}	// namespace push_front_test

}	// namespace hamon_forward_list_test
