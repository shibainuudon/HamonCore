/**
 *	@file	unit_test_expected_op_assign_val.cpp
 *
 *	@brief	正常値からの代入演算子のテスト
 *
 *	template<class U = remove_cv_t<T>>
 *	constexpr expected& operator=(U&& v);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace op_assign_val_test
{

// Test constraints
static_assert(hamon::is_assignable<hamon::expected<int, int>&, int>::value, "");

// is_same_v<expected, remove_cvref_t<U>>
// it is true because it covered by the copy assignment
static_assert(hamon::is_assignable<hamon::expected<int, int>&, hamon::expected<int, int>>::value, "");

// remove_cvref_t<U> is a specialization of unexpected
// it is true because it covered the unexpected overload
static_assert(hamon::is_assignable<hamon::expected<int, int>&, hamon::unexpected<int>>::value, "");

// !is_constructible_v<T, U>
struct NoCtorFromInt
{
	NoCtorFromInt(int) = delete;
	NoCtorFromInt& operator=(int);
};
static_assert(!hamon::is_assignable<hamon::expected<NoCtorFromInt, int>&, int>::value, "");

// !is_assignable_v<T&, U>
struct NoAssignFromInt
{
	explicit NoAssignFromInt(int);
	NoAssignFromInt& operator=(int) = delete;
};
static_assert(!hamon::is_assignable<hamon::expected<NoAssignFromInt, int>&, int>::value, "");

template <bool moveNoexcept, bool convertNoexcept>
struct MaybeNoexcept
{
	explicit MaybeNoexcept(int) noexcept(convertNoexcept);
	MaybeNoexcept(MaybeNoexcept&&) noexcept(moveNoexcept);
	MaybeNoexcept& operator=(MaybeNoexcept&&) = default;
	MaybeNoexcept& operator=(int);
};

// !is_nothrow_constructible_v<T, U> && !is_nothrow_move_constructible_v<T> &&
// is_nothrow_move_constructible_v<E>
static_assert(hamon::is_assignable<hamon::expected<MaybeNoexcept<false, false>, int>&, int>::value, "");

// is_nothrow_constructible_v<T, U> && !is_nothrow_move_constructible_v<T> &&
// !is_nothrow_move_constructible_v<E>
static_assert(hamon::is_assignable<hamon::expected<MaybeNoexcept<false, true>, MaybeNoexcept<false, false>>&, int>::value, "");

// !is_nothrow_constructible_v<T, U> && is_nothrow_move_constructible_v<T> &&
// !is_nothrow_move_constructible_v<E>
static_assert(hamon::is_assignable<hamon::expected<MaybeNoexcept<true, false>, MaybeNoexcept<false, false>>&, int>::value, "");

// !is_nothrow_constructible_v<T, U> && !is_nothrow_move_constructible_v<T> &&
// !is_nothrow_move_constructible_v<E>
static_assert(!hamon::is_assignable<hamon::expected<MaybeNoexcept<false, false>, MaybeNoexcept<false, false>>&, int>::value, "");

// test noexcept

#if !defined(HAMON_USE_STD_EXPECTED)
template <bool CtorNoexcept, bool AssignNoexcept>
struct MaybeNoexcept2
{
	MaybeNoexcept2(int) noexcept(CtorNoexcept);
	MaybeNoexcept2& operator=(int) noexcept(AssignNoexcept);
};

static_assert( hamon::is_nothrow_assignable<hamon::expected<int, int>&, int>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::expected<MaybeNoexcept2<true, true>, int>&, int>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::expected<MaybeNoexcept2<true, false>, int>&, int>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::expected<MaybeNoexcept2<false, true>, int>&, int>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::expected<MaybeNoexcept2<false, false>, int>&, int>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::expected<int, MaybeNoexcept2<true, true>>&, int>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::expected<int, MaybeNoexcept2<true, false>>&, int>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::expected<int, MaybeNoexcept2<false, true>>&, int>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::expected<int, MaybeNoexcept2<false, false>>&, int>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E, typename U>
HAMON_CXX14_CONSTEXPR bool test()
{
	{
		U const src{11};
		hamon::expected<T, E> dst{hamon::in_place, T{12}};
		auto& r = (dst = src);
		static_assert(hamon::is_same<decltype(r), hamon::expected<T, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(dst.has_value());
		VERIFY(dst.value() == T{11});
	}
	{
		U const src{13};
		hamon::expected<T, E> dst{hamon::unexpect, E{14}};
		auto& r = (dst = src);
		static_assert(hamon::is_same<decltype(r), hamon::expected<T, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(dst.has_value());
		VERIFY(dst.value() == T{13});
	}
	{
		hamon::expected<T, E> dst{hamon::in_place, T{15}};
		auto& r = (dst = U{16});
		static_assert(hamon::is_same<decltype(r), hamon::expected<T, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(dst.has_value());
		VERIFY(dst.value() == T{16});
	}
	{
		hamon::expected<T, E> dst{hamon::unexpect, E{17}};
		auto& r = (dst = U{18});
		static_assert(hamon::is_same<decltype(r), hamon::expected<T, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(dst.has_value());
		VERIFY(dst.value() == T{18});
	}
	return true;
}

struct S1
{
	int value;

	HAMON_CXX14_CONSTEXPR S1(int v) : value(v) {}
	HAMON_CXX14_CONSTEXPR S1(S1 const& rhs) : value(rhs.value) {}
	HAMON_CXX14_CONSTEXPR S1(S1&& rhs) : value(rhs.value) {}
	HAMON_CXX14_CONSTEXPR S1& operator=(S1 const& rhs) { value = rhs.value; return *this; }
	HAMON_CXX14_CONSTEXPR S1& operator=(S1&& rhs) { value = rhs.value; return *this; }
	HAMON_CXX14_CONSTEXPR bool operator==(S1 const& rhs) const { return value == rhs.value; }
};

struct S2
{
	int value;

	HAMON_CXX14_CONSTEXPR S2(int v) : value(v) {}
	HAMON_CXX14_CONSTEXPR S2(S2 const& rhs) : value(rhs.value) {}
	HAMON_CXX14_CONSTEXPR S2(S2&& rhs) noexcept : value(rhs.value) {}
	HAMON_CXX14_CONSTEXPR S2& operator=(S2 const& rhs) { value = rhs.value; return *this; }
	HAMON_CXX14_CONSTEXPR S2& operator=(S2&& rhs) { value = rhs.value; return *this; }
	HAMON_CXX14_CONSTEXPR bool operator==(S2 const& rhs) const { return value == rhs.value; }
};

struct S3
{
	static int default_ctor_count;
	static int copy_ctor_count;
	static int move_ctor_count;
	static int copy_assign_count;
	static int move_assign_count;
	static int dtor_count;

	S3()
	{
		++default_ctor_count;
	}

	S3(S3 const&)
	{
		++copy_ctor_count;
	}

	S3(S3&&)
	{
		++move_ctor_count;
	}

	S3& operator=(S3 const&)
	{
		++copy_assign_count;
		return *this;
	}

	S3& operator=(S3&&)
	{
		++move_assign_count;
		return *this;
	}

	~S3()
	{
		++dtor_count;
	}

	static void reset()
	{
		default_ctor_count = 0;
		copy_ctor_count = 0;
		move_ctor_count = 0;
		copy_assign_count = 0;
		move_assign_count = 0;
		dtor_count = 0;
	}
};
int S3::default_ctor_count = 0;
int S3::copy_ctor_count = 0;
int S3::move_ctor_count = 0;
int S3::copy_assign_count = 0;
int S3::move_assign_count = 0;
int S3::dtor_count = 0;

void trase_test_1()
{
	S3::reset();
	{
		S3 const src{};
		hamon::expected<S3, int> dst{hamon::in_place};
		dst = src;
		EXPECT_EQ(2, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(0, S3::move_ctor_count);
		EXPECT_EQ(1, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(0, S3::dtor_count);
	}
	EXPECT_EQ(2, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(0, S3::move_ctor_count);
	EXPECT_EQ(1, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(2, S3::dtor_count);

	S3::reset();
	{
		S3 const src{};
		hamon::expected<S3, int> dst{hamon::unexpect};
		dst = src;
		EXPECT_EQ(1, S3::default_ctor_count);
		EXPECT_EQ(1, S3::copy_ctor_count);
		EXPECT_EQ(0, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(0, S3::dtor_count);
	}
	EXPECT_EQ(1, S3::default_ctor_count);
	EXPECT_EQ(1, S3::copy_ctor_count);
	EXPECT_EQ(0, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(2, S3::dtor_count);

	S3::reset();
	{
		S3 src{};
		hamon::expected<S3, int> dst{hamon::in_place};
		dst = hamon::move(src);
		EXPECT_EQ(2, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(0, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(1, S3::move_assign_count);
		EXPECT_EQ(0, S3::dtor_count);
	}
	EXPECT_EQ(2, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(0, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(1, S3::move_assign_count);
	EXPECT_EQ(2, S3::dtor_count);

	S3::reset();
	{
		S3 src{};
		hamon::expected<S3, int> dst{hamon::unexpect};
		dst = hamon::move(src);
		EXPECT_EQ(1, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(1, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(0, S3::dtor_count);
	}
	EXPECT_EQ(1, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(1, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(2, S3::dtor_count);
}

struct S4
{
	static int default_ctor_count;
	static int copy_ctor_count;
	static int move_ctor_count;
	static int copy_assign_count;
	static int move_assign_count;
	static int dtor_count;

	S4()
	{
		++default_ctor_count;
	}

	S4(S4 const&)
	{
		++copy_ctor_count;
	}

	S4(S4&&) noexcept
	{
		++move_ctor_count;
	}

	S4& operator=(S4 const&)
	{
		++copy_assign_count;
		return *this;
	}

	S4& operator=(S4&&)
	{
		++move_assign_count;
		return *this;
	}

	~S4()
	{
		++dtor_count;
	}

	static void reset()
	{
		default_ctor_count = 0;
		copy_ctor_count = 0;
		move_ctor_count = 0;
		copy_assign_count = 0;
		move_assign_count = 0;
		dtor_count = 0;
	}
};
int S4::default_ctor_count = 0;
int S4::copy_ctor_count = 0;
int S4::move_ctor_count = 0;
int S4::copy_assign_count = 0;
int S4::move_assign_count = 0;
int S4::dtor_count = 0;

void trase_test_2()
{
	S4::reset();
	{
		S4 const src{};
		hamon::expected<S4, int> dst{hamon::in_place};
		dst = src;
		EXPECT_EQ(2, S4::default_ctor_count);
		EXPECT_EQ(0, S4::copy_ctor_count);
		EXPECT_EQ(0, S4::move_ctor_count);
		EXPECT_EQ(1, S4::copy_assign_count);
		EXPECT_EQ(0, S4::move_assign_count);
		EXPECT_EQ(0, S4::dtor_count);
	}
	EXPECT_EQ(2, S4::default_ctor_count);
	EXPECT_EQ(0, S4::copy_ctor_count);
	EXPECT_EQ(0, S4::move_ctor_count);
	EXPECT_EQ(1, S4::copy_assign_count);
	EXPECT_EQ(0, S4::move_assign_count);
	EXPECT_EQ(2, S4::dtor_count);

	S4::reset();
	{
		S4 const src{};
		hamon::expected<S4, int> dst{hamon::unexpect};
		dst = src;
		EXPECT_EQ(1, S4::default_ctor_count);
		EXPECT_EQ(1, S4::copy_ctor_count);
		EXPECT_EQ(1, S4::move_ctor_count);
		EXPECT_EQ(0, S4::copy_assign_count);
		EXPECT_EQ(0, S4::move_assign_count);
		EXPECT_EQ(1, S4::dtor_count);
	}
	EXPECT_EQ(1, S4::default_ctor_count);
	EXPECT_EQ(1, S4::copy_ctor_count);
	EXPECT_EQ(1, S4::move_ctor_count);
	EXPECT_EQ(0, S4::copy_assign_count);
	EXPECT_EQ(0, S4::move_assign_count);
	EXPECT_EQ(3, S4::dtor_count);

	S4::reset();
	{
		S4 src{};
		hamon::expected<S4, int> dst{hamon::in_place};
		dst = hamon::move(src);
		EXPECT_EQ(2, S4::default_ctor_count);
		EXPECT_EQ(0, S4::copy_ctor_count);
		EXPECT_EQ(0, S4::move_ctor_count);
		EXPECT_EQ(0, S4::copy_assign_count);
		EXPECT_EQ(1, S4::move_assign_count);
		EXPECT_EQ(0, S4::dtor_count);
	}
	EXPECT_EQ(2, S4::default_ctor_count);
	EXPECT_EQ(0, S4::copy_ctor_count);
	EXPECT_EQ(0, S4::move_ctor_count);
	EXPECT_EQ(0, S4::copy_assign_count);
	EXPECT_EQ(1, S4::move_assign_count);
	EXPECT_EQ(2, S4::dtor_count);

	S4::reset();
	{
		S4 src{};
		hamon::expected<S4, int> dst{hamon::unexpect};
		dst = hamon::move(src);
		EXPECT_EQ(1, S4::default_ctor_count);
		EXPECT_EQ(0, S4::copy_ctor_count);
		EXPECT_EQ(1, S4::move_ctor_count);
		EXPECT_EQ(0, S4::copy_assign_count);
		EXPECT_EQ(0, S4::move_assign_count);
		EXPECT_EQ(0, S4::dtor_count);
	}
	EXPECT_EQ(1, S4::default_ctor_count);
	EXPECT_EQ(0, S4::copy_ctor_count);
	EXPECT_EQ(1, S4::move_ctor_count);
	EXPECT_EQ(0, S4::copy_assign_count);
	EXPECT_EQ(0, S4::move_assign_count);
	EXPECT_EQ(2, S4::dtor_count);
}

void deduce_test()
{
	// Test default template argument.
	// Without it, the template parameter cannot be deduced from an initializer list
	{
		struct Bar
		{
			int i;
			int j;
			constexpr Bar(int ii, int jj) : i(ii), j(jj) {}
		};

		hamon::expected<Bar, int> e({5, 6});
		e = {7, 8};
		EXPECT_TRUE(e.value().i == 7);
		EXPECT_TRUE(e.value().j == 8);
	}
}

#undef VERIFY

void exceptions_test()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	struct ThrowOnCtor
	{
		struct Exception{};
		ThrowOnCtor(int) { throw Exception{}; }
	};

	{
		hamon::expected<ThrowOnCtor, int> dst{hamon::unexpect, 5};
		EXPECT_THROW(dst = 10, ThrowOnCtor::Exception);
		EXPECT_TRUE(!dst.has_value());
		EXPECT_TRUE(dst.error() == 5);
	}
#endif
}

GTEST_TEST(ExpectedTest, OpAssignValTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<S1, int, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, S1, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<S2, int, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, S2, int>()));

	trase_test_1();
	trase_test_2();

	deduce_test();

	exceptions_test();
}

}	// namespace op_assign_val_test

}	// namespace hamon_expected_test
