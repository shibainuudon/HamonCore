/**
 *	@file	unit_test_forward_list_push_front.cpp
 *
 *	@brief	push_front のテスト
 *
 *	void push_front(const T& x);
 *	void push_front(T&& x);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace push_front_test
{

#if !defined(HAMON_USE_STD_FORWARD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// MSVCでconstexprにすると内部コンパイラエラーになってしまう TODO
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             /**/
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
FORWARD_LIST_TEST_CONSTEXPR bool test()
{
	using ForwardList = hamon::forward_list<T>;

	{
		ForwardList v;
		static_assert(hamon::is_same<decltype(v.push_front(hamon::declval<T const&>())), void>::value, "");
		static_assert(hamon::is_same<decltype(v.push_front(hamon::declval<T&&>())), void>::value, "");
		static_assert(!noexcept(v.push_front(hamon::declval<T const&>())), "");
		static_assert(!noexcept(v.push_front(hamon::declval<T&&>())), "");
	}
	{
		ForwardList v;
		VERIFY(v.empty());

		T const x(T{10});
		v.push_front(x);
		VERIFY(!v.empty());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}

		v.push_front(T{20});
		VERIFY(!v.empty());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}

		v.push_front(x);
		VERIFY(!v.empty());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}

		v.push_front(T{30});
		VERIFY(!v.empty());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{30});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
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

GTEST_TEST(ForwardListTest, PushFrontTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<S1>());

// 操作中に例外が発生した場合、副作用は発生しない
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::forward_list<ThrowOnCopy> v;
		EXPECT_TRUE(v.empty());

		ThrowOnCopy const t(1);
		EXPECT_THROW(v.push_front(t), ThrowOnCopy::Exception);
		EXPECT_TRUE(v.empty());

		v.push_front(ThrowOnCopy(2));
		EXPECT_TRUE(!v.empty());
		{
			auto it = v.begin();
			EXPECT_EQ(2, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
	{
		hamon::forward_list<ThrowOnCopy> v(2);
		EXPECT_TRUE(!v.empty());

		ThrowOnCopy const t(1);
		EXPECT_THROW(v.push_front(t), ThrowOnCopy::Exception);
		EXPECT_TRUE(!v.empty());
		{
			auto it = v.begin();
			EXPECT_EQ(13, (it++)->value);
			EXPECT_EQ(13, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		v.push_front(ThrowOnCopy(2));
		EXPECT_TRUE(!v.empty());
		{
			auto it = v.begin();
			EXPECT_EQ( 2, (it++)->value);
			EXPECT_EQ(13, (it++)->value);
			EXPECT_EQ(13, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
	{
		hamon::forward_list<ThrowOnMove> v(3);
		EXPECT_TRUE(!v.empty());

		ThrowOnMove const t(1);
		v.push_front(t);
		EXPECT_TRUE(!v.empty());
		{
			auto it = v.begin();
			EXPECT_EQ( 1, (it++)->value);
			EXPECT_EQ(14, (it++)->value);
			EXPECT_EQ(14, (it++)->value);
			EXPECT_EQ(14, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_THROW(v.push_front(ThrowOnMove(2)), ThrowOnMove::Exception);
		EXPECT_TRUE(!v.empty());
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

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace push_front_test

}	// namespace hamon_forward_list_test
