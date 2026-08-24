/**
 *	@file	unit_test_list_erase.cpp
 *
 *	@brief	erase のテスト
 *
 *	iterator erase(const_iterator position);
 *	iterator erase(const_iterator position, const_iterator last);
 */

#include <hamon/list/list.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace erase_test
{

#if !(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// VS2019でconstexprにすると内部コンパイラエラーになってしまう
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
	using Iterator = typename List::iterator;
	using ConstIterator = typename List::const_iterator;

	{
		List v;
		ConstIterator it{};
		static_assert(hamon::is_same<decltype(v.erase(it)), Iterator>::value, "");
		static_assert(hamon::is_same<decltype(v.erase(it, it)), Iterator>::value, "");
		static_assert( noexcept(v.erase(it)), "");
		static_assert( noexcept(v.erase(it, it)), "");
	}
	{
		List v{1,2,3,4,5};
		{
			auto ret = v.erase(v.begin());
			VERIFY(ret == v.begin());
			VERIFY(v.size() == 4);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == 2);
				VERIFY(*it++ == 3);
				VERIFY(*it++ == 4);
				VERIFY(*it++ == 5);
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == 5);
				VERIFY(*it++ == 4);
				VERIFY(*it++ == 3);
				VERIFY(*it++ == 2);
				VERIFY(it == v.rend());
			}
		}
		{
			auto ret = v.erase(hamon::next(v.begin(), 1));
			VERIFY(ret == hamon::next(v.begin(), 1));
			VERIFY(v.size() == 3);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == 2);
				VERIFY(*it++ == 4);
				VERIFY(*it++ == 5);
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == 5);
				VERIFY(*it++ == 4);
				VERIFY(*it++ == 2);
				VERIFY(it == v.rend());
			}
		}
		{
			auto ret = v.erase(hamon::next(v.begin(), 2));
			VERIFY(ret == hamon::next(v.begin(), 2));
			VERIFY(v.size() == 2);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == 2);
				VERIFY(*it++ == 4);
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == 4);
				VERIFY(*it++ == 2);
				VERIFY(it == v.rend());
			}
		}
		{
			auto ret = v.erase(v.begin());
			VERIFY(ret == v.begin());
			VERIFY(v.size() == 1);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == 4);
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == 4);
				VERIFY(it == v.rend());
			}
		}
		{
			auto ret = v.erase(v.begin());
			VERIFY(ret == v.end());
			VERIFY(v.size() == 0);
			VERIFY(v.begin() == v.end());
			VERIFY(v.rbegin() == v.rend());
		}
	}
	{
		List v{1,2,3,4,5};
		{
			auto ret = v.erase(v.begin(), v.end());
			VERIFY(ret == v.end());
			VERIFY(v.size() == 0);
			VERIFY(v.begin() == v.end());
			VERIFY(v.rbegin() == v.rend());
		}
	}
	{
		List v{1,2,3,4,5};
		{
			auto ret = v.erase(hamon::next(v.begin(), 1), v.end());
			VERIFY(ret == v.end());
			VERIFY(v.size() == 1);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == 1);
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == 1);
				VERIFY(it == v.rend());
			}
		}
	}
	{
		List v{1,2,3,4,5};
		{
			auto ret = v.erase(v.begin(), hamon::next(v.begin(), 3));
			VERIFY(ret == v.begin());
			VERIFY(v.size() == 2);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == 4);
				VERIFY(*it++ == 5);
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == 5);
				VERIFY(*it++ == 4);
				VERIFY(it == v.rend());
			}
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ListTest, EraseTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace erase_test

}	// namespace hamon_list_test
