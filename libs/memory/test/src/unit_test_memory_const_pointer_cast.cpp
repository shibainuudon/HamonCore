﻿/**
 *	@file	unit_test_memory_const_pointer_cast.cpp
 *
 *	@brief	const_pointer_cast のテスト
 *
 *	template<class T, class U>
 *	shared_ptr<T> const_pointer_cast(const shared_ptr<U>& r) noexcept;
 *
 *	template<class T, class U>
 *	shared_ptr<T> const_pointer_cast(shared_ptr<U>&& r) noexcept;
 */

#include <hamon/memory/const_pointer_cast.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace const_pointer_cast_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int const> sp1(new int(42));
		static_assert(noexcept(hamon::const_pointer_cast<int>(sp1)), "");
		auto sp2 = hamon::const_pointer_cast<int>(sp1);
		static_assert(hamon::is_same<decltype(sp2), hamon::shared_ptr<int>>::value, "");
		VERIFY(sp1 == sp2);
		VERIFY(sp1.get() != nullptr);
		VERIFY(2 == sp1.use_count());
		VERIFY(2 == sp2.use_count());
	}
	{
		hamon::shared_ptr<int const> sp1(new int(42));
		static_assert(noexcept(hamon::const_pointer_cast<int>(hamon::move(sp1))), "");
		auto sp2 = hamon::const_pointer_cast<int>(hamon::move(sp1));
		static_assert(hamon::is_same<decltype(sp2), hamon::shared_ptr<int>>::value, "");
		VERIFY(sp1 != sp2);
		VERIFY(sp1.get() == nullptr);
		VERIFY(0 == sp1.use_count());
		VERIFY(1 == sp2.use_count());
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

GTEST_TEST(MemoryTest, ConstPointerCastTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace const_pointer_cast_test

}	// namespace hamon_memory_test
