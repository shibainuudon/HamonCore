/**
 *	@file	unit_test_inplace_vector_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr inplace_vector() noexcept;
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace ctor_default_test
{

struct S
{
	S() = delete;
	S(S &&) = delete;
	S(S const&) = delete;
	S& operator=(S &&) = delete;
	S& operator=(S const&) = delete;
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
HAMON_CXX14_CONSTEXPR bool test_impl()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	static_assert( hamon::is_default_constructible<InplaceVector>::value, "");
	static_assert( hamon::is_nothrow_default_constructible<InplaceVector>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<InplaceVector>::value, "");
	static_assert(!hamon::is_trivially_default_constructible<InplaceVector>::value, "");

	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.max_size() == N);
		VERIFY(v.capacity() == N);
	}
	{
		InplaceVector v{};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.max_size() == N);
		VERIFY(v.capacity() == N);
	}
	{
		InplaceVector v = {};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.max_size() == N);
		VERIFY(v.capacity() == N);
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl<T, 0>()));
	VERIFY((test_impl<T, 1>()));
	VERIFY((test_impl<T, 2>()));
	VERIFY((test_impl<T, 10>()));
	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, CtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<S>());
#if !defined(HAMON_NO_EXCEPTIONS)
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<ThrowOnDefaultCtor>());
#endif
}

}	// namespace ctor_default_test

}	// namespace hamon_inplace_vector_test
