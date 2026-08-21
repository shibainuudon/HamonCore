/**
 *	@file	unit_test_forward_list_resize.cpp
 *
 *	@brief	resize のテスト
 *
 *	void resize(size_type sz);
 *	void resize(size_type sz, const value_type& c);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace resize_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using ForwardList = hamon::forward_list<T>;
	using SizeType = typename ForwardList::size_type;

	{
		ForwardList v;
		SizeType sz;
		T const c{};
		static_assert(hamon::is_same<decltype(v.resize(sz)), void>::value, "");
		static_assert(hamon::is_same<decltype(v.resize(sz, c)), void>::value, "");
		static_assert(!noexcept(v.resize(sz)), "");
		static_assert(!noexcept(v.resize(sz, c)), "");
	}
	{
		ForwardList v;
		VERIFY(v.empty());

		v.resize(3);
		{
			auto it = v.begin();
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(it == v.end());
		}

		v.resize(3);
		{
			auto it = v.begin();
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(it == v.end());
		}

		v.resize(5);
		{
			auto it = v.begin();
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(it == v.end());
		}

		v.resize(0);
		VERIFY(v.empty());
	}
	{
		ForwardList v;
		VERIFY(v.empty());

		v.resize(3, T{10});
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}

		v.resize(5, T{20});
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{20});
			VERIFY(it == v.end());
		}

		v.resize(5, T{99});
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{20});
			VERIFY(it == v.end());
		}

		v.resize(4, T{30});
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(it == v.end());
		}

		v.resize(0, T{40});
		VERIFY(v.empty());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, ResizeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace resize_test

}	// namespace hamon_forward_list_test
