/**
 *	@file	unit_test_forward_list_insert_range_after.cpp
 *
 *	@brief	insert_range_after のテスト
 *
 *	template<container-compatible-range<T> R>
 *	iterator insert_range_after(const_iterator position, R&& rg);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_forward_list_test
{

namespace insert_range_after_test
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

template <typename T, template <typename> class RangeWrapper>
FORWARD_LIST_TEST_CONSTEXPR bool test_impl()
{
	using ForwardList = hamon::forward_list<T>;
	using Iterator = typename ForwardList::iterator;
	using ConstIterator = typename ForwardList::const_iterator;
	using Range = RangeWrapper<T>;

	{
		ForwardList v;
		ConstIterator pos;
		Range rg;
		static_assert(hamon::is_same<decltype(v.insert_range_after(pos, rg)), Iterator>::value, "");
		static_assert(!noexcept(v.insert_range_after(pos, rg)), "");
	}
	{
		ForwardList v;
		VERIFY(v.empty());

		{
			T a[] = {{1},{2},{3},{4}};
			Range r(a);
			auto ret = v.insert_range_after(v.before_begin(), r);
			VERIFY(ret == hamon::next(v.begin(), 3));
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(it == v.end());
		}
		{
			T a[] = {{10},{20}};
			auto ret = v.insert_range_after(v.begin(), Range(a));
			VERIFY(ret == hamon::next(v.begin(), 2));
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(it == v.end());
		}
	}

	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test()
{
	return
		test_impl<T, test_input_range>() &&
		test_impl<T, test_forward_range>() &&
		test_impl<T, test_bidirectional_range>() &&
		test_impl<T, test_random_access_range>() &&
		test_impl<T, test_contiguous_range>() &&
		test_impl<T, test_input_sized_range>() &&
		test_impl<T, test_forward_sized_range>() &&
		test_impl<T, test_bidirectional_sized_range>() &&
		test_impl<T, test_random_access_sized_range>() &&
		test_impl<T, test_contiguous_sized_range>();
}

#undef VERIFY

#if !defined(HAMON_NO_EXCEPTIONS)
struct MayThrow
{
	struct Exception{};

	int value;
	static int s_instance_count;
	static int s_instance_max_count;

	MayThrow() : value(0)
	{
		Ctor();
	}

	MayThrow(int v) : value(v)
	{
		Ctor();
	}

	MayThrow(MayThrow const& other)
		: value(other.value)
	{
		Ctor();
	}

	MayThrow(MayThrow&& other)
		: value(other.value)
	{
		Ctor();
	}

	~MayThrow()
	{
		--s_instance_count;
	}

private:
	void Ctor()
	{
		if (s_instance_count >= s_instance_max_count)
		{
			throw Exception{};
		}
		++s_instance_count;
	}
};

int MayThrow::s_instance_count = 0;
int MayThrow::s_instance_max_count = 0;
#endif

GTEST_TEST(ForwardListTest, InsertRangeAfterTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());

// 操作中に例外が発生した場合、副作用は発生しない
#if !defined(HAMON_NO_EXCEPTIONS)
	MayThrow::s_instance_count = 0;
	MayThrow::s_instance_max_count = 0;
	{
		MayThrow::s_instance_max_count = 8;

		hamon::forward_list<MayThrow> v;

		MayThrow const t[] {MayThrow(1), MayThrow(2), MayThrow(3)};
		EXPECT_EQ(3, MayThrow::s_instance_count);

		v.insert_range_after(v.before_begin(), t);
		EXPECT_EQ(6, MayThrow::s_instance_count);
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(2, (it++)->value);
			EXPECT_EQ(3, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_THROW(v.insert_range_after(v.before_begin(), t), MayThrow::Exception);
		EXPECT_EQ(6, MayThrow::s_instance_count);
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(2, (it++)->value);
			EXPECT_EQ(3, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		MayThrow::s_instance_max_count = 10;

		v.insert_range_after(v.begin(), t);
		EXPECT_EQ(9, MayThrow::s_instance_count);
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(2, (it++)->value);
			EXPECT_EQ(3, (it++)->value);
			EXPECT_EQ(2, (it++)->value);
			EXPECT_EQ(3, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_THROW(v.insert_range_after(v.begin(), t), MayThrow::Exception);
		EXPECT_EQ(9, MayThrow::s_instance_count);
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(2, (it++)->value);
			EXPECT_EQ(3, (it++)->value);
			EXPECT_EQ(2, (it++)->value);
			EXPECT_EQ(3, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
	EXPECT_EQ(0, MayThrow::s_instance_count);
#endif
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace insert_range_after_test

}	// namespace hamon_forward_list_test
