/**
 *	@file	unit_test_inplace_vector_ctor_n_value.cpp
 *
 *	@brief	要素数と値を引数に取るコンストラクタのテスト
 *
 *	constexpr inplace_vector(size_type n, const T& value);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace ctor_n_value_test
{

struct S
{
	int m_value;
	S() = delete;
	S(int v) : m_value(v) {}
	S(S &&);
	S(S const&) = default;
	S& operator=(S &&) = delete;
	S& operator=(S const&) = delete;
	bool operator==(S const& y) const { return m_value == y.m_value; }
};

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnCopy
{
	struct Exception{};

	ThrowOnCopy(int)
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
	using SizeType = typename InplaceVector::size_type;

	static_assert( hamon::is_constructible<InplaceVector, SizeType, T const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<InplaceVector, SizeType, T const&>::value, "");
//	static_assert( hamon::is_implicitly_constructible<InplaceVector, SizeType, T const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<InplaceVector, SizeType, T const&>::value, "");

	{
		InplaceVector v(0, T{40});
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
		InplaceVector v(1, T{41});
		VERIFY(!v.empty());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == T{41});
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_9()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v(9, T{42});
		VERIFY(!v.empty());
		VERIFY(v.size() == 9);
		VERIFY(v[0] == T{42});
		VERIFY(v[1] == T{42});
		VERIFY(v[2] == T{42});
		VERIFY(v[3] == T{42});
		VERIFY(v[4] == T{42});
		VERIFY(v[5] == T{42});
		VERIFY(v[6] == T{42});
		VERIFY(v[7] == T{42});
		VERIFY(v[8] == T{42});
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

GTEST_TEST(InplaceVectorTest, CtorNValueTest)
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
		EXPECT_NO_THROW(InplaceVector v(0, 42));
		EXPECT_THROW   (InplaceVector v(1, 42), hamon::bad_alloc);
	}
	{
		using InplaceVector = hamon::inplace_vector<int, 5>;
		EXPECT_NO_THROW(InplaceVector v(5, 42));
		EXPECT_THROW   (InplaceVector v(6, 42), hamon::bad_alloc);
	}
	{
		using InplaceVector = hamon::inplace_vector<ThrowOnCopy, 0>;
		EXPECT_NO_THROW(InplaceVector v(0, ThrowOnCopy{42}));
		EXPECT_THROW   (InplaceVector v(1, ThrowOnCopy{42}), hamon::bad_alloc);
	}
	{
		using InplaceVector = hamon::inplace_vector<ThrowOnCopy, 5>;
		EXPECT_NO_THROW(InplaceVector v(0, ThrowOnCopy{42}));
		EXPECT_THROW   (InplaceVector v(1, ThrowOnCopy{42}), ThrowOnCopy::Exception);
		EXPECT_THROW   (InplaceVector v(5, ThrowOnCopy{42}), ThrowOnCopy::Exception);
		EXPECT_THROW   (InplaceVector v(6, ThrowOnCopy{42}), hamon::bad_alloc);
	}
HAMON_WARNING_POP()
#endif
}

}	// namespace ctor_n_value_test

}	// namespace hamon_inplace_vector_test
