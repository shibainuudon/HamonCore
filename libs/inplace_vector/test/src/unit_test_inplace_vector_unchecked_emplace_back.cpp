/**
 *	@file	unit_test_inplace_vector_unchecked_emplace_back.cpp
 *
 *	@brief	unchecked_emplace_back のテスト
 *
 *	template<class... Args>
 *	constexpr reference unchecked_emplace_back(Args&&... args);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/pair.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace unchecked_emplace_back_test
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
	using Reference = typename InplaceVector::reference;

	{
		InplaceVector v;
		static_assert(hamon::is_same<decltype(v.unchecked_emplace_back()), Reference>::value, "");
		static_assert(hamon::is_same<decltype(v.unchecked_emplace_back(hamon::declval<T>())), Reference>::value, "");
		static_assert(!noexcept(v.unchecked_emplace_back()), "");
		static_assert(!noexcept(v.unchecked_emplace_back(hamon::declval<T>())), "");
	}

	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		auto& r = v.unchecked_emplace_back(T{42});
		VERIFY(&r == &v.back());
		VERIFY(r == T{42});
		VERIFY(!v.empty());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == T{42});
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_3()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		{
			auto& r = v.unchecked_emplace_back(T{10});
			VERIFY(&r == &v.back());
			VERIFY(r == T{10});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == T{10});
		{
			auto& r = v.unchecked_emplace_back(T{20});
			VERIFY(&r == &v.back());
			VERIFY(r == T{20});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 2);
		VERIFY(v[0] == T{10});
		VERIFY(v[1] == T{20});
		{
			auto& r = v.unchecked_emplace_back(T{30});
			VERIFY(&r == &v.back());
			VERIFY(r == T{30});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{10});
		VERIFY(v[1] == T{20});
		VERIFY(v[2] == T{30});
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl_1<T, 1>()));
	VERIFY((test_impl_1<T, 2>()));
	VERIFY((test_impl_1<T, 3>()));
	VERIFY((test_impl_1<T, 9>()));

//	VERIFY((test_impl_3<T, 1>()));
//	VERIFY((test_impl_3<T, 2>()));
	VERIFY((test_impl_3<T, 3>()));
	VERIFY((test_impl_3<T, 9>()));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test2()
{
	hamon::inplace_vector<Vector3, 10> v;
	VERIFY(v.empty());
	{
		auto& r = v.unchecked_emplace_back(1,2,3);
		VERIFY(&r == &v.back());
	}
	VERIFY(!v.empty());
	VERIFY(v.size() == 1);
	VERIFY(v[0] == Vector3{1,2,3});
	{
		auto& r = v.unchecked_emplace_back(4,5,6);
		VERIFY(&r == &v.back());
	}
	VERIFY(!v.empty());
	VERIFY(v.size() == 2);
	VERIFY(v[0] == Vector3{1,2,3});
	VERIFY(v[1] == Vector3{4,5,6});

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, UncheckedEmplaceBackTest)
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
		hamon::inplace_vector<MayThrow, 3> v;
		EXPECT_NO_THROW(v.unchecked_emplace_back(10));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_THROW(v.unchecked_emplace_back(-10), MayThrow::Exception);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_NO_THROW(v.unchecked_emplace_back(20));
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_THROW(v.unchecked_emplace_back(-1), MayThrow::Exception);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_NO_THROW(v.unchecked_emplace_back(30));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_EQ(30, v[2].value);
	}
#endif

	// https://en.cppreference.com/w/cpp/container/inplace_vector/unchecked_emplace_back
	{
		auto print = [](hamon::inplace_vector<hamon::pair<hamon::string, hamon::string>, 2> const& v)
		{
			std::stringstream ss;
			for (auto const& e : v)
			{
				ss << "(" << e.first << ", " << e.second << "), ";
			}
			return ss.str();
		};

		hamon::inplace_vector<hamon::pair<hamon::string, hamon::string>, 2> fauna;
		hamon::string dog {"DOG"};

		fauna.unchecked_emplace_back("CAT", dog);
		fauna.unchecked_emplace_back("CAT", hamon::move(dog));
		EXPECT_EQ("(CAT, DOG), (CAT, DOG), ", print(fauna));

		// fauna.unchecked_emplace_back("BUG", "BUG"); // undefined behavior: no space
	}
}

}	// namespace unchecked_emplace_back_test

}	// namespace hamon_inplace_vector_test
