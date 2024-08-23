/**
 *	@file	unit_test_memory_reinterpret_pointer_cast.cpp
 *
 *	@brief	reinterpret_pointer_cast のテスト
 *
 *	template<class T, class U>
 *	shared_ptr<T> reinterpret_pointer_cast(const shared_ptr<U>& r) noexcept;
 *
 *	template<class T, class U>
 *	shared_ptr<T> reinterpret_pointer_cast(shared_ptr<U>&& r) noexcept;
 */

#include <hamon/memory/reinterpret_pointer_cast.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace reinterpret_pointer_cast_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<hamon::int8_t[]> sp1(new hamon::int8_t[4]{1,1,1,1});
		static_assert(noexcept(hamon::reinterpret_pointer_cast<hamon::int32_t[]>(sp1)), "");
		auto sp2 = hamon::reinterpret_pointer_cast<hamon::int32_t[]>(sp1);
		static_assert(hamon::is_same<decltype(sp2), hamon::shared_ptr<hamon::int32_t[]>>::value, "");
		VERIFY(2 == sp1.use_count());
		VERIFY(2 == sp2.use_count());
		VERIFY(sp1.get() != nullptr);
		VERIFY(0x01010101 == sp2[0]);
	}
	{
		hamon::shared_ptr<hamon::int8_t[]> sp1(new hamon::int8_t[4]{1,1,1,1});
		static_assert(noexcept(hamon::reinterpret_pointer_cast<hamon::int32_t[]>(hamon::move(sp1))), "");
		auto sp2 = hamon::reinterpret_pointer_cast<hamon::int32_t[]>(hamon::move(sp1));
		static_assert(hamon::is_same<decltype(sp2), hamon::shared_ptr<hamon::int32_t[]>>::value, "");
		VERIFY(0 == sp1.use_count());
		VERIFY(1 == sp2.use_count());
		VERIFY(sp1.get() == nullptr);
		VERIFY(0x01010101 == sp2[0]);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, ReinterpretPointerCastTest)
{
	// reinterpret_castはconstexprにできない
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test());
}

}	// namespace reinterpret_pointer_cast_test

}	// namespace hamon_memory_test
