/**
 *	@file	unit_test_memory_make_shared_for_overwrite.cpp
 *
 *	@brief	make_shared_for_overwrite のテスト
 *
 *	template<class T>
 *	shared_ptr<T> make_shared_for_overwrite();
 *
 *	template<class T>
 *	shared_ptr<T> make_shared_for_overwrite(size_t N);
 */

#include <hamon/memory/make_shared_for_overwrite.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace make_shared_for_overwrite_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	// (1)
	{
		auto sp = hamon::make_shared_for_overwrite<int>();
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<int>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
	}
	{
		auto sp = hamon::make_shared_for_overwrite<double[3]>();
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<double[3]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
	}
	{
		auto sp = hamon::make_shared_for_overwrite<int[2][3]>();
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<int[2][3]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
	}
	{
		auto sp = hamon::make_shared_for_overwrite<float[4][3][2]>();
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<float[4][3][2]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
	}

	// (2)
	{
		auto sp = hamon::make_shared_for_overwrite<long[]>(3);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<long[]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
	}
	{
		auto sp = hamon::make_shared_for_overwrite<long[][2]>(3);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<long[][2]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
	}
	{
		auto sp = hamon::make_shared_for_overwrite<int[][2][3]>(4);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<int[][2][3]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
	}
	return true;
}

#undef VERIFY

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC) && \
	!(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 130000))
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#else
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#endif

GTEST_TEST(MemoryTest, MakeSharedForOverwriteTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace make_shared_for_overwrite_test

}	// namespace hamon_memory_test
