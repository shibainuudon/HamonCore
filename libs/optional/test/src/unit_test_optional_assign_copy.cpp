/**
 *	@file	unit_test_optional_assign_copy.cpp
 *
 *	@brief	コピー代入演算子のテスト
 *
 *	constexpr optional<T>& operator=(const optional& rhs);
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace assign_copy_test
{

struct NonCopyable
{
	NonCopyable(NonCopyable const&) = delete;
	NonCopyable& operator=(NonCopyable const&) = delete;
};
static_assert(!hamon::is_copy_assignable<NonCopyable>::value, "");
static_assert(!hamon::is_copy_constructible<NonCopyable>::value, "");

struct NonCopyAssignable
{
	NonCopyAssignable(NonCopyAssignable const&);
	NonCopyAssignable& operator=(NonCopyAssignable const&) = delete;
};
static_assert(!hamon::is_copy_assignable<NonCopyAssignable>::value, "");
static_assert( hamon::is_copy_constructible<NonCopyAssignable>::value, "");

struct NonCopyConstructible
{
	NonCopyConstructible(NonCopyConstructible const&) = delete;
	NonCopyConstructible& operator=(NonCopyConstructible const&);
};
static_assert( hamon::is_copy_assignable<NonCopyConstructible>::value, "");
static_assert(!hamon::is_copy_constructible<NonCopyConstructible>::value, "");

struct Copyable
{
	Copyable(Copyable const&);
	Copyable& operator=(Copyable const&);
};
static_assert( hamon::is_copy_assignable<Copyable>::value, "");
static_assert( hamon::is_copy_constructible<Copyable>::value, "");

struct Trivial
{
};
static_assert( hamon::is_trivially_copy_constructible<Trivial>::value, "");
static_assert( hamon::is_trivially_copy_assignable<Trivial>::value, "");
static_assert( hamon::is_trivially_destructible<Trivial>::value, "");

struct NonTrivialCopyCtor
{
	NonTrivialCopyCtor(NonTrivialCopyCtor const&);
};
static_assert(!hamon::is_trivially_copy_constructible<NonTrivialCopyCtor>::value, "");
static_assert( hamon::is_trivially_copy_assignable<NonTrivialCopyCtor>::value, "");
static_assert( hamon::is_trivially_destructible<NonTrivialCopyCtor>::value, "");

struct NonTrivialCopyAssign
{
	NonTrivialCopyAssign& operator=(NonTrivialCopyAssign const&);
};
static_assert( hamon::is_trivially_copy_constructible<NonTrivialCopyAssign>::value, "");
static_assert(!hamon::is_trivially_copy_assignable<NonTrivialCopyAssign>::value, "");
static_assert( hamon::is_trivially_destructible<NonTrivialCopyAssign>::value, "");

struct NonTrivialDtor
{
	~NonTrivialDtor();
};
static_assert(!hamon::is_trivially_copy_constructible<NonTrivialDtor>::value, "");
static_assert( hamon::is_trivially_copy_assignable<NonTrivialDtor>::value, "");
static_assert(!hamon::is_trivially_destructible<NonTrivialDtor>::value, "");

struct Nothrow
{
	Nothrow(Nothrow const&) noexcept;
	Nothrow& operator=(Nothrow const&) noexcept;
};
static_assert( hamon::is_nothrow_copy_constructible<Nothrow>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<Nothrow>::value, "");

struct MayThrowCopyCtor
{
	MayThrowCopyCtor(MayThrowCopyCtor const&) noexcept(false);
	MayThrowCopyCtor& operator=(MayThrowCopyCtor const&) noexcept;
};
static_assert(!hamon::is_nothrow_copy_constructible<MayThrowCopyCtor>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<MayThrowCopyCtor>::value, "");

struct MayThrowCopyAssign
{
	MayThrowCopyAssign(MayThrowCopyAssign const&) noexcept;
	MayThrowCopyAssign& operator=(MayThrowCopyAssign const&) noexcept(false);
};
static_assert( hamon::is_nothrow_copy_constructible<MayThrowCopyAssign>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<MayThrowCopyAssign>::value, "");

struct MayThrow
{
	MayThrow(MayThrow const&) noexcept(false);
	MayThrow& operator=(MayThrow const&) noexcept(false);
};
static_assert(!hamon::is_nothrow_copy_constructible<MayThrow>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<MayThrow>::value, "");

// [optional.assign]/7
// This operator is defined as deleted unless
// is_copy_constructible_v<T> is true and is_copy_assignable_v<T> is true.
static_assert( hamon::is_copy_assignable<hamon::optional<int>>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::optional<NonCopyable>>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::optional<NonCopyAssignable>>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::optional<NonCopyConstructible>>::value, "");
static_assert( hamon::is_copy_assignable<hamon::optional<Copyable>>::value, "");

// [optional.assign]/7
// If is_trivially_copy_constructible_v<T> && is_trivially_copy_assignable_v<T> &&
// is_trivially_destructible_v<T> is true, this assignment operator is trivial.
static_assert( hamon::is_trivially_copy_assignable<hamon::optional<int>>::value, "");
static_assert( hamon::is_trivially_copy_assignable<hamon::optional<Trivial>>::value, "");
static_assert(!hamon::is_trivially_copy_assignable<hamon::optional<NonTrivialCopyCtor>>::value, "");
static_assert(!hamon::is_trivially_copy_assignable<hamon::optional<NonTrivialCopyAssign>>::value, "");
static_assert(!hamon::is_trivially_copy_assignable<hamon::optional<NonTrivialDtor>>::value, "");

// extension
#if !defined(HAMON_USE_STD_OPTIONAL)
static_assert( hamon::is_nothrow_copy_assignable<hamon::optional<int>>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<hamon::optional<Nothrow>>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::optional<MayThrowCopyCtor>>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::optional<MayThrowCopyAssign>>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::optional<MayThrow>>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	// *this contains a value, rhs contains a value
	{
		hamon::optional<int> o1 {42};
		hamon::optional<int> const o2 {13};
		VERIFY(o1.has_value());
		VERIFY(o2.has_value());
		auto& r = (o1 = o2);
		VERIFY(o1.has_value());
		VERIFY(o2.has_value());
		VERIFY(o1.value() == 13);
		VERIFY(*o1 == 13);
		static_assert(hamon::is_same<decltype(r), hamon::optional<int>&>::value, "");
		VERIFY(&r == &o1);
	}

	// *this contains a value, rhs does not contain a value
	{
		hamon::optional<int> o1 {42};
		hamon::optional<int> const o2;
		VERIFY(o1.has_value());
		VERIFY(!o2.has_value());
		auto& r = (o1 = o2);
		VERIFY(!o1.has_value());
		VERIFY(!o2.has_value());
		static_assert(hamon::is_same<decltype(r), hamon::optional<int>&>::value, "");
		VERIFY(&r == &o1);
	}

	// *this dos not contain a value, rhs contains a value
	{
		hamon::optional<int> o1;
		hamon::optional<int> const o2 {13};
		VERIFY(!o1.has_value());
		VERIFY(o2.has_value());
		auto& r = (o1 = o2);
		VERIFY(o1.has_value());
		VERIFY(o2.has_value());
		VERIFY(o1.value() == 13);
		VERIFY(*o1 == 13);
		static_assert(hamon::is_same<decltype(r), hamon::optional<int>&>::value, "");
		VERIFY(&r == &o1);
	}

	// *this dos not contain a value, rhs does not contain a value
	{
		hamon::optional<int> o1;
		hamon::optional<int> const o2;
		VERIFY(!o1.has_value());
		VERIFY(!o2.has_value());
		auto& r = (o1 = o2);
		VERIFY(!o1.has_value());
		VERIFY(!o2.has_value());
		static_assert(hamon::is_same<decltype(r), hamon::optional<int>&>::value, "");
		VERIFY(&r == &o1);
	}

	return true;
}

#undef VERIFY

static int s_copy_assign_count = 0;
static int s_copy_ctor_count = 0;
static int s_dtor_count = 0;

struct S
{
	S(int)
	{
	}

	S(S const&)
	{
		++s_copy_ctor_count;
	}

	S& operator=(S const&)
	{
		++s_copy_assign_count;
		return *this;
	}

	~S()
	{
		++s_dtor_count;
	}
};

void InvokeCountTest()
{
	s_copy_assign_count = 0;
	s_copy_ctor_count = 0;
	s_dtor_count = 0;

	// *this contains a value, rhs contains a value
	{
		hamon::optional<S> o1 {42};
		hamon::optional<S> const o2 {13};
		o1 = o2;
		EXPECT_EQ(1, s_copy_assign_count);
		EXPECT_EQ(0, s_copy_ctor_count);
		EXPECT_EQ(0, s_dtor_count);
	}

	s_copy_assign_count = 0;
	s_copy_ctor_count = 0;
	s_dtor_count = 0;

	// *this contains a value, rhs does not contain a value
	{
		hamon::optional<S> o1 {42};
		hamon::optional<S> const o2;
		o1 = o2;
		EXPECT_EQ(0, s_copy_assign_count);
		EXPECT_EQ(0, s_copy_ctor_count);
		EXPECT_EQ(1, s_dtor_count);
	}

	s_copy_assign_count = 0;
	s_copy_ctor_count = 0;
	s_dtor_count = 0;

	// *this dos not contain a value, rhs contains a value
	{
		hamon::optional<S> o1;
		hamon::optional<S> const o2 {13};
		o1 = o2;
		EXPECT_EQ(0, s_copy_assign_count);
		EXPECT_EQ(1, s_copy_ctor_count);
		EXPECT_EQ(0, s_dtor_count);
	}

	s_copy_assign_count = 0;
	s_copy_ctor_count = 0;
	s_dtor_count = 0;

	// *this dos not contain a value, rhs does not contain a value
	{
		hamon::optional<S> o1;
		hamon::optional<S> const o2;
		o1 = o2;
		EXPECT_EQ(0, s_copy_assign_count);
		EXPECT_EQ(0, s_copy_ctor_count);
		EXPECT_EQ(0, s_dtor_count);
	}
}

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnCopy1
{
	int value = -1;

	ThrowOnCopy1(int v) : value(v) {}

	ThrowOnCopy1(ThrowOnCopy1 const& rhs)
		: value(rhs.value)
	{
		throw 42;
	}

	ThrowOnCopy1& operator=(ThrowOnCopy1 const& rhs)
	{
		value = rhs.value;
		throw 42;
	}
};

struct ThrowOnCopy2
{
	int value = -1;

	ThrowOnCopy2(int v) : value(v) {}

	ThrowOnCopy2(ThrowOnCopy2 const&)
	{
		throw 42;
	}

	ThrowOnCopy2& operator=(ThrowOnCopy2 const&)
	{
		throw 42;
	}
};

void ThrowOnCopyTest()
{
	// *this contains a value, rhs contains a value
	{
		hamon::optional<ThrowOnCopy1> o1 {42};
		hamon::optional<ThrowOnCopy1> const o2 {13};
		EXPECT_ANY_THROW(o1 = o2);
		EXPECT_TRUE( o1.has_value());
		EXPECT_TRUE( o2.has_value());
		EXPECT_EQ(13, o1.value().value);
		EXPECT_EQ(13, o2.value().value);
		EXPECT_EQ(13, o1->value);
		EXPECT_EQ(13, o2->value);
	}
	{
		hamon::optional<ThrowOnCopy2> o1 {42};
		hamon::optional<ThrowOnCopy2> const o2 {13};
		EXPECT_ANY_THROW(o1 = o2);
		EXPECT_TRUE( o1.has_value());
		EXPECT_TRUE( o2.has_value());
		EXPECT_EQ(42, o1.value().value);
		EXPECT_EQ(13, o2.value().value);
		EXPECT_EQ(42, o1->value);
		EXPECT_EQ(13, o2->value);
	}

	// *this contains a value, rhs does not contain a value
	{
		hamon::optional<ThrowOnCopy1> o1 {42};
		hamon::optional<ThrowOnCopy1> const o2;
		EXPECT_NO_THROW(o1 = o2);
		EXPECT_TRUE(!o1.has_value());
		EXPECT_TRUE(!o2.has_value());
	}
	{
		hamon::optional<ThrowOnCopy2> o1 {42};
		hamon::optional<ThrowOnCopy2> const o2;
		EXPECT_NO_THROW(o1 = o2);
		EXPECT_TRUE(!o1.has_value());
		EXPECT_TRUE(!o2.has_value());
	}

	// *this dos not contain a value, rhs contains a value
	{
		hamon::optional<ThrowOnCopy1> o1;
		hamon::optional<ThrowOnCopy1> const o2 {13};
		EXPECT_ANY_THROW(o1 = o2);
		EXPECT_TRUE(!o1.has_value());
		EXPECT_TRUE( o2.has_value());
		EXPECT_EQ(13, o2.value().value);
		EXPECT_EQ(13, o2->value);
	}
	{
		hamon::optional<ThrowOnCopy2> o1;
		hamon::optional<ThrowOnCopy2> const o2 {13};
		EXPECT_ANY_THROW(o1 = o2);
		EXPECT_TRUE(!o1.has_value());
		EXPECT_TRUE( o2.has_value());
		EXPECT_EQ(13, o2.value().value);
		EXPECT_EQ(13, o2->value);
	}

	// *this dos not contain a value, rhs does not contain a value
	{
		hamon::optional<ThrowOnCopy1> o1;
		hamon::optional<ThrowOnCopy1> const o2;
		EXPECT_NO_THROW(o1 = o2);
		EXPECT_TRUE(!o1.has_value());
		EXPECT_TRUE(!o2.has_value());
	}
	{
		hamon::optional<ThrowOnCopy2> o1;
		hamon::optional<ThrowOnCopy2> const o2;
		EXPECT_NO_THROW(o1 = o2);
		EXPECT_TRUE(!o1.has_value());
		EXPECT_TRUE(!o2.has_value());
	}
}
#endif

GTEST_TEST(OptionalTest, AssignCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
	InvokeCountTest();
#if !defined(HAMON_NO_EXCEPTIONS)
	ThrowOnCopyTest();
#endif
}

}	// namespace assign_copy_test

}	// namespace hamon_optional_test
