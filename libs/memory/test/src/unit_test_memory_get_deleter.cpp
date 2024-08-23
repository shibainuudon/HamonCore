/**
 *	@file	unit_test_memory_get_deleter.cpp
 *
 *	@brief	get_deleter のテスト
 *
 *	template<class D, class T>
 *	D* get_deleter(const shared_ptr<T>& p) noexcept;
 */

#include <hamon/memory/get_deleter.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace get_deleter_test
{

struct Deleter1
{
	int value;

	HAMON_CXX11_CONSTEXPR Deleter1(int v) : value(v) {}

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete p; }
};

struct Deleter2
{
	int value;

	HAMON_CXX11_CONSTEXPR Deleter2(int v) : value(v) {}

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete[] p; }
};

struct Deleter3
{
	int value;

	HAMON_CXX11_CONSTEXPR Deleter3(int v) : value(v) {}

	HAMON_CXX14_CONSTEXPR void operator()(hamon::nullptr_t) const {}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int> sp(new int, Deleter1{42});
		static_assert(noexcept(hamon::get_deleter<Deleter1>(sp)), "");
		static_assert(hamon::is_same<decltype(hamon::get_deleter<Deleter1>(sp)), Deleter1*>::value, "");
		VERIFY(hamon::get_deleter<Deleter1>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter1>(sp)->value == 42);
		VERIFY(hamon::get_deleter<Deleter2>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter3>(sp) == nullptr);
	}
	{
		hamon::shared_ptr<int[]> sp(new int[3]{1,2,3}, Deleter2{43});
		static_assert(noexcept(hamon::get_deleter<Deleter2>(sp)), "");
		static_assert(hamon::is_same<decltype(hamon::get_deleter<Deleter2>(sp)), Deleter2*>::value, "");
		VERIFY(hamon::get_deleter<Deleter1>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp)->value == 43);
		VERIFY(hamon::get_deleter<Deleter3>(sp) == nullptr);
	}
	{
		hamon::shared_ptr<int[3]> sp(new int[3]{1,2,3}, Deleter2{44});
		static_assert(noexcept(hamon::get_deleter<Deleter2>(sp)), "");
		static_assert(hamon::is_same<decltype(hamon::get_deleter<Deleter2>(sp)), Deleter2*>::value, "");
		VERIFY(hamon::get_deleter<Deleter1>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp)->value == 44);
		VERIFY(hamon::get_deleter<Deleter3>(sp) == nullptr);
	}
	{
		hamon::allocator<char> a;
		hamon::shared_ptr<int> sp(new int, Deleter1{42}, a);
		static_assert(noexcept(hamon::get_deleter<Deleter1>(sp)), "");
		static_assert(hamon::is_same<decltype(hamon::get_deleter<Deleter1>(sp)), Deleter1*>::value, "");
		VERIFY(hamon::get_deleter<Deleter1>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter1>(sp)->value == 42);
		VERIFY(hamon::get_deleter<Deleter2>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter3>(sp) == nullptr);
	}
	{
		hamon::allocator<char> a;
		hamon::shared_ptr<int[]> sp(new int[3]{1,2,3}, Deleter2{43}, a);
		static_assert(noexcept(hamon::get_deleter<Deleter2>(sp)), "");
		static_assert(hamon::is_same<decltype(hamon::get_deleter<Deleter2>(sp)), Deleter2*>::value, "");
		VERIFY(hamon::get_deleter<Deleter1>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp)->value == 43);
		VERIFY(hamon::get_deleter<Deleter3>(sp) == nullptr);
	}
	{
		hamon::allocator<char> a;
		hamon::shared_ptr<int[3]> sp(new int[3]{1,2,3}, Deleter2{44}, a);
		static_assert(noexcept(hamon::get_deleter<Deleter2>(sp)), "");
		static_assert(hamon::is_same<decltype(hamon::get_deleter<Deleter2>(sp)), Deleter2*>::value, "");
		VERIFY(hamon::get_deleter<Deleter1>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp)->value == 44);
		VERIFY(hamon::get_deleter<Deleter3>(sp) == nullptr);
	}
	{
		hamon::shared_ptr<int> sp(nullptr, Deleter3{42});
		static_assert(noexcept(hamon::get_deleter<Deleter3>(sp)), "");
		static_assert(hamon::is_same<decltype(hamon::get_deleter<Deleter3>(sp)), Deleter3*>::value, "");
		VERIFY(hamon::get_deleter<Deleter1>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter3>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter3>(sp)->value == 42);
	}
	{
		hamon::shared_ptr<int[]> sp(nullptr, Deleter3{43});
		static_assert(noexcept(hamon::get_deleter<Deleter3>(sp)), "");
		static_assert(hamon::is_same<decltype(hamon::get_deleter<Deleter3>(sp)), Deleter3*>::value, "");
		VERIFY(hamon::get_deleter<Deleter1>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter3>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter3>(sp)->value == 43);
	}
	{
		hamon::shared_ptr<int[2]> sp(nullptr, Deleter3{44});
		static_assert(noexcept(hamon::get_deleter<Deleter3>(sp)), "");
		static_assert(hamon::is_same<decltype(hamon::get_deleter<Deleter3>(sp)), Deleter3*>::value, "");
		VERIFY(hamon::get_deleter<Deleter1>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter3>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter3>(sp)->value == 44);
	}
	{
		hamon::allocator<char> a;
		hamon::shared_ptr<int> sp(nullptr, Deleter3{42}, a);
		static_assert(noexcept(hamon::get_deleter<Deleter3>(sp)), "");
		static_assert(hamon::is_same<decltype(hamon::get_deleter<Deleter3>(sp)), Deleter3*>::value, "");
		VERIFY(hamon::get_deleter<Deleter1>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter3>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter3>(sp)->value == 42);
	}
	{
		hamon::allocator<char> a;
		hamon::shared_ptr<int[]> sp(nullptr, Deleter3{43}, a);
		static_assert(noexcept(hamon::get_deleter<Deleter3>(sp)), "");
		static_assert(hamon::is_same<decltype(hamon::get_deleter<Deleter3>(sp)), Deleter3*>::value, "");
		VERIFY(hamon::get_deleter<Deleter1>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter3>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter3>(sp)->value == 43);
	}
	{
		hamon::allocator<char> a;
		hamon::shared_ptr<int[2]> sp(nullptr, Deleter3{44}, a);
		static_assert(noexcept(hamon::get_deleter<Deleter3>(sp)), "");
		static_assert(hamon::is_same<decltype(hamon::get_deleter<Deleter3>(sp)), Deleter3*>::value, "");
		VERIFY(hamon::get_deleter<Deleter1>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter3>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter3>(sp)->value == 44);
	}
	{
		hamon::unique_ptr<int, Deleter1> up(new int, Deleter1{42});
		hamon::shared_ptr<int> sp(hamon::move(up));
		static_assert(noexcept(hamon::get_deleter<Deleter1>(sp)), "");
		static_assert(hamon::is_same<decltype(hamon::get_deleter<Deleter1>(sp)), Deleter1*>::value, "");
		VERIFY(hamon::get_deleter<Deleter1>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter1>(sp)->value == 42);
		VERIFY(hamon::get_deleter<Deleter2>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter3>(sp) == nullptr);
	}
	{
		hamon::unique_ptr<int[], Deleter2> up(new int[3]{1,2,3}, Deleter2{43});
		hamon::shared_ptr<int[]> sp(hamon::move(up));
		static_assert(noexcept(hamon::get_deleter<Deleter2>(sp)), "");
		static_assert(hamon::is_same<decltype(hamon::get_deleter<Deleter2>(sp)), Deleter2*>::value, "");
		VERIFY(hamon::get_deleter<Deleter1>(sp) == nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp)->value == 43);
		VERIFY(hamon::get_deleter<Deleter3>(sp) == nullptr);
	}
	{
		hamon::shared_ptr<int> sp;
		VERIFY(hamon::get_deleter<Deleter1>(sp) == nullptr);
		sp.reset(new int, Deleter1{42});
		VERIFY(hamon::get_deleter<Deleter1>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter1>(sp)->value == 42);
	}
	{
		hamon::shared_ptr<int[]> sp;
		VERIFY(hamon::get_deleter<Deleter2>(sp) == nullptr);
		sp.reset(new int[3]{1,2,3}, Deleter2{42});
		VERIFY(hamon::get_deleter<Deleter2>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp)->value == 42);
	}
	{
		hamon::shared_ptr<int[3]> sp;
		VERIFY(hamon::get_deleter<Deleter2>(sp) == nullptr);
		sp.reset(new int[3]{1,2,3}, Deleter2{42});
		VERIFY(hamon::get_deleter<Deleter2>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp)->value == 42);
	}
	{
		hamon::allocator<char> a;
		hamon::shared_ptr<int> sp;
		VERIFY(hamon::get_deleter<Deleter1>(sp) == nullptr);
		sp.reset(new int, Deleter1{42}, a);
		VERIFY(hamon::get_deleter<Deleter1>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter1>(sp)->value == 42);
	}
	{
		hamon::allocator<char> a;
		hamon::shared_ptr<int[]> sp;
		VERIFY(hamon::get_deleter<Deleter2>(sp) == nullptr);
		sp.reset(new int[3]{1,2,3}, Deleter2{42}, a);
		VERIFY(hamon::get_deleter<Deleter2>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp)->value == 42);
	}
	{
		hamon::allocator<char> a;
		hamon::shared_ptr<int[3]> sp;
		VERIFY(hamon::get_deleter<Deleter2>(sp) == nullptr);
		sp.reset(new int[3]{1,2,3}, Deleter2{42}, a);
		VERIFY(hamon::get_deleter<Deleter2>(sp) != nullptr);
		VERIFY(hamon::get_deleter<Deleter2>(sp)->value == 42);
	}
	return true;
}

#undef VERIFY

// P2738R1 : "constexpr cast from void*" (C++26)が実装されれば定数に評価できる
#if 0 && defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC) && \
	!(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 130000))
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#else
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#endif

GTEST_TEST(MemoryTest, GetDeleterTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace get_deleter_test

}	// namespace hamon_memory_test
