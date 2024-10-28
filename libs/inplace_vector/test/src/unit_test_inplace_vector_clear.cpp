/**
 *	@file	unit_test_inplace_vector_clear.cpp
 *
 *	@brief	clear のテスト
 *
 *	constexpr void clear() noexcept;
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace clear_test
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

struct S4
{
	static int s_dtor_count;
	~S4() {++s_dtor_count;}
};
int S4::s_dtor_count = 0;

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v;
		static_assert(hamon::is_same<decltype(v.clear()), void>::value, "");
		static_assert( noexcept(v.clear()), "");
	}
	{
		InplaceVector v;
		v.clear();
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_5()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v(1);
		VERIFY(!v.empty());
		VERIFY(v.size() == 1);
		v.clear();
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
	}
	{
		InplaceVector v(2);
		VERIFY(!v.empty());
		VERIFY(v.size() == 2);
		v.clear();
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
	}
	{
		InplaceVector v(5);
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		v.clear();
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl_0<T, 0>()));
	VERIFY((test_impl_0<T, 1>()));
	VERIFY((test_impl_0<T, 2>()));
	VERIFY((test_impl_0<T, 5>()));
	VERIFY((test_impl_0<T, 6>()));
	VERIFY((test_impl_0<T, 9>()));

//	VERIFY((test_impl_5<T, 0>()));
//	VERIFY((test_impl_5<T, 1>()));
//	VERIFY((test_impl_5<T, 2>()));
	VERIFY((test_impl_5<T, 5>()));
	VERIFY((test_impl_5<T, 6>()));
	VERIFY((test_impl_5<T, 9>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, ClearTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
	EXPECT_TRUE(test<S3>());

	S4::s_dtor_count = 0;
	{
		hamon::inplace_vector<S4, 10> v;
		v.clear();
		EXPECT_EQ(0, S4::s_dtor_count);
	}
	EXPECT_EQ(0, S4::s_dtor_count);

	S4::s_dtor_count = 0;
	{
		hamon::inplace_vector<S4, 10> v(5);
		v.clear();
		EXPECT_EQ(5, S4::s_dtor_count);
	}
	EXPECT_EQ(5, S4::s_dtor_count);

	// https://en.cppreference.com/w/cpp/container/inplace_vector/clear
	{
		hamon::inplace_vector<int, 3> container {1, 2, 3};

		// Before clear
		{
			std::stringstream ss;
			for (auto const& value : container)
			{
				ss << value << ' ';
			}
			EXPECT_EQ("1 2 3 ", ss.str());
			EXPECT_EQ(3u, container.size());
		}

		container.clear();

		// After clear
		{
			std::stringstream ss;
			for (auto const& value : container)
			{
				ss << value << ' ';
			}
			EXPECT_EQ("", ss.str());
			EXPECT_EQ(0u, container.size());
		}
	}
}

}	// namespace clear_test

}	// namespace hamon_inplace_vector_test
