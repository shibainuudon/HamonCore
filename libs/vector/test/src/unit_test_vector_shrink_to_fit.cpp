/**
 *	@file	unit_test_vector_shrink_to_fit.cpp
 *
 *	@brief	shrink_to_fit のテスト
 *
 *	constexpr void shrink_to_fit();
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace shrink_to_fit_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Vector = hamon::vector<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().shrink_to_fit()),
		void
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Vector&>().shrink_to_fit()), "");

	{
		Vector v{1,2,3,4,5};
		VERIFY(v.size() == 5);
		VERIFY(v.capacity() >= v.size());
		v.shrink_to_fit();
		VERIFY(v.size() == 5);
		VERIFY(v.capacity() == v.size());

		v.pop_back();
		VERIFY(v.size() == 4);
		VERIFY(v.capacity() >= v.size());
		v.shrink_to_fit();
		VERIFY(v.size() == 4);
		VERIFY(v.capacity() == v.size());

		v.clear();
		VERIFY(v.size() == 0);
		VERIFY(v.capacity() >= v.size());
		v.shrink_to_fit();
		VERIFY(v.size() == 0);
		VERIFY(v.capacity() == v.size());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, ShrinkToFitTest)
{
#if !(defined(HAMON_CLANG_VERSION) && defined(HAMON_STDLIB_DINKUMWARE))	// win-clangだとconstexprにできない
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
#else
	EXPECT_TRUE(test<int>());
	EXPECT_TRUE(test<unsigned char>());
	EXPECT_TRUE(test<float>());
#endif
}

}	// namespace shrink_to_fit_test

}	// namespace hamon_vector_test
