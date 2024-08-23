/**
 *	@file	unit_test_memory_dynamic_pointer_cast.cpp
 *
 *	@brief	dynamic_pointer_cast のテスト
 *
 *	template<class T, class U>
 *	shared_ptr<T> dynamic_pointer_cast(const shared_ptr<U>& r) noexcept;
 *
 *	template<class T, class U>
 *	shared_ptr<T> dynamic_pointer_cast(shared_ptr<U>&& r) noexcept;
 */

#include <hamon/memory/dynamic_pointer_cast.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace dynamic_pointer_cast_test
{

struct Base
{
	HAMON_CXX20_CONSTEXPR virtual ~Base() {}
};

struct Derived1 : public Base
{};

struct Derived2 : public Base
{};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
#if !defined(HAMON_NO_RTTI)
	{
		hamon::shared_ptr<Base> sp1(new Derived1);
		static_assert(noexcept(hamon::dynamic_pointer_cast<Derived1>(sp1)), "");
		auto sp2 = hamon::dynamic_pointer_cast<Derived1>(sp1);
		static_assert(hamon::is_same<decltype(sp2), hamon::shared_ptr<Derived1>>::value, "");
		VERIFY(sp2 != nullptr);
		VERIFY(2 == sp1.use_count());
		VERIFY(2 == sp2.use_count());
	}
	{
		hamon::shared_ptr<Base> sp1(new Derived1);
		static_assert(noexcept(hamon::dynamic_pointer_cast<Derived2>(sp1)), "");
		auto sp2 = hamon::dynamic_pointer_cast<Derived2>(sp1);
		static_assert(hamon::is_same<decltype(sp2), hamon::shared_ptr<Derived2>>::value, "");
		VERIFY(sp2 == nullptr);
		VERIFY(1 == sp1.use_count());
		VERIFY(0 == sp2.use_count());
	}
	{
		hamon::shared_ptr<Base> sp1(new Derived1);
		static_assert(noexcept(hamon::dynamic_pointer_cast<Derived1>(hamon::move(sp1))), "");
		auto sp2 = hamon::dynamic_pointer_cast<Derived1>(hamon::move(sp1));
		static_assert(hamon::is_same<decltype(sp2), hamon::shared_ptr<Derived1>>::value, "");
		VERIFY(sp2 != nullptr);
		VERIFY(0 == sp1.use_count());
		VERIFY(1 == sp2.use_count());
	}
	{
		hamon::shared_ptr<Base> sp1(new Derived1);
		static_assert(noexcept(hamon::dynamic_pointer_cast<Derived2>(hamon::move(sp1))), "");
		auto sp2 = hamon::dynamic_pointer_cast<Derived2>(hamon::move(sp1));
		static_assert(hamon::is_same<decltype(sp2), hamon::shared_ptr<Derived2>>::value, "");
		VERIFY(sp2 == nullptr);
		VERIFY(1 == sp1.use_count());
		VERIFY(0 == sp2.use_count());
	}
#endif
	return true;
}

#undef VERIFY

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC) && defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_CAST)
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#else
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#endif

GTEST_TEST(MemoryTest, DynamicPointerCastTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace dynamic_pointer_cast_test

}	// namespace hamon_memory_test
