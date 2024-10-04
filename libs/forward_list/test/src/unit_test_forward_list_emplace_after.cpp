/**
 *	@file	unit_test_forward_list_emplace_after.cpp
 *
 *	@brief	emplace_after のテスト
 *
 *	template<class... Args>
 *	iterator emplace_after(const_iterator position, Args&&... args);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace emplace_after_test
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
FORWARD_LIST_TEST_CONSTEXPR bool test1()
{
	using ForwardList = hamon::forward_list<T>;
	using Iterator = typename ForwardList::iterator;
	using ConstIterator = typename ForwardList::const_iterator;

	{
		ForwardList v;
		ConstIterator it;
		static_assert(hamon::is_same<decltype(v.emplace_after(it)), Iterator>::value, "");
		static_assert(hamon::is_same<decltype(v.emplace_after(it, T{})), Iterator>::value, "");
		static_assert(!noexcept(v.emplace_after(it)), "");
		static_assert(!noexcept(v.emplace_after(it, T{})), "");
	}

	ForwardList v;
	VERIFY(v.empty());

	{
		auto r = v.emplace_after(v.before_begin(), T{10});
		VERIFY(r == v.begin());
		auto it = v.begin();
		VERIFY(*it++ == T{10});
		VERIFY(it == v.end());
	}
	{
		auto r = v.emplace_after(v.begin(), T{20});
		VERIFY(r == hamon::next(v.begin(), 1));
		auto it = v.begin();
		VERIFY(*it++ == T{10});
		VERIFY(*it++ == T{20});
		VERIFY(it == v.end());
	}
	{
		auto r = v.emplace_after(v.begin(), T{30});
		VERIFY(r == hamon::next(v.begin(), 1));
		auto it = v.begin();
		VERIFY(*it++ == T{10});
		VERIFY(*it++ == T{30});
		VERIFY(*it++ == T{20});
		VERIFY(it == v.end());
	}

	return true;
}

#undef VERIFY

#if !defined(HAMON_NO_EXCEPTIONS)
struct MayThrow
{
	struct Exception{};

	int value;

	MayThrow(int v) : value(v)
	{
		if (v < 0)
		{
			throw Exception{};
		}
	}
};
#endif

GTEST_TEST(ForwardListTest, EmplaceAfterTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

#if !defined(HAMON_NO_EXCEPTIONS)
	// 操作中に例外が発生した場合、副作用は発生しない
	{
		hamon::forward_list<MayThrow> v;
		EXPECT_TRUE(v.empty());

		v.emplace_after(v.before_begin(), 2);
		EXPECT_TRUE(!v.empty());
		{
			auto it = v.begin();
			EXPECT_EQ(2, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_THROW(v.emplace_after(v.before_begin(), -2), MayThrow::Exception);
		{
			auto it = v.begin();
			EXPECT_EQ(2, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		v.emplace_after(v.begin(), 3);
		{
			auto it = v.begin();
			EXPECT_EQ(2, (it++)->value);
			EXPECT_EQ(3, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_THROW(v.emplace_after(v.begin(), -3), MayThrow::Exception);
		{
			auto it = v.begin();
			EXPECT_EQ(2, (it++)->value);
			EXPECT_EQ(3, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
	{
		hamon::forward_list<MayThrow> v;
		EXPECT_TRUE(v.empty());

		EXPECT_THROW(v.emplace_after(v.before_begin(), -1), MayThrow::Exception);
		EXPECT_TRUE(v.empty());

		v.emplace_after(v.before_begin(), 3);
		EXPECT_TRUE(!v.empty());
		{
			auto it = v.begin();
			EXPECT_EQ(3, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
#endif
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace emplace_after_test

}	// namespace hamon_forward_list_test
