/**
 *	@file	unit_test_inplace_vector_insert_iterator.cpp
 *
 *	@brief	insert のテスト
 *
 *	template<class InputIterator>
 *	constexpr iterator insert(const_iterator position, InputIterator first, InputIterator last);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_inplace_vector_test
{

namespace insert_iterator_test
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

	ThrowOnCopy& operator=(ThrowOnCopy const&) = default;
	ThrowOnCopy& operator=(ThrowOnCopy &&) = default;
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N, template <typename> class IteratorWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using Iterator = typename InplaceVector::iterator;
	using ConstIterator = typename InplaceVector::const_iterator;
	using InputIterator = IteratorWrapper<T>;

	{
		InplaceVector v;
		ConstIterator pos;
		InputIterator first;
		InputIterator last;
		static_assert(hamon::is_same<decltype(v.insert(pos, first, last)), Iterator>::value, "");
		static_assert(!noexcept(v.insert(pos, first, last)), "");
	}
	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		T a[] = {T{1}, T{2}, T{3}};
		auto it = v.insert(v.begin(), InputIterator{a}, InputIterator{a});
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
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
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		{
			T a[] = {T{1}, T{2}, T{3}};
			auto it = v.insert(v.end(), InputIterator{a}, InputIterator{a + 3});
			VERIFY(it == v.begin());
			VERIFY(*it == T{1});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{2});
		VERIFY(v[2] == T{3});

		{
			T b[] = {T{4}, T{5}};
			auto it = v.insert(v.begin() + 1, InputIterator{b}, InputIterator{b + 2});
			VERIFY(it == v.begin() + 1);
			VERIFY(*it == T{4});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{4});
		VERIFY(v[2] == T{5});
		VERIFY(v[3] == T{2});
		VERIFY(v[4] == T{3});
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

GTEST_TEST(InplaceVectorTest, InsertIteratorTest)
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
		int const a[]{1,2,3,4,5};
		EXPECT_THROW(v.insert(v.end(), a, a + 1), hamon::bad_alloc);
		EXPECT_TRUE(v.empty());
		EXPECT_EQ(0u, v.size());
		EXPECT_NO_THROW(v.insert(v.end(), a, a));
		EXPECT_TRUE(v.empty());
		EXPECT_EQ(0u, v.size());
	}
	{
		hamon::inplace_vector<int, 1> v;
		int const a[]{1,2,3,4,5};
		EXPECT_NO_THROW(v.insert(v.end(), a, a + 1));
		EXPECT_TRUE(!v.empty());
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_THROW(v.insert(v.end(), a, a + 1), hamon::bad_alloc);
		EXPECT_TRUE(!v.empty());
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(1, v[0]);
	}
	{
		hamon::inplace_vector<ThrowOnCopy, 5> v;
		EXPECT_TRUE(v.empty());
		ThrowOnCopy a[]{1,2,3,4,5};
		EXPECT_THROW(v.insert(v.begin(), a, a + 3), ThrowOnCopy::Exception);
		EXPECT_TRUE(v.empty());
		EXPECT_NO_THROW(v.insert(v.begin(), a, a + 0));
		EXPECT_TRUE(v.empty());
		EXPECT_NO_THROW(v.insert(v.begin(), hamon::make_move_iterator(a), hamon::make_move_iterator(a + 3)));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0].value);
		EXPECT_EQ(2, v[1].value);
		EXPECT_EQ(3, v[2].value);
		EXPECT_THROW(v.insert(v.begin(), a, a + 2), ThrowOnCopy::Exception);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0].value);
		EXPECT_EQ(2, v[1].value);
		EXPECT_EQ(3, v[2].value);
		EXPECT_THROW(v.insert(v.begin(), a, a + 3), hamon::bad_alloc);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0].value);
		EXPECT_EQ(2, v[1].value);
		EXPECT_EQ(3, v[2].value);
	}
#endif
}

}	// namespace insert_iterator_test

}	// namespace hamon_inplace_vector_test
