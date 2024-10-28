/**
 *	@file	unit_test_inplace_vector_emplace.cpp
 *
 *	@brief	emplace のテスト
 *
 *	template<class... Args>
 *	constexpr iterator emplace(const_iterator position, Args&&... args);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace emplace_test
{

struct S1
{
	int m_value;
	constexpr bool operator==(S1 const& y) const { return m_value == y.m_value; }
};

struct S2
{
	int m_value;
	S2() = default;
	constexpr S2(int v) : m_value(v) {}
	constexpr S2(S2 const& x) : m_value(x.m_value) {}
	S2& operator=(S2 const&) = default;
	S2& operator=(S2 &&) = default;
	constexpr bool operator==(S2 const& y) const { return m_value == y.m_value; }
};

struct S3
{
	int m_value;
	constexpr S3() : m_value(0) {}
	constexpr S3(int v) : m_value(v) {}
	constexpr S3(S3 const& x) : m_value(x.m_value) {}
	S3& operator=(S3 const&) = default;
	S3& operator=(S3 &&) = default;
	constexpr bool operator==(S3 const& y) const { return m_value == y.m_value; }
};

struct Vector3
{
	int x;
	int y;
	int z;

	Vector3() = default;

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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_1()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using Iterator = typename InplaceVector::iterator;
	using ConstIterator = typename InplaceVector::const_iterator;

	{
		InplaceVector v;
		ConstIterator it;
		static_assert(hamon::is_same<decltype(v.emplace(it)), Iterator>::value, "");
		static_assert(hamon::is_same<decltype(v.emplace(it, hamon::declval<T>())), Iterator>::value, "");
		static_assert(!noexcept(v.emplace(it)), "");
		static_assert(!noexcept(v.emplace(it, hamon::declval<T>())), "");
	}
	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		auto it = v.emplace(v.begin(), T{42});
		VERIFY(it == v.begin());
		VERIFY(*it == T{42});
		VERIFY(!v.empty());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == T{42});
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_5()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		{
			auto it = v.emplace(v.end(), T{10});
			VERIFY(it == v.begin());
			VERIFY(*it == T{10});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == T{10});

		{
			auto it = v.emplace(v.begin() + 1, T{11});
			VERIFY(it == v.begin() + 1);
			VERIFY(*it == T{11});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 2);
		VERIFY(v[0] == T{10});
		VERIFY(v[1] == T{11});

		{
			auto it = v.emplace(v.begin(), T{12});
			VERIFY(it == v.begin());
			VERIFY(*it == T{12});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{12});
		VERIFY(v[1] == T{10});
		VERIFY(v[2] == T{11});

		{
			auto it = v.emplace(v.end(), T{13});
			VERIFY(it == v.begin() + 3);
			VERIFY(*it == T{13});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 4);
		VERIFY(v[0] == T{12});
		VERIFY(v[1] == T{10});
		VERIFY(v[2] == T{11});
		VERIFY(v[3] == T{13});

		{
			auto it = v.emplace(v.begin() + 3, T{14});
			VERIFY(it == v.begin() + 3);
			VERIFY(*it == T{14});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v[0] == T{12});
		VERIFY(v[1] == T{10});
		VERIFY(v[2] == T{11});
		VERIFY(v[3] == T{14});
		VERIFY(v[4] == T{13});
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl_1<T, 1>()));
	VERIFY((test_impl_1<T, 2>()));
	VERIFY((test_impl_1<T, 5>()));
	VERIFY((test_impl_1<T, 6>()));
	VERIFY((test_impl_1<T, 9>()));

//	VERIFY((test_impl_5<T, 1>()));
//	VERIFY((test_impl_5<T, 2>()));
	VERIFY((test_impl_5<T, 5>()));
	VERIFY((test_impl_5<T, 6>()));
	VERIFY((test_impl_5<T, 9>()));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test2()
{
	hamon::inplace_vector<Vector3, 10> v;
	VERIFY(v.empty());
	{
		auto it = v.emplace(v.end(), 1,2,3);
		VERIFY(it == v.begin());
	}
	VERIFY(!v.empty());
	VERIFY(v.size() == 1);
	VERIFY(v[0] == Vector3{1,2,3});
	{
		auto it = v.emplace(v.begin(), 4,5,6);
		VERIFY(it == v.begin());
	}
	VERIFY(!v.empty());
	VERIFY(v.size() == 2);
	VERIFY(v[0] == Vector3{4,5,6});
	VERIFY(v[1] == Vector3{1,2,3});
	{
		auto it = v.emplace(v.begin() + 1, 7,8,9);
		VERIFY(it == v.begin() + 1);
	}
	VERIFY(!v.empty());
	VERIFY(v.size() == 3);
	VERIFY(v[0] == Vector3{4,5,6});
	VERIFY(v[1] == Vector3{7,8,9});
	VERIFY(v[2] == Vector3{1,2,3});

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, EmplaceTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
	EXPECT_TRUE(test<S3>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::inplace_vector<int, 0> v;
		EXPECT_THROW(v.emplace(v.end(), 1), hamon::bad_alloc);
		EXPECT_TRUE(v.empty());
		EXPECT_EQ(0u, v.size());
	}
	{
		hamon::inplace_vector<int, 1> v;
		EXPECT_NO_THROW(v.emplace(v.begin(), 10));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0]);
		EXPECT_THROW(v.emplace(v.begin(), 20), hamon::bad_alloc);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0]);
	}
	{
		hamon::inplace_vector<MayThrow, 3> v;
		EXPECT_NO_THROW(v.emplace(v.begin(), 10));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_THROW(v.emplace(v.begin(), -10), MayThrow::Exception);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_NO_THROW(v.emplace(v.begin(), 20));
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(20, v[0].value);
		EXPECT_EQ(10, v[1].value);
		EXPECT_THROW(v.emplace(v.begin(), -1), MayThrow::Exception);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(20, v[0].value);
		EXPECT_EQ(10, v[1].value);
		EXPECT_NO_THROW(v.emplace(v.begin() + 1, 30));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(20, v[0].value);
		EXPECT_EQ(30, v[1].value);
		EXPECT_EQ(10, v[2].value);
		EXPECT_THROW(v.emplace(v.begin(), -1), hamon::bad_alloc);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(20, v[0].value);
		EXPECT_EQ(30, v[1].value);
		EXPECT_EQ(10, v[2].value);
	}
#endif

	// https://en.cppreference.com/w/cpp/container/inplace_vector/emplace
	{
		using P = hamon::pair<int, int>;
		using I = hamon::inplace_vector<P, 3>;
		auto nums = I {{0, 1}, {2, 3}};

		auto it = nums.emplace(nums.begin() + 1, -1, -2);
		EXPECT_TRUE((*it == P {-1, -2}));
		EXPECT_TRUE((nums == I {P {0, 1}, {-1, -2}, {2, 3}}));

#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW(nums.emplace(nums.begin(), 1, 3), hamon::bad_alloc); // throws: no space
#endif
	}
}

}	// namespace emplace_test

}	// namespace hamon_inplace_vector_test
