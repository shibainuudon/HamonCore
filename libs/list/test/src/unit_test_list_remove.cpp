/**
 *	@file	unit_test_list_remove.cpp
 *
 *	@brief	remove のテスト
 *
 *	size_type remove(const T& value);
 */

#include <hamon/list/list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace remove_test
{

#if !defined(HAMON_USE_STD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// VS2019でconstexprにすると内部コンパイラエラーになってしまう
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
LIST_TEST_CONSTEXPR bool test()
{
	using List = hamon::list<T>;
	using SizeType = typename List::size_type;

	{
		List v;
		T const value{};
		static_assert(hamon::is_same<decltype(v.remove(value)), SizeType>::value, "");
		static_assert(!noexcept(v.remove(value)), "");
	}
	{
		List v{3,1,4,1,5};
		{
			auto ret = v.remove(1);
			VERIFY(ret == 2);
			VERIFY(v.size() == 3);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == T{3});
				VERIFY(*it++ == T{4});
				VERIFY(*it++ == T{5});
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == T{5});
				VERIFY(*it++ == T{4});
				VERIFY(*it++ == T{3});
				VERIFY(it == v.rend());
			}
		}
		{
			auto ret = v.remove(1);
			VERIFY(ret == 0);
			VERIFY(v.size() == 3);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == T{3});
				VERIFY(*it++ == T{4});
				VERIFY(*it++ == T{5});
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == T{5});
				VERIFY(*it++ == T{4});
				VERIFY(*it++ == T{3});
				VERIFY(it == v.rend());
			}
		}
		{
			auto ret = v.remove(3);
			VERIFY(ret == 1);
			VERIFY(v.size() == 2);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == T{4});
				VERIFY(*it++ == T{5});
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == T{5});
				VERIFY(*it++ == T{4});
				VERIFY(it == v.rend());
			}
		}
		{
			auto ret = v.remove(5);
			VERIFY(ret == 1);
			VERIFY(v.size() == 1);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == T{4});
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == T{4});
				VERIFY(it == v.rend());
			}
		}
		{
			auto ret = v.remove(4);
			VERIFY(ret == 1);
			VERIFY(v.empty());
			VERIFY(v.size() == 0);
			VERIFY(v.begin() == v.end());
			VERIFY(v.rbegin() == v.rend());
		}
		{
			auto ret = v.remove(0);
			VERIFY(ret == 0);
			VERIFY(v.empty());
			VERIFY(v.size() == 0);
			VERIFY(v.begin() == v.end());
			VERIFY(v.rbegin() == v.rend());
		}
	}
	{
		List v{1,1,1,2,2};
		{
			auto ret = v.remove(1);
			VERIFY(ret == 3);
			VERIFY(v.size() == 2);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == 2);
				VERIFY(*it++ == 2);
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == 2);
				VERIFY(*it++ == 2);
				VERIFY(it == v.rend());
			}
		}
		{
			auto ret = v.remove(2);
			VERIFY(ret == 2);
			VERIFY(v.empty());
			VERIFY(v.size() == 0);
			VERIFY(v.begin() == v.end());
			VERIFY(v.rbegin() == v.rend());
		}
	}
	{
		List v{1,1,1,2,2};
		{
			auto ret = v.remove(2);
			VERIFY(ret == 2);
			VERIFY(v.size() == 3);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == 1);
				VERIFY(*it++ == 1);
				VERIFY(*it++ == 1);
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == 1);
				VERIFY(*it++ == 1);
				VERIFY(*it++ == 1);
				VERIFY(it == v.rend());
			}
		}
		{
			auto ret = v.remove(1);
			VERIFY(ret == 3);
			VERIFY(v.empty());
			VERIFY(v.size() == 0);
			VERIFY(v.begin() == v.end());
			VERIFY(v.rbegin() == v.rend());
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ListTest, RemoveTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace remove_test

}	// namespace hamon_list_test
