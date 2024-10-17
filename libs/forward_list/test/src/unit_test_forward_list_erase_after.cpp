/**
 *	@file	unit_test_forward_list_erase_after.cpp
 *
 *	@brief	erase_after のテスト
 *
 *	iterator erase_after(const_iterator position);
 *	iterator erase_after(const_iterator position, const_iterator last);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace erase_after_test
{

#if !defined(HAMON_USE_STD_FORWARD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// MSVCでconstexprにすると内部コンパイラエラーになってしまう TODO
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test()
{
	using ForwardList = hamon::forward_list<T>;
	using Iterator = typename ForwardList::iterator;
	using ConstIterator = typename ForwardList::const_iterator;

	{
		ForwardList v;
		ConstIterator it{};
		static_assert(hamon::is_same<decltype(v.erase_after(it)), Iterator>::value, "");
		static_assert(hamon::is_same<decltype(v.erase_after(it, it)), Iterator>::value, "");
#if !defined(HAMON_USE_STD_FORWARD_LIST)
		static_assert( noexcept(v.erase_after(it)), "");
		static_assert( noexcept(v.erase_after(it, it)), "");
#endif
	}
	{
		ForwardList v{1,2,3,4,5};

		{
			auto ret = v.erase_after(v.before_begin());
			VERIFY(ret == v.begin());

			auto it = v.begin();
			VERIFY(*it++ == 2);
			VERIFY(*it++ == 3);
			VERIFY(*it++ == 4);
			VERIFY(*it++ == 5);
			VERIFY(it == v.end());
		}

		{
			auto ret = v.erase_after(v.begin());
			VERIFY(ret == hamon::next(v.begin(), 1));

			auto it = v.begin();
			VERIFY(*it++ == 2);
			VERIFY(*it++ == 4);
			VERIFY(*it++ == 5);
			VERIFY(it == v.end());
		}

		{
			auto ret = v.erase_after(hamon::next(v.begin(), 1));
			VERIFY(ret == hamon::next(v.begin(), 2));

			auto it = v.begin();
			VERIFY(*it++ == 2);
			VERIFY(*it++ == 4);
			VERIFY(it == v.end());
		}

		{
			auto ret = v.erase_after(v.before_begin());
			VERIFY(ret == v.begin());

			auto it = v.begin();
			VERIFY(*it++ == 4);
			VERIFY(it == v.end());
		}

		{
			auto ret = v.erase_after(v.before_begin());
			VERIFY(ret == v.end());
			VERIFY(v.empty());
		}
	}
	{
		ForwardList v{1,2,3,4,5};

		{
			auto ret = v.erase_after(v.before_begin(), hamon::next(v.begin(), 2));
			VERIFY(ret == v.begin());

			auto it = v.begin();
			VERIFY(*it++ == 3);
			VERIFY(*it++ == 4);
			VERIFY(*it++ == 5);
			VERIFY(it == v.end());
		}
	}
	{
		ForwardList v{1,2,3,4,5};

		{
			auto ret = v.erase_after(v.begin(), v.end());
			VERIFY(ret == v.end());

			auto it = v.begin();
			VERIFY(*it++ == 1);
			VERIFY(it == v.end());
		}
	}
	{
		ForwardList v{1,2,3,4,5};

		{
			auto ret = v.erase_after(v.before_begin(), v.end());
			VERIFY(ret == v.end());
			VERIFY(v.empty());
		}
		{
			auto ret = v.erase_after(v.before_begin(), v.end());
			VERIFY(ret == v.end());
			VERIFY(v.empty());
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, EraseAfterTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace erase_after_test

}	// namespace hamon_forward_list_test
