/**
 *	@file	unit_test_inplace_vector_ctor_iterator.cpp
 *
 *	@brief	イテレータを引数に取るコンストラクタのテスト
 *
 *	template<class InputIterator>
 *	constexpr inplace_vector(InputIterator first, InputIterator last);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_inplace_vector_test
{

namespace ctor_iterator_test
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

	ThrowOnCopy()
	{
	}

	ThrowOnCopy(ThrowOnCopy const&)
	{
		throw Exception{};
	}
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N, template <typename> class IteratorWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using Iterator = IteratorWrapper<T>;

	static_assert( hamon::is_constructible<InplaceVector, Iterator, Iterator>::value, "");
	static_assert(!hamon::is_nothrow_constructible<InplaceVector, Iterator, Iterator>::value, "");
	static_assert( hamon::is_implicitly_constructible<InplaceVector, Iterator, Iterator>::value, "");
	static_assert(!hamon::is_trivially_constructible<InplaceVector, Iterator, Iterator>::value, "");

	T a[] = {T{1}, T{2}, T{3}};
	{
		InplaceVector v(Iterator{a}, Iterator{a});
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
	}

	return true;
}

template <typename T, hamon::size_t N, template <typename> class IteratorWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl_3()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using Iterator = IteratorWrapper<T>;

	T a[] = {T{1}, T{2}, T{3}};
	{
		InplaceVector v(Iterator{a}, Iterator{a + 3});
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{2});
		VERIFY(v[2] == T{3});
	}

	return true;
}

template <typename T, template <typename> class IteratorWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl()
{
	VERIFY((test_impl_0<T, 0, IteratorWrapper>()));
	VERIFY((test_impl_0<T, 1, IteratorWrapper>()));
	VERIFY((test_impl_0<T, 2, IteratorWrapper>()));
	VERIFY((test_impl_0<T, 3, IteratorWrapper>()));
	VERIFY((test_impl_0<T, 4, IteratorWrapper>()));

//	VERIFY((test_impl_3<T, 0, IteratorWrapper>()));
//	VERIFY((test_impl_3<T, 1, IteratorWrapper>()));
//	VERIFY((test_impl_3<T, 2, IteratorWrapper>()));
	VERIFY((test_impl_3<T, 3, IteratorWrapper>()));
	VERIFY((test_impl_3<T, 4, IteratorWrapper>()));

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

GTEST_TEST(InplaceVectorTest, CtorIteratorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
	EXPECT_TRUE(test<S3>());

#if !defined(HAMON_NO_EXCEPTIONS)
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wunused-variable")
	{
		using InplaceVector = hamon::inplace_vector<int, 0>;
		int a[10]{};
		EXPECT_NO_THROW(InplaceVector v(a, a + 0));
		EXPECT_THROW   (InplaceVector v(a, a + 1), hamon::bad_alloc);
	}
	{
		using InplaceVector = hamon::inplace_vector<int, 5>;
		int a[10]{};
		EXPECT_NO_THROW(InplaceVector v(a, a + 5));
		EXPECT_THROW   (InplaceVector v(a, a + 6), hamon::bad_alloc);
	}
	{
		using InplaceVector = hamon::inplace_vector<ThrowOnCopy, 0>;
		ThrowOnCopy a[10]{};
		EXPECT_NO_THROW(InplaceVector v(a, a + 0));
		EXPECT_THROW   (InplaceVector v(a, a + 1), hamon::bad_alloc);
	}
	{
		using InplaceVector = hamon::inplace_vector<ThrowOnCopy, 5>;
		ThrowOnCopy a[10]{};
		EXPECT_NO_THROW(InplaceVector v(a, a + 0));
		EXPECT_THROW   (InplaceVector v(a, a + 1), ThrowOnCopy::Exception);
		EXPECT_THROW   (InplaceVector v(a, a + 5), ThrowOnCopy::Exception);
		EXPECT_THROW   (InplaceVector v(a, a + 6), hamon::bad_alloc);
	}
HAMON_WARNING_POP()
#endif
}

}	// namespace ctor_iterator_test

}	// namespace hamon_inplace_vector_test
