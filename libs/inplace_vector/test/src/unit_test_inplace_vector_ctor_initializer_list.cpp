/**
 *	@file	unit_test_inplace_vector_ctor_initializer_list.cpp
 *
 *	@brief	initializer_listを引数に取るコンストラクタのテスト
 *
 *	constexpr inplace_vector(initializer_list<T> il);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace ctor_initializer_list_test
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

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	static_assert( hamon::is_constructible<InplaceVector, std::initializer_list<T>>::value, "");
	static_assert(!hamon::is_nothrow_constructible<InplaceVector, std::initializer_list<T>>::value, "");
	static_assert( hamon::is_implicitly_constructible<InplaceVector, std::initializer_list<T>>::value, "");
	static_assert(!hamon::is_trivially_constructible<InplaceVector, std::initializer_list<T>>::value, "");

	{
		InplaceVector v({});
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_3()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v = {T{1}, T{2}, T{3}};
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{2});
		VERIFY(v[2] == T{3});
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
	VERIFY((test_impl_0<T, 4>()));

//	VERIFY((test_impl_3<T, 0>()));
//	VERIFY((test_impl_3<T, 1>()));
//	VERIFY((test_impl_3<T, 2>()));
	VERIFY((test_impl_3<T, 3>()));
	VERIFY((test_impl_3<T, 4>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, CtorInitializerListTest)
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

#if !defined(HAMON_NO_EXCEPTIONS)
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wunused-variable")
	{
		using InplaceVector = hamon::inplace_vector<int, 0>;
		EXPECT_NO_THROW(InplaceVector v({}));
		EXPECT_THROW   (InplaceVector v({1}), hamon::bad_alloc);
	}
	{
		using InplaceVector = hamon::inplace_vector<int, 5>;
		EXPECT_NO_THROW(InplaceVector v({1,2,3,4,5}));
		EXPECT_THROW   (InplaceVector v({1,2,3,4,5,6}), hamon::bad_alloc);
	}
	{
		using T = ThrowOnCopy;
		using InplaceVector = hamon::inplace_vector<T, 0>;
		EXPECT_NO_THROW(InplaceVector v({}));
		EXPECT_THROW   (InplaceVector v({T{}}), hamon::bad_alloc);
	}
	{
		using T = ThrowOnCopy;
		using InplaceVector = hamon::inplace_vector<T, 5>;
		EXPECT_NO_THROW(InplaceVector v({}));
		EXPECT_THROW   (InplaceVector v({T{}}), ThrowOnCopy::Exception);
		EXPECT_THROW   (InplaceVector v({T{},T{},T{},T{},T{}}), ThrowOnCopy::Exception);
		EXPECT_THROW   (InplaceVector v({T{},T{},T{},T{},T{},T{}}), hamon::bad_alloc);
	}
HAMON_WARNING_POP()
#endif
}

}	// namespace ctor_initializer_list_test

}	// namespace hamon_inplace_vector_test
