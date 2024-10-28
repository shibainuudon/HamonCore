/**
 *	@file	unit_test_inplace_vector_ctor_n.cpp
 *
 *	@brief	要素数を引数に取るコンストラクタのテスト
 *
 *	constexpr explicit inplace_vector(size_type n);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace ctor_n_test
{

struct S
{
	int m_value;
	S() : m_value(42) {}
	S(S &&) = delete;
	S(S const&) = delete;
	S& operator=(S &&) = delete;
	S& operator=(S const&) = delete;
	bool operator==(S const& y) const { return m_value == y.m_value; }
};

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnDefaultCtor
{
	struct Exception{};

	ThrowOnDefaultCtor()
	{
		throw Exception{};
	}
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using SizeType = typename InplaceVector::size_type;

	static_assert( hamon::is_constructible<InplaceVector, SizeType>::value, "");
	static_assert(!hamon::is_nothrow_constructible<InplaceVector, SizeType>::value, "");
	static_assert(!hamon::is_implicitly_constructible<InplaceVector, SizeType>::value, "");
	static_assert(!hamon::is_trivially_constructible<InplaceVector, SizeType>::value, "");

	{
		InplaceVector v(0);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_1()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v(1);
		VERIFY(!v.empty());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == T{});
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_9()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v(9);
		VERIFY(!v.empty());
		VERIFY(v.size() == 9);
		VERIFY(v[0] == T{});
		VERIFY(v[1] == T{});
		VERIFY(v[2] == T{});
		VERIFY(v[3] == T{});
		VERIFY(v[4] == T{});
		VERIFY(v[5] == T{});
		VERIFY(v[6] == T{});
		VERIFY(v[7] == T{});
		VERIFY(v[8] == T{});
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl_0<T, 0>()));
	VERIFY((test_impl_0<T, 1>()));
	VERIFY((test_impl_0<T, 2>()));
	VERIFY((test_impl_0<T, 3>()));
	VERIFY((test_impl_0<T, 9>()));

//	VERIFY((test_impl_1<T, 0>()));
	VERIFY((test_impl_1<T, 1>()));
	VERIFY((test_impl_1<T, 2>()));
	VERIFY((test_impl_1<T, 3>()));
	VERIFY((test_impl_1<T, 9>()));

//	VERIFY((test_impl_9<T, 0>()));
//	VERIFY((test_impl_9<T, 1>()));
//	VERIFY((test_impl_9<T, 2>()));
//	VERIFY((test_impl_9<T, 3>()));
	VERIFY((test_impl_9<T, 9>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, CtorNTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
	EXPECT_TRUE(test<S>());

#if !defined(HAMON_NO_EXCEPTIONS)
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wunused-variable")
	{
		using InplaceVector = hamon::inplace_vector<int, 0>;
		EXPECT_NO_THROW(InplaceVector v(0));
		EXPECT_THROW   (InplaceVector v(1), hamon::bad_alloc);
	}
	{
		using InplaceVector = hamon::inplace_vector<int, 5>;
		EXPECT_NO_THROW(InplaceVector v(5));
		EXPECT_THROW   (InplaceVector v(6), hamon::bad_alloc);
	}
	{
		using InplaceVector = hamon::inplace_vector<ThrowOnDefaultCtor, 0>;
		EXPECT_NO_THROW(InplaceVector v(0));
		EXPECT_THROW   (InplaceVector v(1), hamon::bad_alloc);
	}
	{
		using InplaceVector = hamon::inplace_vector<ThrowOnDefaultCtor, 5>;
		EXPECT_NO_THROW(InplaceVector v(0));
		EXPECT_THROW   (InplaceVector v(1), ThrowOnDefaultCtor::Exception);
		EXPECT_THROW   (InplaceVector v(5), ThrowOnDefaultCtor::Exception);
		EXPECT_THROW   (InplaceVector v(6), hamon::bad_alloc);
	}
HAMON_WARNING_POP()
#endif
}

}	// namespace ctor_n_test

}	// namespace hamon_inplace_vector_test
