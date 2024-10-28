/**
 *	@file	unit_test_inplace_vector_assign_n_value.cpp
 *
 *	@brief	assign のテスト
 *
 *	constexpr void assign(size_type n, const T& u);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/algorithm.hpp>
#include <hamon/array.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace assign_n_value_test
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

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnCopy
{
	struct Exception{};

	int value;

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

	ThrowOnCopy& operator=(ThrowOnCopy const&)
	{
		throw Exception{};
	}

	ThrowOnCopy& operator=(ThrowOnCopy &&) = default;
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using SizeType = typename InplaceVector::size_type;

	{
		InplaceVector v;
		SizeType const n{};
		T const c{};
		static_assert(hamon::is_same<decltype(v.assign(n, c)), void>::value, "");
		static_assert(!noexcept(v.assign(n, c)), "");
	}
	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		v.assign(0, T{42});
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
		InplaceVector v;

		v.assign(3, T{1});
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{1});
		VERIFY(v[2] == T{1});

		v.assign(5, T{11});
		VERIFY(v.size() == 5);
		VERIFY(v[0] == T{11});
		VERIFY(v[1] == T{11});
		VERIFY(v[2] == T{11});
		VERIFY(v[3] == T{11});
		VERIFY(v[4] == T{11});

		v.assign(5, T{21});
		VERIFY(v.size() == 5);
		VERIFY(v[0] == T{21});
		VERIFY(v[1] == T{21});
		VERIFY(v[2] == T{21});
		VERIFY(v[3] == T{21});
		VERIFY(v[4] == T{21});

		v.assign(2, T{31});
		VERIFY(v.size() == 2);
		VERIFY(v[0] == T{31});
		VERIFY(v[1] == T{31});

		v.assign(0, T{41});
		VERIFY(v.empty());
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

//	VERIFY((test_impl_5<T, 0>()));
//	VERIFY((test_impl_5<T, 1>()));
//	VERIFY((test_impl_5<T, 2>()));
	VERIFY((test_impl_5<T, 5>()));
	VERIFY((test_impl_5<T, 6>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, AssignNValueTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
	EXPECT_TRUE(test<S3>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::inplace_vector<int, 0> v;
		EXPECT_NO_THROW(v.assign(0, 42));
		EXPECT_TRUE(v.empty());
		EXPECT_EQ(0u, v.size());
		EXPECT_THROW(v.assign(1, 42), hamon::bad_alloc);
		EXPECT_TRUE(v.empty());
		EXPECT_EQ(0u, v.size());
	}
	{
		hamon::inplace_vector<int, 3> v;
		EXPECT_NO_THROW(v.assign(3, 42));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(42, v[0]);
		EXPECT_EQ(42, v[1]);
		EXPECT_EQ(42, v[2]);
		EXPECT_THROW(v.assign(4, 43), hamon::bad_alloc);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(42, v[0]);
		EXPECT_EQ(42, v[1]);
		EXPECT_EQ(42, v[2]);
	}
	{
		hamon::inplace_vector<ThrowOnCopy, 3> v;
		v.emplace_back(10);
		v.emplace_back(20);
		EXPECT_THROW(v.assign(1, ThrowOnCopy{1}), ThrowOnCopy::Exception);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_THROW(v.assign(2, ThrowOnCopy{1}), ThrowOnCopy::Exception);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_THROW(v.assign(3, ThrowOnCopy{1}), ThrowOnCopy::Exception);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_THROW(v.assign(4, ThrowOnCopy{1}), hamon::bad_alloc);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_NO_THROW(v.assign(0, ThrowOnCopy{1}));
		EXPECT_TRUE(v.empty());
	}
#endif

	// https://en.cppreference.com/w/cpp/container/inplace_vector/assign
	{
		hamon::inplace_vector<char, 5> chars;

		chars.assign(4, 'a'); // overload (1)
		EXPECT_TRUE(hamon::ranges::equal(chars, hamon::array<char, 4>{'a', 'a', 'a', 'a'}));

		const char extra[3] {'a', 'b', 'c'};
		chars.assign(hamon::cbegin(extra), hamon::cend(extra)); // overload (2)
		EXPECT_TRUE(hamon::ranges::equal(chars, hamon::array<char, 3>{'a', 'b', 'c'}));

		chars.assign({'C', '+', '+', '2', '6'}); // overload (3)
		EXPECT_TRUE(hamon::ranges::equal(chars, hamon::array<char, 5>{'C', '+', '+', '2', '6'}));

#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW(chars.assign(8, 'x'), hamon::bad_alloc); // throws: count > chars.capacity()
		{
			const char bad[8] {'?'}; // ranges::distance(bad) > chars.capacity()
			EXPECT_THROW(chars.assign(hamon::cbegin(bad), hamon::cend(bad)), hamon::bad_alloc); // throws
		}
		{
			const auto l = {'1', '2', '3', '4', '5', '6'};
			EXPECT_THROW(chars.assign(l), hamon::bad_alloc); // throws: l.size() > chars.capacity()
		}
#endif
	}
}

}	// namespace assign_n_value_test

}	// namespace hamon_inplace_vector_test
