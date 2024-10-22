/**
 *	@file	unit_test_list_insert_range.cpp
 *
 *	@brief	insert_range のテスト
 *
 *	template<container-compatible-range<T> R>
 *	iterator insert_range(const_iterator position, R&& rg);
 */

#include <hamon/list/list.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_list_test
{

namespace insert_range_test
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

template <typename T, template <typename> class RangeWrapper>
LIST_TEST_CONSTEXPR bool test_impl()
{
	using List = hamon::list<T>;
	using Iterator = typename List::iterator;
	using ConstIterator = typename List::const_iterator;
	using Range = RangeWrapper<T>;

	{
		List v;
		ConstIterator pos;
		Range rg;
		static_assert(hamon::is_same<decltype(v.insert_range(pos, rg)), Iterator>::value, "");
		static_assert(!noexcept(v.insert_range(pos, rg)), "");
	}
	{
		List v;
		VERIFY(v.empty());

		{
			T a[] = {{1},{2},{3},{4}};
			Range r(a);
			auto ret = v.insert_range(v.begin(), r);
			VERIFY(ret == v.begin());
			VERIFY(v.size() == 4);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == T{1});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{3});
				VERIFY(*it++ == T{4});
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == T{4});
				VERIFY(*it++ == T{3});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{1});
				VERIFY(it == v.rend());
			}
		}
		{
			T a[] = {{10},{20}};
			auto ret = v.insert_range(hamon::next(v.begin(), 1), Range(a));
			VERIFY(ret == hamon::next(v.begin(), 1));
			VERIFY(v.size() == 6);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == T{1});
				VERIFY(*it++ == T{10});
				VERIFY(*it++ == T{20});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{3});
				VERIFY(*it++ == T{4});
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == T{4});
				VERIFY(*it++ == T{3});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{20});
				VERIFY(*it++ == T{10});
				VERIFY(*it++ == T{1});
				VERIFY(it == v.rend());
			}
		}
		{
			T a[] = {{7},{8},{9}};
			auto ret = v.insert_range(v.end(), Range(a));
			VERIFY(ret == hamon::next(v.begin(), 6));
			VERIFY(v.size() == 9);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == T{1});
				VERIFY(*it++ == T{10});
				VERIFY(*it++ == T{20});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{3});
				VERIFY(*it++ == T{4});
				VERIFY(*it++ == T{7});
				VERIFY(*it++ == T{8});
				VERIFY(*it++ == T{9});
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == T{9});
				VERIFY(*it++ == T{8});
				VERIFY(*it++ == T{7});
				VERIFY(*it++ == T{4});
				VERIFY(*it++ == T{3});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{20});
				VERIFY(*it++ == T{10});
				VERIFY(*it++ == T{1});
				VERIFY(it == v.rend());
			}
		}
	}

	return true;
}

template <typename T>
LIST_TEST_CONSTEXPR bool test()
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

GTEST_TEST(ListTest, InsertRangeTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());

// 操作中に例外が発生した場合、副作用は発生しない
#if !defined(HAMON_NO_EXCEPTIONS)
	MayThrow::s_instance_count = 0;
	MayThrow::s_instance_max_count = 0;
	{
		MayThrow::s_instance_max_count = 8;

		hamon::list<MayThrow> v;

		MayThrow const t[] {MayThrow(1), MayThrow(2), MayThrow(3)};
		EXPECT_EQ(3, MayThrow::s_instance_count);

		v.insert_range(v.begin(), t);
		EXPECT_EQ(6, MayThrow::s_instance_count);
		EXPECT_EQ(3u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(2, (it++)->value);
			EXPECT_EQ(3, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_THROW(v.insert_range(v.begin(), t), MayThrow::Exception);
		EXPECT_EQ(6, MayThrow::s_instance_count);
		EXPECT_EQ(3u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(2, (it++)->value);
			EXPECT_EQ(3, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		MayThrow::s_instance_max_count = 10;

		v.insert_range(hamon::next(v.begin(), 1), t);
		EXPECT_EQ(9, MayThrow::s_instance_count);
		EXPECT_EQ(6u, v.size());
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

		EXPECT_THROW(v.insert_range(hamon::next(v.begin(), 1), t), MayThrow::Exception);
		EXPECT_EQ(9, MayThrow::s_instance_count);
		EXPECT_EQ(6u, v.size());
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

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace insert_range_test

}	// namespace hamon_list_test
