/**
 *	@file	unit_test_forward_list_remove.cpp
 *
 *	@brief	remove のテスト
 *
 *	size_type remove(const T& value);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace remove_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using ForwardList = hamon::forward_list<T>;
	using SizeType = typename ForwardList::size_type;

	{
		ForwardList v;
		T const value{};
		static_assert(hamon::is_same<decltype(v.remove(value)), SizeType>::value, "");
		static_assert(!noexcept(v.remove(value)), "");
	}
	{
		ForwardList v{3,1,4,1,5};
		{
			auto ret = v.remove(1);
			VERIFY(ret == 2);

			auto it = v.begin();
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v.end());
		}
		{
			auto ret = v.remove(1);
			VERIFY(ret == 0);

			auto it = v.begin();
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v.end());
		}
		{
			auto ret = v.remove(3);
			VERIFY(ret == 1);

			auto it = v.begin();
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v.end());
		}
		{
			auto ret = v.remove(5);
			VERIFY(ret == 1);

			auto it = v.begin();
			VERIFY(*it++ == T{4});
			VERIFY(it == v.end());
		}
		{
			auto ret = v.remove(4);
			VERIFY(ret == 1);
			VERIFY(v.empty());
		}
		{
			auto ret = v.remove(0);
			VERIFY(ret == 0);
			VERIFY(v.empty());
		}
	}
	{
		ForwardList v{1,1,1,2,2};
		{
			auto ret = v.remove(1);
			VERIFY(ret == 3);

			auto it = v.begin();
			VERIFY(*it++ == 2);
			VERIFY(*it++ == 2);
			VERIFY(it == v.end());
		}
		{
			auto ret = v.remove(2);
			VERIFY(ret == 2);
			VERIFY(v.empty());
		}
	}
	{
		ForwardList v{1,1,1,2,2};
		{
			auto ret = v.remove(2);
			VERIFY(ret == 2);

			auto it = v.begin();
			VERIFY(*it++ == 1);
			VERIFY(*it++ == 1);
			VERIFY(*it++ == 1);
			VERIFY(it == v.end());
		}
		{
			auto ret = v.remove(1);
			VERIFY(ret == 3);
			VERIFY(v.empty());
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, RemoveTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace remove_test

}	// namespace hamon_forward_list_test
