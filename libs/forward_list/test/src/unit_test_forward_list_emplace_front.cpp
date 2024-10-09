/**
 *	@file	unit_test_forward_list_emplace_front.cpp
 *
 *	@brief	emplace_front のテスト
 *
 *	template<class... Args>
 *	reference emplace_front(Args&&... args);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace emplace_front_test
{

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
HAMON_CXX20_CONSTEXPR bool test1()
{
	using ForwardList = hamon::forward_list<T>;
	//using Reference = typename ForwardList::reference;

	ForwardList v;

//	static_assert(hamon::is_same<decltype(v.emplace_front()), Reference>::value, "");
//	static_assert(hamon::is_same<decltype(v.emplace_front(hamon::declval<T>())), Reference>::value, "");

	static_assert(!noexcept(v.emplace_front()), "");
	static_assert(!noexcept(v.emplace_front(hamon::declval<T>())), "");

	VERIFY(v.empty());

	{
		/*auto& r =*/ v.emplace_front(T{10});
		//VERIFY(&r == &v.front());
		VERIFY(!v.empty());
		auto it = v.begin();
		VERIFY(*it++ == T{10});
		VERIFY(it == v.end());
	}
	{
		/*auto& r =*/ v.emplace_front(T{20});
		//VERIFY(&r == &v.front());
		VERIFY(!v.empty());
		auto it = v.begin();
		VERIFY(*it++ == T{20});
		VERIFY(*it++ == T{10});
		VERIFY(it == v.end());
	}

	return true;
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	hamon::forward_list<Vector3> v;
	VERIFY(v.empty());

	{
		/*auto& r =*/ v.emplace_front(1,2,3);
		//VERIFY(&r == &v.front());
		VERIFY(!v.empty());
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

GTEST_TEST(ForwardListTest, EmplaceFrontTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());

#if !defined(HAMON_NO_EXCEPTIONS)
	// 操作中に例外が発生した場合、副作用は発生しない
	{
		hamon::forward_list<MayThrow> v;
		EXPECT_TRUE(v.empty());

		v.emplace_front(2);
		EXPECT_TRUE(!v.empty());
		{
			auto it = v.begin();
			EXPECT_EQ(2, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_THROW(v.emplace_front(-2), MayThrow::Exception);
		EXPECT_TRUE(!v.empty());
		{
			auto it = v.begin();
			EXPECT_EQ(2, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
	{
		hamon::forward_list<MayThrow> v;
		EXPECT_TRUE(v.empty());

		EXPECT_THROW(v.emplace_front(-1), MayThrow::Exception);
		EXPECT_TRUE(v.empty());

		v.emplace_front(3);
		EXPECT_TRUE(!v.empty());
		{
			auto it = v.begin();
			EXPECT_EQ(3, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
	{
		hamon::forward_list<ThrowOnCopy> v;
		EXPECT_TRUE(v.empty());

		ThrowOnCopy const t(1);
		EXPECT_THROW(v.emplace_front(t), ThrowOnCopy::Exception);
		EXPECT_TRUE(v.empty());

		v.emplace_front(ThrowOnCopy(2));
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
		EXPECT_THROW(v.emplace_front(t), ThrowOnCopy::Exception);
		EXPECT_TRUE(!v.empty());
		{
			auto it = v.begin();
			EXPECT_EQ(13, (it++)->value);
			EXPECT_EQ(13, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		v.emplace_front(ThrowOnCopy(2));
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
		v.emplace_front(t);
		EXPECT_TRUE(!v.empty());
		{
			auto it = v.begin();
			EXPECT_EQ( 1, (it++)->value);
			EXPECT_EQ(14, (it++)->value);
			EXPECT_EQ(14, (it++)->value);
			EXPECT_EQ(14, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_THROW(v.emplace_front(ThrowOnMove(2)), ThrowOnMove::Exception);
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

}	// namespace emplace_front_test

}	// namespace hamon_forward_list_test
