/**
 *	@file	unit_test_vector_push_back.cpp
 *
 *	@brief	push_back のテスト
 *
 *	constexpr void push_back(const T& x);
 *	constexpr void push_back(T&& x);
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace push_back_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Vector = hamon::vector<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().push_back(hamon::declval<T const&>())),
		void
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().push_back(hamon::declval<T&&>())),
		void
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Vector&>().push_back(hamon::declval<T const&>())), "");
	static_assert(!noexcept(
		hamon::declval<Vector&>().push_back(hamon::declval<T&&>())), "");

	{
		Vector v;
		VERIFY(v.size() == 0);

		T const x(10);
		v.push_back(x);
		VERIFY(v.size() == 1);
		VERIFY(v[0] == 10);

		v.push_back(20);
		VERIFY(v.size() == 2);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 20);

		v.push_back(30);
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 30);

		v.push_back(40);
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 30);
		VERIFY(v[3] == 40);

		v.push_back(50);
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 30);
		VERIFY(v[3] == 40);
		VERIFY(v[4] == 50);

		v.push_back(60);
		VERIFY(v.size() == 6);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 30);
		VERIFY(v[3] == 40);
		VERIFY(v[4] == 50);
		VERIFY(v[5] == 60);

		v.push_back(70);
		v.push_back(80);
		v.push_back(90);
		VERIFY(v.size() == 9);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 30);
		VERIFY(v[3] == 40);
		VERIFY(v[4] == 50);
		VERIFY(v[5] == 60);
		VERIFY(v[6] == 70);
		VERIFY(v[7] == 80);
		VERIFY(v[8] == 90);
	}
	{
		Vector v{1,2,3};
		v.reserve(4);
		// メモリの再確保が行われないときは、end()以外のイテレータは無効にならない
		auto const it1 = v.begin();
		auto const it2 = v.begin() + 1;
		auto const it3 = v.begin() + 2;
		v.push_back(10);
		VERIFY(it1 == v.begin());
		VERIFY(it2 == v.begin() + 1);
		VERIFY(it3 == v.begin() + 2);
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 10);
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

	ThrowOnCopy& operator=(ThrowOnCopy const&) = default;
	ThrowOnCopy& operator=(ThrowOnCopy&&) = default;
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

	ThrowOnMove& operator=(ThrowOnMove const&) = default;
	ThrowOnMove& operator=(ThrowOnMove&&) = default;
};
#endif

GTEST_TEST(VectorTest, PushBackTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::vector<ThrowOnCopy> v;

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		ThrowOnCopy const t(1);
		EXPECT_THROW(v.push_back(t), ThrowOnCopy::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(0u, v.size());

		v.push_back(ThrowOnCopy(2));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 2, v[0].value);
	}
	{
		hamon::vector<ThrowOnCopy> v(2);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		ThrowOnCopy const t(1);
		EXPECT_THROW(v.push_back(t), ThrowOnCopy::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);

		v.push_back(ThrowOnCopy(2));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);
		EXPECT_EQ( 2, v[2].value);
	}
	{
		hamon::vector<ThrowOnCopy> v(2);
		v.reserve(10);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		ThrowOnCopy const t(1);
		EXPECT_THROW(v.push_back(t), ThrowOnCopy::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);

		v.push_back(ThrowOnCopy(2));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);
		EXPECT_EQ( 2, v[2].value);
	}
	{
		hamon::vector<ThrowOnMove> v(3);

		ThrowOnMove const t(1);
		v.push_back(t);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(14, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ( 1, v[3].value);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.push_back(ThrowOnMove(2)), ThrowOnMove::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(14, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ( 1, v[3].value);
	}
	{
		hamon::vector<ThrowOnMove> v(3);
		v.reserve(10);

		ThrowOnMove const t(1);
		v.push_back(t);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(14, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ( 1, v[3].value);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.push_back(ThrowOnMove(2)), ThrowOnMove::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(14, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ( 1, v[3].value);
	}
#endif
}

}	// namespace push_back_test

}	// namespace hamon_vector_test
