/**
 *	@file	unit_test_inplace_vector_ctor_range.cpp
 *
 *	@brief	Rangeを引数に取るコンストラクタのテスト
 *
 *	template<class InputIterator>
 *	constexpr inplace_vector(InputIterator first, InputIterator last);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_inplace_vector_test
{

namespace ctor_range_test
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

template <typename T, hamon::size_t N, template <typename> class RangeWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using Range = RangeWrapper<T>;

	static_assert( hamon::is_constructible<InplaceVector, hamon::from_range_t, Range>::value, "");
	static_assert(!hamon::is_nothrow_constructible<InplaceVector, hamon::from_range_t, Range>::value, "");
	static_assert( hamon::is_implicitly_constructible<InplaceVector, hamon::from_range_t, Range>::value, "");
	static_assert(!hamon::is_trivially_constructible<InplaceVector, hamon::from_range_t, Range>::value, "");

	T a[] = {T{1}, T{2}, T{3}};
	Range r(a, a);
	{
		InplaceVector v(hamon::from_range, r);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
	}

	return true;
}

template <typename T, hamon::size_t N, template <typename> class RangeWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl_3()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using Range = RangeWrapper<T>;

	T a[] = {T{1}, T{2}, T{3}};
	Range r(a);
	{
		InplaceVector v(hamon::from_range, r);
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{2});
		VERIFY(v[2] == T{3});
	}

	return true;
}

template <typename T, template <typename> class RangeWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl()
{
	VERIFY((test_impl_0<T, 0, RangeWrapper>()));
	VERIFY((test_impl_0<T, 1, RangeWrapper>()));
	VERIFY((test_impl_0<T, 2, RangeWrapper>()));
	VERIFY((test_impl_0<T, 3, RangeWrapper>()));
	VERIFY((test_impl_0<T, 4, RangeWrapper>()));

//	VERIFY((test_impl_3<T, 0, RangeWrapper>()));
//	VERIFY((test_impl_3<T, 1, RangeWrapper>()));
//	VERIFY((test_impl_3<T, 2, RangeWrapper>()));
	VERIFY((test_impl_3<T, 3, RangeWrapper>()));
	VERIFY((test_impl_3<T, 4, RangeWrapper>()));

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl<T, test_input_range>()));
	VERIFY((test_impl<T, test_forward_range>()));
	VERIFY((test_impl<T, test_bidirectional_range>()));
	VERIFY((test_impl<T, test_random_access_range>()));
	VERIFY((test_impl<T, test_contiguous_range>()));

	VERIFY((test_impl<T, test_input_sized_range>()));
	VERIFY((test_impl<T, test_forward_sized_range>()));
	VERIFY((test_impl<T, test_bidirectional_sized_range>()));
	VERIFY((test_impl<T, test_random_access_sized_range>()));
	VERIFY((test_impl<T, test_contiguous_sized_range>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, CtorRangeTest)
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
		using Range = test_input_range<int>;
		int a[10]{};
		EXPECT_NO_THROW(InplaceVector v(hamon::from_range, Range(a, a + 0)));
		EXPECT_THROW   (InplaceVector v(hamon::from_range, Range(a, a + 1)), hamon::bad_alloc);
		EXPECT_THROW   (InplaceVector v(hamon::from_range, a), hamon::bad_alloc);
	}
	{
		using InplaceVector = hamon::inplace_vector<int, 5>;
		using Range = test_input_range<int>;
		int a[10]{};
		EXPECT_NO_THROW(InplaceVector v(hamon::from_range, Range(a, a + 5)));
		EXPECT_THROW   (InplaceVector v(hamon::from_range, Range(a, a + 6)), hamon::bad_alloc);
		EXPECT_THROW   (InplaceVector v(hamon::from_range, a), hamon::bad_alloc);
	}
	{
		using InplaceVector = hamon::inplace_vector<ThrowOnCopy, 0>;
		using Range = test_input_range<ThrowOnCopy>;
		ThrowOnCopy a[10]{};
		EXPECT_NO_THROW(InplaceVector v(hamon::from_range, Range(a, a + 0)));
		EXPECT_THROW   (InplaceVector v(hamon::from_range, Range(a, a + 1)), hamon::bad_alloc);
		EXPECT_THROW   (InplaceVector v(hamon::from_range, a), hamon::bad_alloc);
	}
	{
		using InplaceVector = hamon::inplace_vector<ThrowOnCopy, 5>;
		using Range = test_input_range<ThrowOnCopy>;
		ThrowOnCopy a[10]{};
		EXPECT_NO_THROW(InplaceVector v(hamon::from_range, Range(a, a + 0)));
		EXPECT_THROW   (InplaceVector v(hamon::from_range, Range(a, a + 1)), ThrowOnCopy::Exception);
		EXPECT_THROW   (InplaceVector v(hamon::from_range, Range(a, a + 5)), ThrowOnCopy::Exception);
		EXPECT_THROW   (InplaceVector v(hamon::from_range, Range(a, a + 6)), hamon::bad_alloc);
		EXPECT_THROW   (InplaceVector v(hamon::from_range, a), hamon::bad_alloc);
	}
HAMON_WARNING_POP()
#endif
}

}	// namespace ctor_range_test

}	// namespace hamon_inplace_vector_test
