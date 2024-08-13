/**
 *	@file	unit_test_memory_uninitialized_construct_using_allocator.cpp
 *
 *	@brief	uninitialized_construct_using_allocator のテスト
 */

#include <hamon/memory/uninitialized_construct_using_allocator.hpp>
#include <hamon/memory/allocator_arg_t.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/array.hpp>
#include <hamon/pair.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace uninitialized_construct_using_allocator_test
{

enum class RefType
{
	LValue,
	ConstLValue,
	RValue,
	ConstRValue,
	None,
};

struct MyAlloc {};

struct FirstAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR FirstAlloc() noexcept
		: n(-1)
	{}

	HAMON_CXX11_CONSTEXPR FirstAlloc(int) noexcept
		: n(-1)
	{}

	HAMON_CXX11_CONSTEXPR FirstAlloc(hamon::allocator_arg_t, MyAlloc const&) noexcept
		: n(42)
	{}

	HAMON_CXX11_CONSTEXPR FirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int& i) noexcept
		: n(i), ref_type(RefType::LValue)
	{}

	HAMON_CXX11_CONSTEXPR FirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int&& i) noexcept
		: n(i), ref_type(RefType::RValue)
	{}

	HAMON_CXX11_CONSTEXPR FirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int const& i) noexcept
		: n(i), ref_type(RefType::ConstLValue)
	{}

	HAMON_CXX11_CONSTEXPR FirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int const&& i) noexcept
		: n(i), ref_type(RefType::ConstRValue)
	{}

	HAMON_CXX11_CONSTEXPR FirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int i, int j) noexcept
		: n(i+j)
	{}

	int n;
	RefType	ref_type = RefType::None;
};

struct LastAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR LastAlloc() noexcept
		: n(-1)
	{}

	HAMON_CXX11_CONSTEXPR LastAlloc(int) noexcept
		: n(-1)
	{}

	HAMON_CXX11_CONSTEXPR LastAlloc(MyAlloc const&) noexcept
		: n(43)
	{}

	HAMON_CXX11_CONSTEXPR LastAlloc(int& i, MyAlloc const&) noexcept
		: n(i), ref_type(RefType::LValue)
	{}

	HAMON_CXX11_CONSTEXPR LastAlloc(int&& i, MyAlloc const&) noexcept
		: n(i), ref_type(RefType::RValue)
	{}

	HAMON_CXX11_CONSTEXPR LastAlloc(int const& i, MyAlloc const&) noexcept
		: n(i), ref_type(RefType::ConstLValue)
	{}

	HAMON_CXX11_CONSTEXPR LastAlloc(int const&& i, MyAlloc const&) noexcept
		: n(i), ref_type(RefType::ConstRValue)
	{}

	HAMON_CXX11_CONSTEXPR LastAlloc(int i, int j, MyAlloc const&) noexcept
		: n(i+j)
	{}

	int n;
	RefType	ref_type = RefType::None;
};

struct NoAlloc
{
	HAMON_CXX11_CONSTEXPR NoAlloc() noexcept
		: n(44)
	{}

	HAMON_CXX11_CONSTEXPR NoAlloc(int& i) noexcept
		: n(i), ref_type(RefType::LValue)
	{}

	HAMON_CXX11_CONSTEXPR NoAlloc(int&& i) noexcept
		: n(i), ref_type(RefType::RValue)
	{}

	HAMON_CXX11_CONSTEXPR NoAlloc(int const& i) noexcept
		: n(i), ref_type(RefType::ConstLValue)
	{}

	HAMON_CXX11_CONSTEXPR NoAlloc(int const&& i) noexcept
		: n(i), ref_type(RefType::ConstRValue)
	{}

	HAMON_CXX11_CONSTEXPR NoAlloc(int i, int j) noexcept
		: n(i+j)
	{}

	HAMON_CXX11_CONSTEXPR NoAlloc(hamon::allocator_arg_t, MyAlloc const&, int) noexcept
		: n(-1)
	{}

	HAMON_CXX11_CONSTEXPR NoAlloc(int, MyAlloc const&) noexcept
		: n(-1)
	{}

	int n;
	RefType	ref_type = RefType::None;
};

