/**
 *	@file	unit_test_inplace_vector_erase.cpp
 *
 *	@brief	erase のテスト
 *
 *	constexpr iterator erase(const_iterator position);
 *	constexpr iterator erase(const_iterator first, const_iterator last);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace erase_test
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
HAMON_CXX14_CONSTEXPR bool test_impl_1()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using Iterator = typename InplaceVector::iterator;
	using ConstIterator = typename InplaceVector::const_iterator;

	{
		InplaceVector v;
		ConstIterator it;
		static_assert(hamon::is_same<decltype(v.erase(it)), Iterator>::value, "");
		static_assert(hamon::is_same<decltype(v.erase(it, it)), Iterator>::value, "");
		static_assert(!noexcept(v.erase(it)), "");
		static_assert(!noexcept(v.erase(it, it)), "");
	}
	{
		InplaceVector v{T{42}};
		auto it = v.erase(v.begin());
		VERIFY(it == v.begin());
		VERIFY(v.empty());
	}
	{
		InplaceVector v{T{42}};
		auto it = v.erase(v.begin(), v.begin());
		VERIFY(it == v.begin());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == T{42});
	}
	{
		InplaceVector v{T{42}};
		auto it = v.erase(v.begin(), v.end());
		VERIFY(it == v.begin());
		VERIFY(v.empty());
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_5()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v{T{1},T{2},T{3},T{4},T{5}};
		auto it = v.erase(v.begin());
		VERIFY(it == v.begin());
		VERIFY(v.size() == 4);
		VERIFY(v[0] == T{2});
		VERIFY(v[1] == T{3});
		VERIFY(v[2] == T{4});
		VERIFY(v[3] == T{5});
	}
	{
		InplaceVector v{T{1},T{2},T{3},T{4},T{5}};
		auto it = v.erase(hamon::next(v.begin(), 1));
		VERIFY(it == hamon::next(v.begin(), 1));
		VERIFY(v.size() == 4);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{3});
		VERIFY(v[2] == T{4});
		VERIFY(v[3] == T{5});
	}
	{
		InplaceVector v{T{1},T{2},T{3},T{4},T{5}};
		auto it = v.erase(hamon::next(v.begin(), 4));
		VERIFY(it == hamon::next(v.begin(), 4));
		VERIFY(v.size() == 4);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{2});
		VERIFY(v[2] == T{3});
		VERIFY(v[3] == T{4});
	}
	{
		InplaceVector v{T{1},T{2},T{3},T{4},T{5}};
		auto it = v.erase(v.begin(), hamon::next(v.begin(), 2));
		VERIFY(it == v.begin());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{3});
		VERIFY(v[1] == T{4});
		VERIFY(v[2] == T{5});
	}
	{
		InplaceVector v{T{1},T{2},T{3},T{4},T{5}};
		auto it = v.erase(hamon::next(v.begin(), 1), hamon::next(v.begin(), 4));
		VERIFY(it == hamon::next(v.begin(), 1));
		VERIFY(v.size() == 2);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{5});
	}
	{
		InplaceVector v{T{1},T{2},T{3},T{4},T{5}};
		auto it = v.erase(hamon::next(v.begin(), 2), v.end());
		VERIFY(it == hamon::next(v.begin(), 2));
		VERIFY(v.size() == 2);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{2});
	}
	{
		InplaceVector v{T{1},T{2},T{3},T{4},T{5}};
		auto it = v.erase(v.begin(), v.begin());
		VERIFY(it == v.begin());
		VERIFY(v.size() == 5);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{2});
		VERIFY(v[2] == T{3});
		VERIFY(v[3] == T{4});
		VERIFY(v[4] == T{5});
	}
	{
		InplaceVector v{T{1},T{2},T{3},T{4},T{5}};
		auto it = v.erase(v.end(), v.end());
		VERIFY(it == v.end());
		VERIFY(v.size() == 5);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{2});
		VERIFY(v[2] == T{3});
		VERIFY(v[3] == T{4});
		VERIFY(v[4] == T{5});
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

#undef VERIFY

GTEST_TEST(InplaceVectorTest, EraseTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
#if defined(HAMON_MSVC) && (HAMON_MSVC < 1930)
	                      EXPECT_TRUE(test<S1>());
#else
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
#endif
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
	EXPECT_TRUE(test<S3>());

	S4::s_dtor_count = 0;
	{
		hamon::inplace_vector<S4, 10> v(5);
		v.erase(v.begin());
		EXPECT_EQ(1, S4::s_dtor_count);
		v.erase(hamon::next(v.begin(), 1));
		EXPECT_EQ(2, S4::s_dtor_count);
	}
	EXPECT_EQ(5, S4::s_dtor_count);

	S4::s_dtor_count = 0;
	{
		hamon::inplace_vector<S4, 10> v(5);
		v.erase(hamon::next(v.begin(), 2), v.end());
		EXPECT_EQ(3, S4::s_dtor_count);
		v.erase(v.begin(), v.begin());
		EXPECT_EQ(3, S4::s_dtor_count);
	}
	EXPECT_EQ(5, S4::s_dtor_count);

	// https://en.cppreference.com/w/cpp/container/inplace_vector/erase
	{
		auto print = [](hamon::inplace_vector<int, 10> const& v)
		{
			std::stringstream ss;
			for (auto const& e : v)
			{
				ss << e << ", ";
			}
			return ss.str();
		};

		hamon::inplace_vector<int, 10> v {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		EXPECT_EQ("0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ", print(v));

		v.erase(v.begin());
		EXPECT_EQ("1, 2, 3, 4, 5, 6, 7, 8, 9, ", print(v));

		v.erase(v.begin() + 2, v.begin() + 5);
		EXPECT_EQ("1, 2, 6, 7, 8, 9, ", print(v));

		// Erase all even numbers
		for (hamon::inplace_vector<int, 10>::iterator it {v.begin()}; it != v.end();)
		{
			if (*it % 2 == 0)
			{
				it = v.erase(it);
			}
			else
			{
				++it;
			}
		}
		EXPECT_EQ("1, 7, 9, ", print(v));
	}
}

}	// namespace erase_test

}	// namespace hamon_inplace_vector_test
