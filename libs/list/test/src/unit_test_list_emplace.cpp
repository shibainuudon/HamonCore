/**
 *	@file	unit_test_list_emplace.cpp
 *
 *	@brief	emplace のテスト
 *
 *	template<class... Args> iterator emplace(const_iterator position, Args&&... args);
 */

#include <hamon/list/list.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace emplace_test
{

#if !defined(HAMON_USE_STD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// VS2019でconstexprにすると内部コンパイラエラーになってしまう
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             /**/
#endif

struct Vector3
{
	int x;
	int y;
	int z;

	HAMON_CXX11_CONSTEXPR
	Vector3(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
};

HAMON_CXX11_CONSTEXPR bool
operator==(Vector3 const& lhs, Vector3 const& rhs)
{
	return
		lhs.x == rhs.x &&
		lhs.y == rhs.y &&
		lhs.z == rhs.z;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
LIST_TEST_CONSTEXPR bool test1()
{
	using List = hamon::list<T>;
	using Iterator = typename List::iterator;
	using ConstIterator = typename List::const_iterator;

	{
		List v;
		ConstIterator it;
		static_assert(hamon::is_same<decltype(v.emplace(it)), Iterator>::value, "");
		static_assert(hamon::is_same<decltype(v.emplace(it, hamon::declval<T>())), Iterator>::value, "");
		static_assert(!noexcept(v.emplace(it)), "");
		static_assert(!noexcept(v.emplace(it, hamon::declval<T>())), "");
	}

	List v;
	VERIFY(v.empty());

	{
		auto r = v.emplace(v.begin(), T{10});
		VERIFY(r == v.begin());
		VERIFY(v.size() == 1);
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
	}
	{
		auto r = v.emplace(v.begin(), T{20});
		VERIFY(r == v.begin());
		VERIFY(v.size() == 2);
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
	}
	{
		auto r = v.emplace(v.end(), T{30});
		VERIFY(r == hamon::next(v.begin(), 2));
		VERIFY(v.size() == 3);
		{
			auto it = v.begin();
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{30});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{30});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(it == v.rend());
		}
	}
	{
		auto r = v.emplace(hamon::next(v.begin(), 2), T{40});
		VERIFY(r == hamon::next(v.begin(), 2));
		VERIFY(v.size() == 4);
		{
			auto it = v.begin();
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{40});
			VERIFY(*it++ == T{30});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{30});
			VERIFY(*it++ == T{40});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(it == v.rend());
		}
	}

	return true;
}

LIST_TEST_CONSTEXPR bool test2()
{
	hamon::list<Vector3> v;
	VERIFY(v.empty());

	{
		auto r = v.emplace(v.begin(), 1,2,3);
		VERIFY(r == v.begin());
		VERIFY(!v.empty());
		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(*it++ == Vector3{1,2,3});
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

GTEST_TEST(ListTest, EmplaceTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2());

#if !defined(HAMON_NO_EXCEPTIONS)
	// 操作中に例外が発生した場合、副作用は発生しない
	{
		hamon::list<MayThrow> v;
		EXPECT_TRUE(v.empty());

		v.emplace(v.begin(), 2);
		EXPECT_EQ(1u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(2, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_THROW(v.emplace(v.begin(), -2), MayThrow::Exception);
		EXPECT_EQ(1u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(2, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		v.emplace(v.begin(), 3);
		EXPECT_EQ(2u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(3, (it++)->value);
			EXPECT_EQ(2, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_THROW(v.emplace(v.begin(), -3), MayThrow::Exception);
		EXPECT_EQ(2u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(3, (it++)->value);
			EXPECT_EQ(2, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
	{
		hamon::list<MayThrow> v;
		EXPECT_TRUE(v.empty());

		EXPECT_THROW(v.emplace(v.begin(), -1), MayThrow::Exception);
		EXPECT_TRUE(v.empty());

		v.emplace(v.begin(), 3);
		EXPECT_EQ(1u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(3, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
#endif
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace emplace_test

}	// namespace hamon_list_test