struct ConvertibleToPair
{
	HAMON_CXX11_CONSTEXPR operator hamon::pair<int, int>() const { return {1, 2}; }
};

GTEST_TEST(MemoryTest, UninitializedConstructUsingAllocatorTest)
{
	// non-pair overload

	// (const Alloc&, Args&&...)
	{
		hamon::allocator<int> a{};
		auto* ptr = a.allocate(1);
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{});
		static_assert(hamon::is_same<decltype(t), int*>::value, "");
		EXPECT_EQ(*t, 0);
		a.deallocate(ptr, 1);
	}
	{
		hamon::allocator<FirstAlloc> a{};
		auto* ptr = a.allocate(1);
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{});
		static_assert(hamon::is_same<decltype(t), FirstAlloc*>::value, "");
		EXPECT_EQ(t->n, 42);
		a.deallocate(ptr, 1);
	}
	{
		hamon::allocator<LastAlloc> a{};
		auto* ptr = a.allocate(1);
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{});
		static_assert(hamon::is_same<decltype(t), LastAlloc*>::value, "");
		EXPECT_EQ(t->n, 43);
		a.deallocate(ptr, 1);
	}
	{
		hamon::allocator<NoAlloc> a{};
		auto* ptr = a.allocate(1);
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{});
		static_assert(hamon::is_same<decltype(t), NoAlloc*>::value, "");
		EXPECT_EQ(t->n, 44);
		a.deallocate(ptr, 1);
	}
	{
		hamon::allocator<int> a{};
		auto* ptr = a.allocate(1);
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{}, 10);
		static_assert(hamon::is_same<decltype(t), int*>::value, "");
		EXPECT_EQ(*t, 10);
		a.deallocate(ptr, 1);
	}
	{
		hamon::allocator<FirstAlloc> a{};
		auto* ptr = a.allocate(1);
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{}, 11);
		static_assert(hamon::is_same<decltype(t), FirstAlloc*>::value, "");
		EXPECT_EQ(t->n, 11);
		a.deallocate(ptr, 1);
	}
	{
		hamon::allocator<LastAlloc> a{};
		auto* ptr = a.allocate(1);
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{}, 12);
		static_assert(hamon::is_same<decltype(t), LastAlloc*>::value, "");
		EXPECT_EQ(t->n, 12);
		a.deallocate(ptr, 1);
	}
	{
		hamon::allocator<NoAlloc> a{};
		auto* ptr = a.allocate(1);
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{}, 13);
		static_assert(hamon::is_same<decltype(t), NoAlloc*>::value, "");
		EXPECT_EQ(t->n, 13);
		a.deallocate(ptr, 1);
	}
	{
		hamon::allocator<FirstAlloc> a{};
		auto* ptr = a.allocate(1);
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{}, 10, 11);
		static_assert(hamon::is_same<decltype(t), FirstAlloc*>::value, "");
		EXPECT_EQ(t->n, 21);
		a.deallocate(ptr, 1);
	}
	{
		hamon::allocator<LastAlloc> a{};
		auto* ptr = a.allocate(1);
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{}, 12, 13);
		static_assert(hamon::is_same<decltype(t), LastAlloc*>::value, "");
		EXPECT_EQ(t->n, 25);
		a.deallocate(ptr, 1);
	}
	{
		hamon::allocator<NoAlloc> a{};
		auto* ptr = a.allocate(1);
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{}, 14, 15);
		static_assert(hamon::is_same<decltype(t), NoAlloc*>::value, "");
		EXPECT_EQ(t->n, 29);
		a.deallocate(ptr, 1);
	}

	// pair overloads

	// (const Alloc&, piecewise_construct_t, Tuple1&&, Tuple2&&)
	{
		hamon::allocator<hamon::pair<int, FirstAlloc>> a{};
		auto* ptr = a.allocate(1);
		auto t = hamon::uninitialized_construct_using_allocator(
			ptr,
			MyAlloc{},
			hamon::piecewise_construct_t{},
			hamon::make_tuple(1),
			hamon::make_tuple(2));
		static_assert(hamon::is_same<decltype(t), hamon::pair<int, FirstAlloc>*>::value, "");
		EXPECT_EQ(t->first,    1);
		EXPECT_EQ(t->second.n, 2);
		a.deallocate(ptr, 1);
	}
	{
		hamon::allocator<hamon::pair<LastAlloc, NoAlloc>> a{};
		auto* ptr = a.allocate(1);
		auto t = hamon::uninitialized_construct_using_allocator(
			ptr,
			MyAlloc{},
			hamon::piecewise_construct_t{},
			hamon::make_tuple(),
			hamon::make_tuple(3, 4));
		static_assert(hamon::is_same<decltype(t), hamon::pair<LastAlloc, NoAlloc>*>::value, "");
		EXPECT_EQ(t->first.n,  43);
		EXPECT_EQ(t->second.n, 7);
		a.deallocate(ptr, 1);
	}

	// (const Alloc&)
	{
		hamon::allocator<hamon::pair<FirstAlloc, LastAlloc>> a{};
		auto* ptr = a.allocate(1);
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{});
		static_assert(hamon::is_same<decltype(t), hamon::pair<FirstAlloc, LastAlloc>*>::value, "");
		EXPECT_EQ(t->first.n,  42);
		EXPECT_EQ(t->second.n, 43);
		a.deallocate(ptr, 1);
	}

	// (const Alloc&, U&&, V&&)
	{
		hamon::allocator<hamon::pair<NoAlloc, LastAlloc>> a{};
		auto* ptr = a.allocate(1);
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{}, 5, 6);
		static_assert(hamon::is_same<decltype(t), hamon::pair<NoAlloc, LastAlloc>*>::value, "");
		EXPECT_EQ(t->first.n,  5);
		EXPECT_EQ(t->first.ref_type, RefType::RValue);
		EXPECT_EQ(t->second.n, 6);
		EXPECT_EQ(t->second.ref_type, RefType::RValue);
		a.deallocate(ptr, 1);
	}

	// (const Alloc&, pair<U, V>&)
	{
		hamon::allocator<hamon::pair<FirstAlloc, NoAlloc>> a{};
		auto* ptr = a.allocate(1);
		hamon::pair<int, int> p{7, 8};
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{}, p);
		static_assert(hamon::is_same<decltype(t), hamon::pair<FirstAlloc, NoAlloc>*>::value, "");
		EXPECT_EQ(t->first.n,  7);
		EXPECT_EQ(t->first.ref_type, RefType::LValue);
		EXPECT_EQ(t->second.n, 8);
		EXPECT_EQ(t->second.ref_type, RefType::LValue);
		a.deallocate(ptr, 1);
	}

	// (const Alloc&, const pair<U, V>&)
	{
		hamon::allocator<hamon::pair<LastAlloc, FirstAlloc>> a{};
		auto* ptr = a.allocate(1);
		hamon::pair<int, int> const p{7, 8};
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{}, p);
		static_assert(hamon::is_same<decltype(t), hamon::pair<LastAlloc, FirstAlloc>*>::value, "");
		EXPECT_EQ(t->first.n,  7);
		EXPECT_EQ(t->first.ref_type, RefType::ConstLValue);
		EXPECT_EQ(t->second.n, 8);
		EXPECT_EQ(t->second.ref_type, RefType::ConstLValue);
		a.deallocate(ptr, 1);
	}

	// (const Alloc&, pair<U, V>&&)
	{
		hamon::allocator<hamon::pair<NoAlloc, FirstAlloc>> a{};
		auto* ptr = a.allocate(1);
		hamon::pair<int, int> p{7, 8};
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{}, hamon::move(p));
		static_assert(hamon::is_same<decltype(t), hamon::pair<NoAlloc, FirstAlloc>*>::value, "");
		EXPECT_EQ(t->first.n,  7);
		EXPECT_EQ(t->first.ref_type, RefType::RValue);
		EXPECT_EQ(t->second.n, 8);
		EXPECT_EQ(t->second.ref_type, RefType::RValue);
		a.deallocate(ptr, 1);
	}

	// (const Alloc&, const pair<U, V>&&)
	{
		hamon::allocator<hamon::pair<FirstAlloc, LastAlloc>> a{};
		auto* ptr = a.allocate(1);
		hamon::pair<int, int> const p{7, 8};
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{}, hamon::move(p));
		static_assert(hamon::is_same<decltype(t), hamon::pair<FirstAlloc, LastAlloc>*>::value, "");
		EXPECT_EQ(t->first.n,  7);
		EXPECT_EQ(t->first.ref_type, RefType::ConstRValue);
		EXPECT_EQ(t->second.n, 8);
		EXPECT_EQ(t->second.ref_type, RefType::ConstRValue);
		a.deallocate(ptr, 1);
	}

	// (const Alloc&, PairLike&&)
	{
		hamon::allocator<hamon::pair<FirstAlloc, LastAlloc>> a{};
		auto* ptr = a.allocate(1);
		hamon::array<int, 2> p{9, 10};
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{}, p);
		static_assert(hamon::is_same<decltype(t), hamon::pair<FirstAlloc, LastAlloc>*>::value, "");
		EXPECT_EQ(t->first.n,  9);
		EXPECT_EQ(t->first.ref_type, RefType::LValue);
		EXPECT_EQ(t->second.n, 10);
		EXPECT_EQ(t->second.ref_type, RefType::LValue);
		a.deallocate(ptr, 1);
	}
	{
		hamon::allocator<hamon::pair<FirstAlloc, LastAlloc>> a{};
		auto* ptr = a.allocate(1);
		hamon::array<int, 2> const p{11, 12};
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{}, p);
		static_assert(hamon::is_same<decltype(t), hamon::pair<FirstAlloc, LastAlloc>*>::value, "");
		EXPECT_EQ(t->first.n,  11);
		EXPECT_EQ(t->first.ref_type, RefType::ConstLValue);
		EXPECT_EQ(t->second.n, 12);
		EXPECT_EQ(t->second.ref_type, RefType::ConstLValue);
		a.deallocate(ptr, 1);
	}
	{
		hamon::allocator<hamon::pair<FirstAlloc, LastAlloc>> a{};
		auto* ptr = a.allocate(1);
		hamon::array<int, 2> p{13, 14};
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{}, hamon::move(p));
		static_assert(hamon::is_same<decltype(t), hamon::pair<FirstAlloc, LastAlloc>*>::value, "");
		EXPECT_EQ(t->first.n,  13);
		EXPECT_EQ(t->first.ref_type, RefType::RValue);
		EXPECT_EQ(t->second.n, 14);
		EXPECT_EQ(t->second.ref_type, RefType::RValue);
		a.deallocate(ptr, 1);
	}
	{
		hamon::allocator<hamon::pair<FirstAlloc, LastAlloc>> a{};
		auto* ptr = a.allocate(1);
		hamon::array<int, 2> const p{15, 16};
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{}, hamon::move(p));
		static_assert(hamon::is_same<decltype(t), hamon::pair<FirstAlloc, LastAlloc>*>::value, "");
		EXPECT_EQ(t->first.n,  15);
		EXPECT_EQ(t->first.ref_type, RefType::ConstRValue);
		EXPECT_EQ(t->second.n, 16);
		EXPECT_EQ(t->second.ref_type, RefType::ConstRValue);
		a.deallocate(ptr, 1);
	}

	// (const Alloc&, U&&)
	{
		hamon::allocator<hamon::pair<int, int>> a{};
		auto* ptr = a.allocate(1);
		ConvertibleToPair ctp;
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{}, ctp);
		static_assert(hamon::is_same<decltype(t), hamon::pair<int, int>*>::value, "");
		EXPECT_EQ(t->first,  1);
		EXPECT_EQ(t->second, 2);
		a.deallocate(ptr, 1);
	}
	{
		hamon::allocator<hamon::pair<int, int>> a{};
		auto* ptr = a.allocate(1);
		ConvertibleToPair ctp;
		auto t = hamon::uninitialized_construct_using_allocator(ptr, MyAlloc{}, hamon::move(ctp));
		static_assert(hamon::is_same<decltype(t), hamon::pair<int, int>*>::value, "");
		EXPECT_EQ(t->first,  1);
		EXPECT_EQ(t->second, 2);
		a.deallocate(ptr, 1);
	}
}

}	// namespace uninitialized_construct_using_allocator_test

}	// namespace hamon_memory_test
