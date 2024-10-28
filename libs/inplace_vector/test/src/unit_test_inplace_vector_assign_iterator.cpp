/**
 *	@file	unit_test_inplace_vector_assign_iterator.cpp
 *
 *	@brief	assign のテスト
 *
 *	template<class InputIterator>
 *	constexpr void assign(InputIterator first, InputIterator last);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_inplace_vector_test
{

namespace assign_iterator_test
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

template <typename T, hamon::size_t N, template <typename> class IteratorWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using InputIterator = IteratorWrapper<T>;

	{
		InplaceVector v;
		InputIterator first;
		InputIterator last;
		static_assert(hamon::is_same<decltype(v.assign(first, last)), void>::value, "");
		static_assert(!noexcept(v.assign(first, last)), "");
	}
	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		T a[] = {T{1}, T{2}, T{3}};
		v.assign(InputIterator{a}, InputIterator{a});
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
	}

	return true;
}

template <typename T, hamon::size_t N, template <typename> class IteratorWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl_5()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using InputIterator = IteratorWrapper<T>;

	{
		InplaceVector v;

		{
			T a[] = {T{1}, T{2}, T{3}};
			v.assign(InputIterator{a}, InputIterator{a + 3});
		}
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{2});
		VERIFY(v[2] == T{3});

		{
			T a[] = {T{11}, T{12}, T{13}, T{14}, T{15}};
			v.assign(InputIterator{a}, InputIterator{a + 5});
		}
		VERIFY(v.size() == 5);
		VERIFY(v[0] == T{11});
		VERIFY(v[1] == T{12});
		VERIFY(v[2] == T{13});
		VERIFY(v[3] == T{14});
		VERIFY(v[4] == T{15});

		{
			T a[] = {T{21}, T{22}, T{23}, T{24}};
			v.assign(InputIterator{a}, InputIterator{a + 4});
		}
		VERIFY(v.size() == 4);
		VERIFY(v[0] == T{21});
		VERIFY(v[1] == T{22});
		VERIFY(v[2] == T{23});
		VERIFY(v[3] == T{24});

		{
			T a[] = {T{31}, T{32}};
			v.assign(InputIterator{a}, InputIterator{a + 2});
		}
		VERIFY(v.size() == 2);
		VERIFY(v[0] == T{31});
		VERIFY(v[1] == T{32});
	}

	return true;
}

template <typename T, template <typename> class IteratorWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl()
{
	VERIFY((test_impl_0<T, 0, IteratorWrapper>()));
	VERIFY((test_impl_0<T, 1, IteratorWrapper>()));
	VERIFY((test_impl_0<T, 2, IteratorWrapper>()));
	VERIFY((test_impl_0<T, 5, IteratorWrapper>()));
	VERIFY((test_impl_0<T, 6, IteratorWrapper>()));

//	VERIFY((test_impl_5<T, 0, IteratorWrapper>()));
//	VERIFY((test_impl_5<T, 1, IteratorWrapper>()));
//	VERIFY((test_impl_5<T, 2, IteratorWrapper>()));
	VERIFY((test_impl_5<T, 5, IteratorWrapper>()));
	VERIFY((test_impl_5<T, 6, IteratorWrapper>()));

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl<T, cpp17_input_iterator_wrapper>()));
//	VERIFY((test_impl<T, input_iterator_wrapper>()));
	VERIFY((test_impl<T, forward_iterator_wrapper>()));
	VERIFY((test_impl<T, bidirectional_iterator_wrapper>()));
	VERIFY((test_impl<T, random_access_iterator_wrapper>()));
	VERIFY((test_impl<T, contiguous_iterator_wrapper>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, AssignIteratorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
	EXPECT_TRUE(test<S3>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		int const a[]{1,2,3,4,5};
		hamon::inplace_vector<int, 0> v;
		EXPECT_NO_THROW(v.assign(a, a));
		EXPECT_TRUE(v.empty());
		EXPECT_EQ(0u, v.size());
		EXPECT_THROW(v.assign(a, a + 1), hamon::bad_alloc);
		EXPECT_TRUE(v.empty());
		EXPECT_EQ(0u, v.size());
	}
	{
		int const a[]{1,2,3,4,5};
		hamon::inplace_vector<int, 3> v;
		EXPECT_NO_THROW(v.assign(a, a + 3));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
		EXPECT_THROW(v.assign(a, a + 4), hamon::bad_alloc);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
	}
	{
		ThrowOnCopy const a[]{1,2,3,4,5};
		hamon::inplace_vector<ThrowOnCopy, 3> v;
		v.emplace_back(10);
		v.emplace_back(20);
		EXPECT_THROW(v.assign(a, a + 1), ThrowOnCopy::Exception);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_THROW(v.assign(a, a + 2), ThrowOnCopy::Exception);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_THROW(v.assign(a, a + 3), ThrowOnCopy::Exception);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_THROW(v.assign(a, a + 4), hamon::bad_alloc);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_NO_THROW(v.assign(a, a + 0));
		EXPECT_TRUE(v.empty());
	}
#endif
}

}	// namespace assign_iterator_test

}	// namespace hamon_inplace_vector_test
