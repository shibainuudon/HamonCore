/**
 *	@file	unit_test_expected_emplace.cpp
 *
 *	@brief	emplace のテスト
 *
 *	template<class... Args>
 *	constexpr T& emplace(Args&&... args) noexcept;
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace emplace_test
{

template <typename Void, typename T, typename... Args>
struct CanEmplaceImpl
	: hamon::false_type {};

template <typename T, typename... Args>
struct CanEmplaceImpl<
	hamon::void_t<decltype(hamon::declval<T&>().emplace(hamon::declval<Args>()...))>, T, Args...>
	: hamon::true_type {};

template <typename T, typename... Args>
using CanEmplace = CanEmplaceImpl<void, T, Args...>;

static_assert( CanEmplace<hamon::expected<int, int>, int>::value, "");
static_assert(!CanEmplace<hamon::expected<int, int>, int, int>::value, "");

template <bool Noexcept1, bool Noexcept2>
struct CtorFromInt
{
	CtorFromInt(int) noexcept(Noexcept1);
	CtorFromInt(int, int) noexcept(Noexcept2);
};

static_assert( CanEmplace<hamon::expected<CtorFromInt<true, true>, int>, int>::value, "");
static_assert( CanEmplace<hamon::expected<CtorFromInt<true, true>, int>, int, int>::value, "");
static_assert( CanEmplace<hamon::expected<CtorFromInt<true, false>, int>, int>::value, "");
static_assert(!CanEmplace<hamon::expected<CtorFromInt<true, false>, int>, int, int>::value, "");
static_assert(!CanEmplace<hamon::expected<CtorFromInt<false, true>, int>, int>::value, "");
static_assert( CanEmplace<hamon::expected<CtorFromInt<false, true>, int>, int, int>::value, "");
static_assert(!CanEmplace<hamon::expected<CtorFromInt<false, false>, int>, int>::value, "");
static_assert(!CanEmplace<hamon::expected<CtorFromInt<false, false>, int>, int, int>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E, typename U>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(noexcept(hamon::declval<hamon::expected<T, E>&>().emplace(hamon::declval<U>())), "");

	{
		hamon::expected<T, E> e(hamon::in_place);
		auto& r = e.emplace(U{10});
		static_assert(hamon::is_same<decltype(r), T&>::value, "");
		VERIFY(&r == &(*e));

		VERIFY(e.has_value());
		VERIFY(e.value() == T{10});
	}
	{
		hamon::expected<T, E> e(hamon::unexpect);
		auto& r = e.emplace(U{20});
		static_assert(hamon::is_same<decltype(r), T&>::value, "");
		VERIFY(&r == &(*e));

		VERIFY(e.has_value());
		VERIFY(e.value() == T{20});
	}
	return true;
}

struct S1
{
	int value;

	HAMON_CXX14_CONSTEXPR S1() : value(0) {}
	HAMON_CXX14_CONSTEXPR S1(int v) noexcept : value(v) {}
	HAMON_CXX14_CONSTEXPR bool operator==(S1 const& rhs) const { return value == rhs.value; }
};

struct S2
{
	int value;

	HAMON_CXX14_CONSTEXPR S2() : value(0) {}
	HAMON_CXX14_CONSTEXPR S2(int v) noexcept : value(v) {}
	HAMON_CXX14_CONSTEXPR S2(S2 const&) = delete;
	HAMON_CXX14_CONSTEXPR S2(S2&&) = delete;
	HAMON_CXX14_CONSTEXPR S2& operator=(S2 const& rhs) = delete;
	HAMON_CXX14_CONSTEXPR S2& operator=(S2&& rhs) = delete;
	HAMON_CXX14_CONSTEXPR bool operator==(S2 const& rhs) const { return value == rhs.value; }
};

struct Trased
{
	static int default_ctor_count;
	static int ctor1_count;
	static int ctor2_count;
	static int copy_ctor_count;
	static int move_ctor_count;
	static int copy_assign_count;
	static int move_assign_count;
	static int dtor_count;

	Trased()
	{
		++default_ctor_count;
	}

	Trased(int) noexcept
	{
		++ctor1_count;
	}

	Trased(int, int) noexcept
	{
		++ctor2_count;
	}

	Trased(Trased const&)
	{
		++copy_ctor_count;
	}

	Trased(Trased&&) noexcept
	{
		++move_ctor_count;
	}

	Trased& operator=(Trased const&)
	{
		++copy_assign_count;
		return *this;
	}

	Trased& operator=(Trased&&)
	{
		++move_assign_count;
		return *this;
	}

	~Trased()
	{
		++dtor_count;
	}

	static void reset()
	{
		default_ctor_count = 0;
		ctor1_count = 0;
		ctor2_count = 0;
		copy_ctor_count = 0;
		move_ctor_count = 0;
		copy_assign_count = 0;
		move_assign_count = 0;
		dtor_count = 0;
	}
};
int Trased::default_ctor_count = 0;
int Trased::ctor1_count = 0;
int Trased::ctor2_count = 0;
int Trased::copy_ctor_count = 0;
int Trased::move_ctor_count = 0;
int Trased::copy_assign_count = 0;
int Trased::move_assign_count = 0;
int Trased::dtor_count = 0;

void trase_test()
{
	Trased::reset();
	{
		hamon::expected<Trased, int> e{hamon::in_place};
		e.emplace(10);
		EXPECT_EQ(1, Trased::default_ctor_count);
		EXPECT_EQ(1, Trased::ctor1_count);
		EXPECT_EQ(0, Trased::ctor2_count);
		EXPECT_EQ(0, Trased::copy_ctor_count);
		EXPECT_EQ(0, Trased::move_ctor_count);
		EXPECT_EQ(0, Trased::copy_assign_count);
		EXPECT_EQ(0, Trased::move_assign_count);
		EXPECT_EQ(1, Trased::dtor_count);
	}
	EXPECT_EQ(1, Trased::default_ctor_count);
	EXPECT_EQ(1, Trased::ctor1_count);
	EXPECT_EQ(0, Trased::ctor2_count);
	EXPECT_EQ(0, Trased::copy_ctor_count);
	EXPECT_EQ(0, Trased::move_ctor_count);
	EXPECT_EQ(0, Trased::copy_assign_count);
	EXPECT_EQ(0, Trased::move_assign_count);
	EXPECT_EQ(2, Trased::dtor_count);

	Trased::reset();
	{
		hamon::expected<Trased, int> e{hamon::in_place};
		e.emplace(10, 11);
		EXPECT_EQ(1, Trased::default_ctor_count);
		EXPECT_EQ(0, Trased::ctor1_count);
		EXPECT_EQ(1, Trased::ctor2_count);
		EXPECT_EQ(0, Trased::copy_ctor_count);
		EXPECT_EQ(0, Trased::move_ctor_count);
		EXPECT_EQ(0, Trased::copy_assign_count);
		EXPECT_EQ(0, Trased::move_assign_count);
		EXPECT_EQ(1, Trased::dtor_count);
	}
	EXPECT_EQ(1, Trased::default_ctor_count);
	EXPECT_EQ(0, Trased::ctor1_count);
	EXPECT_EQ(1, Trased::ctor2_count);
	EXPECT_EQ(0, Trased::copy_ctor_count);
	EXPECT_EQ(0, Trased::move_ctor_count);
	EXPECT_EQ(0, Trased::copy_assign_count);
	EXPECT_EQ(0, Trased::move_assign_count);
	EXPECT_EQ(2, Trased::dtor_count);

	Trased::reset();
	{
		hamon::expected<Trased, int> e{hamon::unexpect};
		e.emplace(10);
		EXPECT_EQ(0, Trased::default_ctor_count);
		EXPECT_EQ(1, Trased::ctor1_count);
		EXPECT_EQ(0, Trased::ctor2_count);
		EXPECT_EQ(0, Trased::copy_ctor_count);
		EXPECT_EQ(0, Trased::move_ctor_count);
		EXPECT_EQ(0, Trased::copy_assign_count);
		EXPECT_EQ(0, Trased::move_assign_count);
		EXPECT_EQ(0, Trased::dtor_count);
	}
	EXPECT_EQ(0, Trased::default_ctor_count);
	EXPECT_EQ(1, Trased::ctor1_count);
	EXPECT_EQ(0, Trased::ctor2_count);
	EXPECT_EQ(0, Trased::copy_ctor_count);
	EXPECT_EQ(0, Trased::move_ctor_count);
	EXPECT_EQ(0, Trased::copy_assign_count);
	EXPECT_EQ(0, Trased::move_assign_count);
	EXPECT_EQ(1, Trased::dtor_count);

	Trased::reset();
	{
		hamon::expected<Trased, int> e{hamon::unexpect};
		e.emplace(10, 20);
		EXPECT_EQ(0, Trased::default_ctor_count);
		EXPECT_EQ(0, Trased::ctor1_count);
		EXPECT_EQ(1, Trased::ctor2_count);
		EXPECT_EQ(0, Trased::copy_ctor_count);
		EXPECT_EQ(0, Trased::move_ctor_count);
		EXPECT_EQ(0, Trased::copy_assign_count);
		EXPECT_EQ(0, Trased::move_assign_count);
		EXPECT_EQ(0, Trased::dtor_count);
	}
	EXPECT_EQ(0, Trased::default_ctor_count);
	EXPECT_EQ(0, Trased::ctor1_count);
	EXPECT_EQ(1, Trased::ctor2_count);
	EXPECT_EQ(0, Trased::copy_ctor_count);
	EXPECT_EQ(0, Trased::move_ctor_count);
	EXPECT_EQ(0, Trased::copy_assign_count);
	EXPECT_EQ(0, Trased::move_assign_count);
	EXPECT_EQ(1, Trased::dtor_count);

	Trased::reset();
	{
		hamon::expected<int, Trased> e{hamon::in_place};
		e.emplace(10);
		EXPECT_EQ(0, Trased::default_ctor_count);
		EXPECT_EQ(0, Trased::ctor1_count);
		EXPECT_EQ(0, Trased::ctor2_count);
		EXPECT_EQ(0, Trased::copy_ctor_count);
		EXPECT_EQ(0, Trased::move_ctor_count);
		EXPECT_EQ(0, Trased::copy_assign_count);
		EXPECT_EQ(0, Trased::move_assign_count);
		EXPECT_EQ(0, Trased::dtor_count);
	}
	EXPECT_EQ(0, Trased::default_ctor_count);
	EXPECT_EQ(0, Trased::ctor1_count);
	EXPECT_EQ(0, Trased::ctor2_count);
	EXPECT_EQ(0, Trased::copy_ctor_count);
	EXPECT_EQ(0, Trased::move_ctor_count);
	EXPECT_EQ(0, Trased::copy_assign_count);
	EXPECT_EQ(0, Trased::move_assign_count);
	EXPECT_EQ(0, Trased::dtor_count);

	Trased::reset();
	{
		hamon::expected<int, Trased> e{hamon::unexpect};
		e.emplace(10);
		EXPECT_EQ(1, Trased::default_ctor_count);
		EXPECT_EQ(0, Trased::ctor1_count);
		EXPECT_EQ(0, Trased::ctor2_count);
		EXPECT_EQ(0, Trased::copy_ctor_count);
		EXPECT_EQ(0, Trased::move_ctor_count);
		EXPECT_EQ(0, Trased::copy_assign_count);
		EXPECT_EQ(0, Trased::move_assign_count);
		EXPECT_EQ(1, Trased::dtor_count);
	}
	EXPECT_EQ(1, Trased::default_ctor_count);
	EXPECT_EQ(0, Trased::ctor1_count);
	EXPECT_EQ(0, Trased::ctor2_count);
	EXPECT_EQ(0, Trased::copy_ctor_count);
	EXPECT_EQ(0, Trased::move_ctor_count);
	EXPECT_EQ(0, Trased::copy_assign_count);
	EXPECT_EQ(0, Trased::move_assign_count);
	EXPECT_EQ(1, Trased::dtor_count);
}

#undef VERIFY

GTEST_TEST(ExpectedTest, EmplaceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<S1, float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, S1, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<S2, float, int>()));

	trase_test();
}

}	// namespace emplace_test

}	// namespace hamon_expected_test
