/**
 *	@file	unit_test_deque_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	deque(deque&&);
 *	deque(deque&&, const type_identity_t<Allocator>&);
 */

#include <hamon/deque.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/cstddef.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace ctor_move_test
{

template <typename T>
struct MyAllocator : hamon::allocator<T>
{
	using base_type = hamon::allocator<T>;

	using value_type = T;
	using size_type = hamon::size_t;
	using difference_type = hamon::ptrdiff_t;
	using pointer = T*;
	using propagate_on_container_move_assignment = hamon::false_type;
#if HAMON_CXX_STANDARD < 20
	template <typename U>
	struct rebind
	{
		using other = MyAllocator<U>;
	};
#endif
	using is_always_equal = hamon::false_type;

	HAMON_CXX11_CONSTEXPR MyAllocator() noexcept
		: base_type()
	{}

	HAMON_CXX11_CONSTEXPR MyAllocator(const MyAllocator&) noexcept
		: base_type()
	{}

	template <typename U>
	HAMON_CXX11_CONSTEXPR MyAllocator(const MyAllocator<U>&) noexcept
		: base_type()
	{}

	HAMON_CXX14_CONSTEXPR MyAllocator&
	operator=(const MyAllocator&) noexcept { return *this; }

	HAMON_CXX11_CONSTEXPR bool operator==(MyAllocator const&) const
	{
		return false;
	}

	HAMON_CXX11_CONSTEXPR bool operator!=(MyAllocator const& rhs) const
	{
		return !(*this == rhs);
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, template <typename> class TAllocator>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Allocator = TAllocator<T>;
	using Deque = hamon::deque<T, Allocator>;

	{
		Deque v1{1,2,3};
		Deque v2{hamon::move(v1)};
		VERIFY(v2.size() == 3);
		VERIFY(v2[0] == 1);
		VERIFY(v2[1] == 2);
		VERIFY(v2[2] == 3);
	}
	{
		Deque v1{1,2,3};
		Allocator alloc;
		Deque v2{hamon::move(v1), alloc};
		VERIFY(v2.size() == 3);
		VERIFY(v2[0] == 1);
		VERIFY(v2[1] == 2);
		VERIFY(v2[2] == 3);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, CtorMoveTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, hamon::allocator>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, MyAllocator>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<unsigned char, hamon::allocator>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<unsigned char, MyAllocator>()));
}

}	// namespace ctor_move_test

}	// namespace hamon_deque_test
