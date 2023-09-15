/**
 *	@file	unit_test_optional_swap.cpp
 *
 *	@brief	swap関数のテスト
 *
 *	constexpr void swap(optional& rhs) noexcept(see below);
 *
 *	template<class T>
 *	constexpr void swap(optional<T>& x, optional<T>& y) noexcept(noexcept(x.swap(y)));
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace swap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test1()
{
	// *this contains a value, rhs contains a value
	{
		hamon::optional<int> o1 {42};
		hamon::optional<int> o2 {13};
		VERIFY(o1.has_value());
		VERIFY(o2.has_value());

		o1.swap(o2);
		VERIFY(o1.has_value());
		VERIFY(o2.has_value());
		VERIFY(o1.value() == 13);
		VERIFY(o2.value() == 42);

		swap(o1, o2);
		VERIFY(o1.has_value());
		VERIFY(o2.has_value());
		VERIFY(o1.value() == 42);
		VERIFY(o2.value() == 13);
	}

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test2()
{
	// *this contains a value, rhs does not contain a value
	{
		hamon::optional<int> o1 {42};
		hamon::optional<int> o2;
		VERIFY( o1.has_value());
		VERIFY(!o2.has_value());

		o1.swap(o2);
		VERIFY(!o1.has_value());
		VERIFY( o2.has_value());
		VERIFY(o2.value() == 42);

		swap(o1, o2);
		VERIFY( o1.has_value());
		VERIFY(!o2.has_value());
		VERIFY(o1.value() == 42);
	}

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test3()
{
	// *this dos not contain a value, rhs contains a value
	{
		hamon::optional<int> o1;
		hamon::optional<int> o2 {13};
		VERIFY(!o1.has_value());
		VERIFY( o2.has_value());

		o1.swap(o2);
		VERIFY( o1.has_value());
		VERIFY(!o2.has_value());
		VERIFY(o1.value() == 13);

		swap(o1, o2);
		VERIFY(!o1.has_value());
		VERIFY( o2.has_value());
		VERIFY(o2.value() == 13);
	}

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test4()
{
	// *this dos not contain a value, rhs does not contain a value
	{
		hamon::optional<int> o1;
		hamon::optional<int> o2;
		VERIFY(!o1.has_value());
		VERIFY(!o2.has_value());

		o1.swap(o2);
		VERIFY(!o1.has_value());
		VERIFY(!o2.has_value());

		swap(o1, o2);
		VERIFY(!o1.has_value());
		VERIFY(!o2.has_value());
	}

	return true;
}

#undef VERIFY

static int s_copy_assign_count = 0;
static int s_copy_ctor_count = 0;
static int s_move_assign_count = 0;
static int s_move_ctor_count = 0;
static int s_dtor_count = 0;
static int s_swap_count = 0;

struct S
{
	S() {}

	S(S const&)
	{
		++s_copy_ctor_count;
	}

	S(S &&)
	{
		++s_move_ctor_count;
	}
	
	S& operator=(S const&)
	{
		++s_copy_assign_count;
		return *this;
	}

	S& operator=(S &&)
	{
		++s_move_assign_count;
		return *this;
	}

	~S()
	{
		++s_dtor_count;
	}
};

void swap(S&, S&)
{
	++s_swap_count;
}

void InvokeCountTest()
{
	s_copy_assign_count = 0;
	s_copy_ctor_count = 0;
	s_move_assign_count = 0;
	s_move_ctor_count = 0;
	s_dtor_count = 0;
	s_swap_count = 0;

	// *this contains a value, rhs contains a value
	{
		hamon::optional<S> o1 {hamon::in_place};
		hamon::optional<S> o2 {hamon::in_place};
		o1.swap(o2);
		EXPECT_EQ(0, s_copy_assign_count);
		EXPECT_EQ(0, s_copy_ctor_count);
		EXPECT_EQ(0, s_move_assign_count);
		EXPECT_EQ(0, s_move_ctor_count);
		EXPECT_EQ(0, s_dtor_count);
		EXPECT_EQ(1, s_swap_count);
	}

	s_copy_assign_count = 0;
	s_copy_ctor_count = 0;
	s_move_assign_count = 0;
	s_move_ctor_count = 0;
	s_dtor_count = 0;
	s_swap_count = 0;

	// *this contains a value, rhs does not contain a value
	{
		hamon::optional<S> o1 {hamon::in_place};
		hamon::optional<S> o2;
		o1.swap(o2);
		EXPECT_EQ(0, s_copy_assign_count);
		EXPECT_EQ(0, s_copy_ctor_count);
		EXPECT_EQ(0, s_move_assign_count);
		EXPECT_EQ(1, s_move_ctor_count);
		EXPECT_EQ(1, s_dtor_count);
		EXPECT_EQ(0, s_swap_count);
	}

	s_copy_assign_count = 0;
	s_copy_ctor_count = 0;
	s_move_assign_count = 0;
	s_move_ctor_count = 0;
	s_dtor_count = 0;
	s_swap_count = 0;

	// *this dos not contain a value, rhs contains a value
	{
		hamon::optional<S> o1;
		hamon::optional<S> o2 {hamon::in_place};
		o1.swap(o2);
		EXPECT_EQ(0, s_copy_assign_count);
		EXPECT_EQ(0, s_copy_ctor_count);
		EXPECT_EQ(0, s_move_assign_count);
		EXPECT_EQ(1, s_move_ctor_count);
		EXPECT_EQ(1, s_dtor_count);
		EXPECT_EQ(0, s_swap_count);
	}

	s_copy_assign_count = 0;
	s_copy_ctor_count = 0;
	s_move_assign_count = 0;
	s_move_ctor_count = 0;
	s_dtor_count = 0;
	s_swap_count = 0;

	// *this dos not contain a value, rhs does not contain a value
	{
		hamon::optional<S> o1;
		hamon::optional<S> o2;
		o1.swap(o2);
		EXPECT_EQ(0, s_copy_assign_count);
		EXPECT_EQ(0, s_copy_ctor_count);
		EXPECT_EQ(0, s_move_assign_count);
		EXPECT_EQ(0, s_move_ctor_count);
		EXPECT_EQ(0, s_dtor_count);
		EXPECT_EQ(0, s_swap_count);
	}
}

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnSwap
{
};

void swap(ThrowOnSwap&, ThrowOnSwap&)
{
	throw 42;
}

void ThrowOnSwapTest()
{
	// *this contains a value, rhs contains a value
	{
		hamon::optional<ThrowOnSwap> o1 {hamon::in_place};
		hamon::optional<ThrowOnSwap> o2 {hamon::in_place};
		EXPECT_ANY_THROW(o1.swap(o2));
	}

	// *this contains a value, rhs does not contain a value
	{
		hamon::optional<ThrowOnSwap> o1 {hamon::in_place};
		hamon::optional<ThrowOnSwap> o2;
		EXPECT_NO_THROW(o1.swap(o2));
	}

	// *this dos not contain a value, rhs contains a value
	{
		hamon::optional<ThrowOnSwap> o1;
		hamon::optional<ThrowOnSwap> o2 {hamon::in_place};
		EXPECT_NO_THROW(o1.swap(o2));
	}

	// *this dos not contain a value, rhs does not contain a value
	{
		hamon::optional<ThrowOnSwap> o1;
		hamon::optional<ThrowOnSwap> o2;
		EXPECT_NO_THROW(o1.swap(o2));
	}
}

struct ThrowOnMove
{
	ThrowOnMove() = default;

	ThrowOnMove(ThrowOnMove&&)
	{
		throw 42;
	}
};

void swap(ThrowOnMove&, ThrowOnMove&)
{
}

void ThrowOnMoveTest()
{
	// *this contains a value, rhs contains a value
	{
		hamon::optional<ThrowOnMove> o1 {hamon::in_place};
		hamon::optional<ThrowOnMove> o2 {hamon::in_place};
		EXPECT_NO_THROW(o1.swap(o2));
	}

	// *this contains a value, rhs does not contain a value
	{
		hamon::optional<ThrowOnMove> o1 {hamon::in_place};
		hamon::optional<ThrowOnMove> o2;
		EXPECT_ANY_THROW(o1.swap(o2));
	}

	// *this dos not contain a value, rhs contains a value
	{
		hamon::optional<ThrowOnMove> o1;
		hamon::optional<ThrowOnMove> o2 {hamon::in_place};
		EXPECT_ANY_THROW(o1.swap(o2));
	}

	// *this dos not contain a value, rhs does not contain a value
	{
		hamon::optional<ThrowOnMove> o1;
		hamon::optional<ThrowOnMove> o2;
		EXPECT_NO_THROW(o1.swap(o2));
	}
}
#endif

GTEST_TEST(OptionalTest, SwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test3()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test4()));

	InvokeCountTest();
#if !defined(HAMON_NO_EXCEPTIONS)
	ThrowOnSwapTest();
	ThrowOnMoveTest();
#endif
}

}	// namespace swap_test

}	// namespace hamon_optional_test
