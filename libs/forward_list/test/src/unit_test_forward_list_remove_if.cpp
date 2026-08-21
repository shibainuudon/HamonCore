/**
 *	@file	unit_test_forward_list_remove_if.cpp
 *
 *	@brief	remove_if のテスト
 *
 *	template<class Predicate>
 *	size_type remove_if(Predicate pred);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace remove_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using ForwardList = hamon::forward_list<T>;
	using SizeType = typename ForwardList::size_type;

	{
		ForwardList v;
		auto pred = [](T x) { return x % 2 == 0; };
		static_assert(hamon::is_same<decltype(v.remove_if(pred)), SizeType>::value, "");
		static_assert(!noexcept(v.remove_if(pred)), "");
	}
	{
		ForwardList v{3,1,4,1,5};
		{
			auto ret = v.remove_if([](T x) { return x % 2 == 0; });
			VERIFY(ret == 1);

			auto it = v.begin();
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{5});
			VERIFY(it == v.end());
		}
		{
			auto ret = v.remove_if([](T x) { return x % 2 == 0; });
			VERIFY(ret == 0);

			auto it = v.begin();
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{5});
			VERIFY(it == v.end());
		}
		{
			auto ret = v.remove_if([](T x) { return x % 2 == 1; });
			VERIFY(ret == 4);
			VERIFY(v.empty());
		}
		{
			auto ret = v.remove_if([](T x) { return x % 2 == 1; });
			VERIFY(ret == 0);
			VERIFY(v.empty());
		}
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, RemoveIfTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<long>());
}

}	// namespace remove_if_test

}	// namespace hamon_forward_list_test
