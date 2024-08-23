/**
 *	@file	unit_test_memory_shared_ptr_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class T>
 *	shared_ptr(weak_ptr<T>) -> shared_ptr<T>;
 *
 *	template<class T, class D>
 *	shared_ptr(unique_ptr<T, D>) -> shared_ptr<T>;
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/weak_ptr.hpp>
#include <hamon/memory/unique_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace shared_ptr_test
{

namespace ctad_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		hamon::shared_ptr<int> sp1(new int(42));
		hamon::weak_ptr<int> wp(sp1);
		hamon::shared_ptr sp2(wp);
		static_assert(hamon::is_same<decltype(sp2), hamon::shared_ptr<int>>::value, "");
		VERIFY(*sp2 == 42);
	}
	{
		hamon::unique_ptr<int> up(new int(43));
		hamon::shared_ptr sp(hamon::move(up));
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<int>>::value, "");
		VERIFY(*sp == 43);
	}
#endif
	return true;
}

#undef VERIFY

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC) && \
	!(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 130000))
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#else
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#endif

GTEST_TEST(SharedPtrTest, CtadTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace ctad_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
