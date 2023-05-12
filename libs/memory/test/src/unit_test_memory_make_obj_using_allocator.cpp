/**
 *	@file	unit_test_memory_make_obj_using_allocator.cpp
 *
 *	@brief	make_obj_using_allocator のテスト
 */

#include <hamon/memory/make_obj_using_allocator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/array.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace make_obj_using_allocator_test
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

GTEST_TEST(MemoryTest, MakeObjUsingAllocatorTest)
{
	// non-pair overload

	// (const Alloc&, Args&&...)
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_obj_using_allocator<int>(MyAlloc{});
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, int>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t, 0);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_obj_using_allocator<FirstAlloc>(MyAlloc{});
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, FirstAlloc>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.n, 42);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_obj_using_allocator<LastAlloc>(MyAlloc{});
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, LastAlloc>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.n, 43);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_obj_using_allocator<NoAlloc>(MyAlloc{});
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, NoAlloc>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.n, 44);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_obj_using_allocator<int>(MyAlloc{}, 10);
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, int>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t, 10);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_obj_using_allocator<FirstAlloc>(MyAlloc{}, 11);
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, FirstAlloc>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.n, 11);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.ref_type, RefType::RValue);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_obj_using_allocator<LastAlloc>(MyAlloc{}, 12);
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, LastAlloc>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.n, 12);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.ref_type, RefType::RValue);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_obj_using_allocator<NoAlloc>(MyAlloc{}, 13);
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, NoAlloc>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.n, 13);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.ref_type, RefType::RValue);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_obj_using_allocator<FirstAlloc>(MyAlloc{}, 1, 2);
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, FirstAlloc>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.n, 3);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_obj_using_allocator<LastAlloc>(MyAlloc{}, 3, 4);
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, LastAlloc>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.n, 7);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_obj_using_allocator<NoAlloc>(MyAlloc{}, 5, 6);
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, NoAlloc>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.n, 11);
	}

	// pair overloads

	// (const Alloc&, piecewise_construct_t, Tuple1&&, Tuple2&&)
	{
		HAMON_CXX11_CONSTEXPR auto t =
			hamon::make_obj_using_allocator<hamon::pair<int, FirstAlloc>>(
				MyAlloc{},
				hamon::piecewise_construct_t{},
				hamon::make_tuple(1),
				hamon::make_tuple(2));
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, hamon::pair<int, FirstAlloc>>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.first,    1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.second.n, 2);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t =
			hamon::make_obj_using_allocator<hamon::pair<LastAlloc, NoAlloc>>(
				MyAlloc{},
				hamon::piecewise_construct_t{},
				hamon::make_tuple(),
				hamon::make_tuple(3, 4));
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, hamon::pair<LastAlloc, NoAlloc>>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.first.n,  43);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.second.n, 7);
	}

	// (const Alloc&)
	{
		HAMON_CXX11_CONSTEXPR auto t =
			hamon::make_obj_using_allocator<hamon::pair<FirstAlloc, LastAlloc>>(
				MyAlloc{});
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, hamon::pair<FirstAlloc, LastAlloc>>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.first.n,  42);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.second.n, 43);
	}

	// (const Alloc&, U&&, V&&)
	{
		HAMON_CXX11_CONSTEXPR auto t =
			hamon::make_obj_using_allocator<hamon::pair<NoAlloc, LastAlloc>>(
				MyAlloc{}, 5, 6);
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, hamon::pair<NoAlloc, LastAlloc>>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.first.n,  5);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.first.ref_type, RefType::RValue);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.second.n, 6);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.second.ref_type, RefType::RValue);
	}

	// (const Alloc&, pair<U, V>&)
	{
		hamon::pair<int, int> p{7, 8};
		auto t =
			hamon::make_obj_using_allocator<hamon::pair<FirstAlloc, NoAlloc>>(
				MyAlloc{}, p);
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, hamon::pair<FirstAlloc, NoAlloc>>::value, "");
		EXPECT_EQ(t.first.n,  7);
		EXPECT_EQ(t.first.ref_type, RefType::LValue);
		EXPECT_EQ(t.second.n, 8);
		EXPECT_EQ(t.second.ref_type, RefType::LValue);
	}

	// (const Alloc&, const pair<U, V>&)
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int> p{7, 8};
		HAMON_CXX11_CONSTEXPR auto t =
			hamon::make_obj_using_allocator<hamon::pair<LastAlloc, FirstAlloc>>(
				MyAlloc{}, p);
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, hamon::pair<LastAlloc, FirstAlloc>>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.first.n,  7);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.first.ref_type, RefType::ConstLValue);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.second.n, 8);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.second.ref_type, RefType::ConstLValue);
	}

	// (const Alloc&, pair<U, V>&&)
	{
		hamon::pair<int, int> p{7, 8};
		auto t =
			hamon::make_obj_using_allocator<hamon::pair<NoAlloc, FirstAlloc>>(
				MyAlloc{}, hamon::move(p));
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, hamon::pair<NoAlloc, FirstAlloc>>::value, "");
		EXPECT_EQ(t.first.n,  7);
		EXPECT_EQ(t.first.ref_type, RefType::RValue);
		EXPECT_EQ(t.second.n, 8);
		EXPECT_EQ(t.second.ref_type, RefType::RValue);
	}

	// (const Alloc&, const pair<U, V>&&)
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int> p{7, 8};
		HAMON_CXX11_CONSTEXPR auto t =
			hamon::make_obj_using_allocator<hamon::pair<FirstAlloc, LastAlloc>>(
				MyAlloc{}, hamon::move(p));
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, hamon::pair<FirstAlloc, LastAlloc>>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.first.n,  7);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.first.ref_type, RefType::ConstRValue);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.second.n, 8);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.second.ref_type, RefType::ConstRValue);
	}

	// (const Alloc&, PairLike&&)
	{
		hamon::array<int, 2> p{9, 10};
		auto t =
			hamon::make_obj_using_allocator<hamon::pair<FirstAlloc, LastAlloc>>(
				MyAlloc{}, p);
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, hamon::pair<FirstAlloc, LastAlloc>>::value, "");
		EXPECT_EQ(t.first.n,  9);
		EXPECT_EQ(t.first.ref_type, RefType::LValue);
		EXPECT_EQ(t.second.n, 10);
		EXPECT_EQ(t.second.ref_type, RefType::LValue);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<int, 2> p{11, 12};
		HAMON_CXX11_CONSTEXPR auto t =
			hamon::make_obj_using_allocator<hamon::pair<FirstAlloc, LastAlloc>>(
				MyAlloc{}, p);
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, hamon::pair<FirstAlloc, LastAlloc>>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.first.n,  11);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.first.ref_type, RefType::ConstLValue);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.second.n, 12);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.second.ref_type, RefType::ConstLValue);
	}
	{
		hamon::array<int, 2> p{13, 14};
		auto t =
			hamon::make_obj_using_allocator<hamon::pair<FirstAlloc, LastAlloc>>(
				MyAlloc{}, hamon::move(p));
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, hamon::pair<FirstAlloc, LastAlloc>>::value, "");
		EXPECT_EQ(t.first.n,  13);
		EXPECT_EQ(t.first.ref_type, RefType::RValue);
		EXPECT_EQ(t.second.n, 14);
		EXPECT_EQ(t.second.ref_type, RefType::RValue);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<int, 2> p{15, 16};
		HAMON_CXX11_CONSTEXPR auto t =
			hamon::make_obj_using_allocator<hamon::pair<FirstAlloc, LastAlloc>>(
				MyAlloc{}, hamon::move(p));
		static_assert(hamon::is_same<hamon::remove_cv_t<decltype(t)>, hamon::pair<FirstAlloc, LastAlloc>>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.first.n,  15);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.first.ref_type, RefType::ConstRValue);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.second.n, 16);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.second.ref_type, RefType::ConstRValue);
	}

	// (const Alloc&, U&&)
	{
		ConvertibleToPair ctp;
		auto t = hamon::make_obj_using_allocator<hamon::pair<int, int>>(MyAlloc{}, ctp);
		EXPECT_EQ(t.first,  1);
		EXPECT_EQ(t.second, 2);
	}
	{
		HAMON_CXX11_CONSTEXPR ConvertibleToPair ctp;
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_obj_using_allocator<hamon::pair<int, int>>(MyAlloc{}, ctp);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.first,  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.second, 2);
	}
	{
		ConvertibleToPair ctp;
		auto t = hamon::make_obj_using_allocator<hamon::pair<int, int>>(MyAlloc{}, hamon::move(ctp));
		EXPECT_EQ(t.first,  1);
		EXPECT_EQ(t.second, 2);
	}
	{
		HAMON_CXX11_CONSTEXPR ConvertibleToPair ctp;
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_obj_using_allocator<hamon::pair<int, int>>(MyAlloc{}, hamon::move(ctp));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.first,  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(t.second, 2);
	}
}

}	// namespace make_obj_using_allocator_test

}	// namespace hamon_memory_test
