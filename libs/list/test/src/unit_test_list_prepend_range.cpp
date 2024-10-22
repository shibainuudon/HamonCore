/**
 *	@file	unit_test_list_prepend_range.cpp
 *
 *	@brief	prepend_range のテスト
 *
 *	template<container-compatible-range<T> R>
 *	void prepend_range(R&& rg);
 */

#include <hamon/list/list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_list_test
{

namespace prepend_range_test
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
	using Range = RangeWrapper<T>;

	{
		List v;
		Range rg;
		static_assert(hamon::is_same<decltype(v.prepend_range(rg)), void>::value, "");
		static_assert(!noexcept(v.prepend_range(rg)), "");
	}
	{
		List v;
		VERIFY(v.empty());

		{
			T a[] = {{1},{2},{3},{4}};
			Range r(a);
			v.prepend_range(r);
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
			v.prepend_range(Range(a));
			VERIFY(v.size() == 6);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == T{10});
				VERIFY(*it++ == T{20});
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
				VERIFY(*it++ == T{20});
				VERIFY(*it++ == T{10});
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

GTEST_TEST(ListTest, PrependRangeTest)
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

		v.prepend_range(t);
		EXPECT_EQ(6, MayThrow::s_instance_count);
		EXPECT_EQ(3u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(2, (it++)->value);
			EXPECT_EQ(3, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_THROW(v.prepend_range(t), MayThrow::Exception);
		EXPECT_EQ(6, MayThrow::s_instance_count);
		EXPECT_EQ(3u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
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

}	// namespace prepend_range_test

}	// namespace hamon_list_test
