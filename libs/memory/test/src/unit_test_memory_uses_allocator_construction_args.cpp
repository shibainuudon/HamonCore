/**
 *	@file	unit_test_memory_uses_allocator_construction_args.cpp
 *
 *	@brief	uses_allocator_construction_args のテスト
 */

#include <hamon/memory/uses_allocator_construction_args.hpp>
#include <hamon/memory/allocator_arg_t.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/array.hpp>
#include <hamon/pair.hpp>
#include <hamon/tuple.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>

namespace hamon_memory_test
{

namespace uses_allocator_construction_args_test
{

// 偽アロケータ
struct MyAlloc {};

// アロケータを使用しない偽コンテナ
struct MyContainer0
{
	MyContainer0(int) noexcept;
};

// 偽アロケータを使用する偽コンテナ（allocator_arg_t 使用）
struct MyContainer1
{
	using allocator_type = MyAlloc;
	MyContainer1(hamon::allocator_arg_t, MyAlloc const&, int) noexcept;
};

// 偽アロケータを使用する偽コンテナ（最後の引数）
struct MyContainer2
{
	using allocator_type = MyAlloc;
	MyContainer2(int, MyAlloc const&) noexcept;
};

struct MyContainer3
{
	using allocator_type = MyAlloc;
	MyContainer3(hamon::allocator_arg_t, MyAlloc const&) noexcept;
};

struct MyContainer4
{
	using allocator_type = MyAlloc;
	MyContainer4(MyAlloc const&) noexcept;
};

struct DefaultConstructible
{
	DefaultConstructible();
};

GTEST_TEST(MemoryTest, UsesAllocatorConstructionArgsTest)
{
	// non-pair overload

	// uses_allocator_construction_args(const Alloc&, Args&&...)
	{
		int i = 10;
		auto t = hamon::uses_allocator_construction_args<int>(MyAlloc{}, i);
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<int&>>::value, "");
		EXPECT_EQ(10, hamon::adl_get<0>(t));
	}
	{
		int i = 11;
		auto t = hamon::uses_allocator_construction_args<MyContainer0>(MyAlloc{}, hamon::move(i));
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<int&&>>::value, "");
		EXPECT_EQ(11, hamon::adl_get<0>(t));
	}
	{
		int const i = 12;
		auto t = hamon::uses_allocator_construction_args<MyContainer1>(MyAlloc{}, i);
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<hamon::allocator_arg_t, MyAlloc const&, int const&>>::value, "");
		EXPECT_EQ(12, hamon::adl_get<2>(t));
	}
	{
		int const i = 13;
		auto t = hamon::uses_allocator_construction_args<MyContainer2>(MyAlloc{}, hamon::move(i));
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<int const&&, MyAlloc const&>>::value, "");
		EXPECT_EQ(13, hamon::adl_get<0>(t));
	}
	{
		auto t = hamon::uses_allocator_construction_args<MyContainer3>(MyAlloc{});
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<hamon::allocator_arg_t, MyAlloc const&>>::value, "");
	}
	{
		auto t = hamon::uses_allocator_construction_args<MyContainer4>(MyAlloc{});
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<MyAlloc const&>>::value, "");
	}

	// pair overloads

	// uses_allocator_construction_args(const Alloc&, piecewise_construct_t, Tuple1&&, Tuple2&&)
	{
		int i = 41;
		auto t = hamon::uses_allocator_construction_args<
			hamon::pair<int, MyContainer3>>(
				MyAlloc{},
				hamon::piecewise_construct_t{},
				hamon::forward_as_tuple(i),
				hamon::forward_as_tuple());
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<
				hamon::piecewise_construct_t,
				hamon::tuple<int&>,
				hamon::tuple<hamon::allocator_arg_t, MyAlloc const&>>>::value, "");
		EXPECT_EQ(41, hamon::adl_get<0>(hamon::adl_get<1>(t)));
	}
	{
		int i = 42;
		auto t = hamon::uses_allocator_construction_args<
			hamon::pair<DefaultConstructible, MyContainer2>>(
				MyAlloc{},
				hamon::piecewise_construct_t{},
				hamon::forward_as_tuple(),
				hamon::forward_as_tuple(i));
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<
				hamon::piecewise_construct_t,
				hamon::tuple<>,
				hamon::tuple<int&, MyAlloc const&>>>::value, "");
		EXPECT_EQ(42, hamon::adl_get<0>(hamon::adl_get<2>(t)));
	}

	// uses_allocator_construction_args(const Alloc&)
	{
		auto t = hamon::uses_allocator_construction_args<
			hamon::pair<DefaultConstructible, MyContainer3>>(MyAlloc{});
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<
				hamon::piecewise_construct_t,
				hamon::tuple<>,
				hamon::tuple<hamon::allocator_arg_t, MyAlloc const&>>>::value, "");
	}
	{
		auto t = hamon::uses_allocator_construction_args<
			hamon::pair<MyContainer4, DefaultConstructible>>(MyAlloc{});
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<
				hamon::piecewise_construct_t,
				hamon::tuple<MyAlloc const&>,
				hamon::tuple<>>>::value, "");
	}

	// uses_allocator_construction_args(const Alloc&, U&&, V&&)
	{
		int i = 14;
		int j = 15;
		auto t = hamon::uses_allocator_construction_args<
			hamon::pair<int, MyContainer1>>(MyAlloc{}, i, hamon::move(j));
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<
				hamon::piecewise_construct_t,
				hamon::tuple<int&>,
				hamon::tuple<hamon::allocator_arg_t, MyAlloc const&, int&&>>>::value, "");
		EXPECT_EQ(14, hamon::adl_get<0>(hamon::adl_get<1>(t)));
		EXPECT_EQ(15, hamon::adl_get<2>(hamon::adl_get<2>(t)));
	}
	{
		int const i = 16;
		int const j = 17;
		auto t = hamon::uses_allocator_construction_args<
			hamon::pair<MyContainer1, MyContainer2>>(MyAlloc{}, hamon::move(i), j);
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<
				hamon::piecewise_construct_t,
				hamon::tuple<hamon::allocator_arg_t, MyAlloc const&, int const&&>,
				hamon::tuple<int const&, MyAlloc const&>>>::value, "");
		EXPECT_EQ(16, hamon::adl_get<2>(hamon::adl_get<1>(t)));
		EXPECT_EQ(17, hamon::adl_get<0>(hamon::adl_get<2>(t)));
	}

	// uses_allocator_construction_args(const Alloc&, pair<U, V>&)
	{
		hamon::pair<int, int> p{18, 19};
		auto t = hamon::uses_allocator_construction_args<
			hamon::pair<int, MyContainer1>>(MyAlloc{}, p);
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<
				hamon::piecewise_construct_t,
				hamon::tuple<int&>,
				hamon::tuple<hamon::allocator_arg_t, MyAlloc const&, int&>>>::value, "");
		EXPECT_EQ(18, hamon::adl_get<0>(hamon::adl_get<1>(t)));
		EXPECT_EQ(19, hamon::adl_get<2>(hamon::adl_get<2>(t)));
	}
	{
		hamon::pair<int, int> p{20, 21};
		auto t = hamon::uses_allocator_construction_args<
			hamon::pair<MyContainer1, MyContainer2>>(MyAlloc{}, p);
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<
				hamon::piecewise_construct_t,
				hamon::tuple<hamon::allocator_arg_t, MyAlloc const&, int&>,
				hamon::tuple<int&, MyAlloc const&>>>::value, "");
		EXPECT_EQ(20, hamon::adl_get<2>(hamon::adl_get<1>(t)));
		EXPECT_EQ(21, hamon::adl_get<0>(hamon::adl_get<2>(t)));
	}

	// uses_allocator_construction_args(const Alloc&, const pair<U, V>&)
	{
		hamon::pair<int, int> const p{22, 23};
		auto t = hamon::uses_allocator_construction_args<
			hamon::pair<int, MyContainer1>>(MyAlloc{}, p);
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<
				hamon::piecewise_construct_t,
				hamon::tuple<int const&>,
				hamon::tuple<hamon::allocator_arg_t, MyAlloc const&, int const&>>>::value, "");
		EXPECT_EQ(22, hamon::adl_get<0>(hamon::adl_get<1>(t)));
		EXPECT_EQ(23, hamon::adl_get<2>(hamon::adl_get<2>(t)));
	}
	{
		hamon::pair<int, int> const p{24, 25};
		auto t = hamon::uses_allocator_construction_args<
			hamon::pair<MyContainer1, MyContainer2>>(MyAlloc{}, p);
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<
				hamon::piecewise_construct_t,
				hamon::tuple<hamon::allocator_arg_t, MyAlloc const&, int const&>,
				hamon::tuple<int const&, MyAlloc const&>>>::value, "");
		EXPECT_EQ(24, hamon::adl_get<2>(hamon::adl_get<1>(t)));
		EXPECT_EQ(25, hamon::adl_get<0>(hamon::adl_get<2>(t)));
	}

	// uses_allocator_construction_args(const Alloc&, pair<U, V>&&)
	{
		hamon::pair<int, int> p{26, 27};
		auto t = hamon::uses_allocator_construction_args<
			hamon::pair<int, MyContainer1>>(MyAlloc{}, hamon::move(p));
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<
				hamon::piecewise_construct_t,
				hamon::tuple<int&&>,
				hamon::tuple<hamon::allocator_arg_t, MyAlloc const&, int&&>>>::value, "");
		EXPECT_EQ(26, hamon::adl_get<0>(hamon::adl_get<1>(t)));
		EXPECT_EQ(27, hamon::adl_get<2>(hamon::adl_get<2>(t)));
	}
	{
		hamon::pair<int, int> p{28, 29};
		auto t = hamon::uses_allocator_construction_args<
			hamon::pair<MyContainer1, MyContainer2>>(MyAlloc{}, hamon::move(p));
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<
				hamon::piecewise_construct_t,
				hamon::tuple<hamon::allocator_arg_t, MyAlloc const&, int&&>,
				hamon::tuple<int&&, MyAlloc const&>>>::value, "");
		EXPECT_EQ(28, hamon::adl_get<2>(hamon::adl_get<1>(t)));
		EXPECT_EQ(29, hamon::adl_get<0>(hamon::adl_get<2>(t)));
	}

	// uses_allocator_construction_args(const Alloc&, const pair<U, V>&&)
	{
		hamon::pair<int, int> const p{30, 31};
		auto t = hamon::uses_allocator_construction_args<
			hamon::pair<int, MyContainer1>>(MyAlloc{}, hamon::move(p));
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<
				hamon::piecewise_construct_t,
				hamon::tuple<int const&&>,
				hamon::tuple<hamon::allocator_arg_t, MyAlloc const&, int const&&>>>::value, "");
		EXPECT_EQ(30, hamon::adl_get<0>(hamon::adl_get<1>(t)));
		EXPECT_EQ(31, hamon::adl_get<2>(hamon::adl_get<2>(t)));
	}
	{
		hamon::pair<int, int> const p{32, 33};
		auto t = hamon::uses_allocator_construction_args<
			hamon::pair<MyContainer1, MyContainer2>>(MyAlloc{}, hamon::move(p));
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<
				hamon::piecewise_construct_t,
				hamon::tuple<hamon::allocator_arg_t, MyAlloc const&, int const&&>,
				hamon::tuple<int const&&, MyAlloc const&>>>::value, "");
		EXPECT_EQ(32, hamon::adl_get<2>(hamon::adl_get<1>(t)));
		EXPECT_EQ(33, hamon::adl_get<0>(hamon::adl_get<2>(t)));
	}

