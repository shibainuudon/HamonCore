/**
 *	@file	unit_test_list_push_front.cpp
 *
 *	@brief	push_front のテスト
 *
 *	void push_front(const T& x);
 *	void push_front(T&& x);
 */

#include <hamon/list/list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace push_front_test
{

#if !defined(HAMON_USE_STD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// VS2019でconstexprにすると内部コンパイラエラーになってしまう
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             /**/
#endif

struct S1
{
	int value;
};

HAMON_CXX11_CONSTEXPR bool
operator==(S1 const& lhs, S1 const& rhs)
{
	return lhs.value == rhs.value;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
LIST_TEST_CONSTEXPR bool test()
{
	using List = hamon::list<T>;

	{
		List v;
		static_assert(hamon::is_same<decltype(v.push_front(hamon::declval<T const&>())), void>::value, "");
		static_assert(hamon::is_same<decltype(v.push_front(hamon::declval<T&&>())), void>::value, "");
		static_assert(!noexcept(v.push_front(hamon::declval<T const&>())), "");
		static_assert(!noexcept(v.push_front(hamon::declval<T&&>())), "");
	}
	{
		List v;
		VERIFY(v.empty());

		T const x(T{10});
		v.push_front(x);
		VERIFY(v.size() == 1);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{10});
			VERIFY(it == v.rend());
		}

		v.push_front(T{20});
		VERIFY(v.size() == 2);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(it == v.rend());
		}

		v.push_front(x);
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.rend());
		}

		v.push_front(T{30});
		VERIFY(v.size() == 4);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{30});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{30});
			VERIFY(it == v.rend());
		}
	}
	return true;
}

#undef VERIFY

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnCopy
{
	struct Exception{};

	int value;

	ThrowOnCopy() : value(13)
	{
	}

	ThrowOnCopy(int v) : value(v)
	{
	}

	ThrowOnCopy(ThrowOnCopy const&)
	{
		throw Exception{};
	}

	ThrowOnCopy(ThrowOnCopy&& other) noexcept
		: value(other.value)
	{
	}
};

struct ThrowOnMove
{
	struct Exception{};

	int value;

	ThrowOnMove() : value(14)
	{
	}

	ThrowOnMove(int v) : value(v)
	{
	}

	ThrowOnMove(ThrowOnMove const& other)
		: value(other.value)
	{
	}

	ThrowOnMove(ThrowOnMove&&)
	{
		throw Exception{};
	}
};
#endif

GTEST_TEST(ListTest, PushFrontTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<S1>());

// 操作中に例外が発生した場合、副作用は発生しない
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::list<ThrowOnCopy> v;
		EXPECT_TRUE(v.empty());

		ThrowOnCopy const t(1);
		EXPECT_THROW(v.push_front(t), ThrowOnCopy::Exception);
		EXPECT_TRUE(v.empty());

		v.push_front(ThrowOnCopy(2));
		EXPECT_EQ(1u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(2, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
	{
		hamon::list<ThrowOnCopy> v(2);
		EXPECT_EQ(2u, v.size());

		ThrowOnCopy const t(1);
		EXPECT_THROW(v.push_front(t), ThrowOnCopy::Exception);
		EXPECT_EQ(2u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(13, (it++)->value);
			EXPECT_EQ(13, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		v.push_front(ThrowOnCopy(2));
		EXPECT_EQ(3u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ( 2, (it++)->value);
			EXPECT_EQ(13, (it++)->value);
			EXPECT_EQ(13, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
	{
		hamon::list<ThrowOnMove> v(3);
		EXPECT_EQ(3u, v.size());

		ThrowOnMove const t(1);
		v.push_front(t);
		EXPECT_EQ(4u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ( 1, (it++)->value);
			EXPECT_EQ(14, (it++)->value);
			EXPECT_EQ(14, (it++)->value);
			EXPECT_EQ(14, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_THROW(v.push_front(ThrowOnMove(2)), ThrowOnMove::Exception);
		EXPECT_EQ(4u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ( 1, (it++)->value);
			EXPECT_EQ(14, (it++)->value);
			EXPECT_EQ(14, (it++)->value);
			EXPECT_EQ(14, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
#endif
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace push_front_test

}	// namespace hamon_list_test
