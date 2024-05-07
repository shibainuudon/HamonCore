/**
 *	@file	unit_test_vector_emplace_back.cpp
 *
 *	@brief	emplace_back のテスト
 *
 *	template<class... Args>
 *	constexpr reference emplace_back(Args&&... args);
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace emplace_back_test
{

struct MoveOnly
{
	int value;
	HAMON_CXX11_CONSTEXPR MoveOnly(int v) : value(v) {}
	HAMON_CXX11_CONSTEXPR MoveOnly(MoveOnly const& x) : value(x.value) {} // = delete;	// TODO Visual Studio 2019 だけ？
	HAMON_CXX11_CONSTEXPR MoveOnly(MoveOnly && x) noexcept : value(x.value) {}
	HAMON_CXX14_CONSTEXPR MoveOnly& operator=(MoveOnly const&) = delete;
	HAMON_CXX14_CONSTEXPR MoveOnly& operator=(MoveOnly && x) noexcept { value = x.value; return *this; }
};

struct S
{
	int value;
	HAMON_CXX11_CONSTEXPR S(int x) : value(x) {}
	HAMON_CXX11_CONSTEXPR S(int x, int y) : value(x + y) {}
	HAMON_CXX11_CONSTEXPR S(int x, int y, int z) : value(x + y + z) {}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR bool test1()
{
	using T = int;
	using Vector = hamon::vector<T>;
	using Reference = typename Vector::reference;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().emplace_back()),
		Reference
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().emplace_back(hamon::declval<T>())),
		Reference
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Vector&>().emplace_back()), "");
	static_assert(!noexcept(
		hamon::declval<Vector&>().emplace_back(hamon::declval<T>())), "");

	{
		Vector v{1,2,3};
		auto& r = v.emplace_back(10);
		VERIFY(&r == &v[3]);
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 10);
	}
	{
		Vector v{1,2,3};
		v.reserve(4);
		// メモリの再確保が行われないときは、end()以外のイテレータは無効にならない
		auto const it1 = v.begin();
		auto const it2 = v.begin() + 1;
		auto const it3 = v.begin() + 2;
		v.emplace_back(10);
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

HAMON_CXX20_CONSTEXPR bool test2()
{
	{
		hamon::vector<MoveOnly> v;

		auto& r1 = v.emplace_back(10);
		VERIFY(&r1 == &v[0]);
		VERIFY(v.size() == 1);
		VERIFY(v[0].value == 10);

		auto& r2 = v.emplace_back(11);
		VERIFY(&r2 == &v[1]);
		VERIFY(v.size() == 2);
		VERIFY(v[0].value == 10);
		VERIFY(v[1].value == 11);

		auto& r3 = v.emplace_back(12);
		VERIFY(&r3 == &v[2]);
		VERIFY(v.size() == 3);
		VERIFY(v[0].value == 10);
		VERIFY(v[1].value == 11);
		VERIFY(v[2].value == 12);
	}
	{
		hamon::vector<S> v;

		auto& r1 = v.emplace_back(10);
		VERIFY(&r1 == &v[0]);
		VERIFY(v.size() == 1);
		VERIFY(v[0].value == 10);

		auto& r2 = v.emplace_back(11, 12);
		VERIFY(&r2 == &v[1]);
		VERIFY(v.size() == 2);
		VERIFY(v[0].value == 10);
		VERIFY(v[1].value == 23);

		auto& r3 = v.emplace_back(1, 2, 3);
		VERIFY(&r3 == &v[2]);
		VERIFY(v.size() == 3);
		VERIFY(v[0].value == 10);
		VERIFY(v[1].value == 23);
		VERIFY(v[2].value == 6);
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

GTEST_TEST(VectorTest, EmplaceBackTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::vector<MayThrow> v;

		v.emplace_back(2);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 2, v[0].value);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.emplace_back(-2), MayThrow::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 2, v[0].value);
	}
	{
		hamon::vector<MayThrow> v;

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.emplace_back(-1), MayThrow::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(0u, v.size());

		v.emplace_back(3);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 3, v[0].value);
	}
	{
		hamon::vector<ThrowOnCopy> v;

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		ThrowOnCopy const t(1);
		EXPECT_THROW(v.emplace_back(t), ThrowOnCopy::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(0u, v.size());

		v.emplace_back(ThrowOnCopy(2));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 2, v[0].value);
	}
	{
		hamon::vector<ThrowOnCopy> v(2);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		ThrowOnCopy const t(1);
		EXPECT_THROW(v.emplace_back(t), ThrowOnCopy::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);

		v.emplace_back(ThrowOnCopy(2));
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
		EXPECT_THROW(v.emplace_back(t), ThrowOnCopy::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);

		v.emplace_back(ThrowOnCopy(2));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);
		EXPECT_EQ( 2, v[2].value);
	}
	{
		hamon::vector<ThrowOnMove> v(3);

		ThrowOnMove const t(1);
		v.emplace_back(t);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(14, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ( 1, v[3].value);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.emplace_back(ThrowOnMove(2)), ThrowOnMove::Exception);
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
		v.emplace_back(t);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(14, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ( 1, v[3].value);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.emplace_back(ThrowOnMove(2)), ThrowOnMove::Exception);
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

}	// namespace emplace_back_test

}	// namespace hamon_vector_test