#if 0	// TODO
	// uses_allocator_construction_args(const Alloc&, PairLike&&)
	{
		hamon::tuple<int, int> p{14, 15};
		auto t = hamon::uses_allocator_construction_args<
			hamon::pair<int, MyContainer1>>(MyAlloc{}, p);
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<
				hamon::piecewise_construct_t,
				hamon::tuple<int&>,
				hamon::tuple<hamon::allocator_arg_t, MyAlloc const&, int&>>>::value, "");
		EXPECT_EQ(14, hamon::adl_get<0>(hamon::adl_get<1>(t)));
		EXPECT_EQ(15, hamon::adl_get<2>(hamon::adl_get<2>(t)));
	}
	{
		hamon::array<int, 2> const p{16, 17};
		auto t = hamon::uses_allocator_construction_args<
			hamon::pair<MyContainer1, MyContainer2>>(MyAlloc{}, p);
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<
				hamon::piecewise_construct_t,
				hamon::tuple<hamon::allocator_arg_t, MyAlloc const&, int const&>,
				hamon::tuple<int const&, MyAlloc const&>>>::value, "");
		EXPECT_EQ(16, hamon::adl_get<2>(hamon::adl_get<1>(t)));
		EXPECT_EQ(17, hamon::adl_get<0>(hamon::adl_get<2>(t)));
	}
	{
		hamon::array<int, 2> p{18, 19};
		auto t = hamon::uses_allocator_construction_args<
			hamon::pair<int, MyContainer1>>(MyAlloc{}, hamon::move(p));
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<
				hamon::piecewise_construct_t,
				hamon::tuple<int&&>,
				hamon::tuple<hamon::allocator_arg_t, MyAlloc const&, int&&>>>::value, "");
		EXPECT_EQ(18, hamon::adl_get<0>(hamon::adl_get<1>(t)));
		EXPECT_EQ(19, hamon::adl_get<2>(hamon::adl_get<2>(t)));
	}
	{
		hamon::tuple<int, int> const p{20, 21};
		auto t = hamon::uses_allocator_construction_args<
			hamon::pair<MyContainer1, MyContainer2>>(MyAlloc{}, hamon::move(p));
		static_assert(hamon::is_same<decltype(t),
			hamon::tuple<
				hamon::piecewise_construct_t,
				hamon::tuple<hamon::allocator_arg_t, MyAlloc const&, int const&&>,
				hamon::tuple<int const&&, MyAlloc const&>>>::value, "");
		EXPECT_EQ(20, hamon::adl_get<2>(hamon::adl_get<1>(t)));
		EXPECT_EQ(21, hamon::adl_get<0>(hamon::adl_get<2>(t)));
	}
#endif

	// TODO
	// uses_allocator_construction_args(const Alloc&, U&&)
}

}	// namespace uses_allocator_construction_args_test

}	// namespace hamon_memory_test
