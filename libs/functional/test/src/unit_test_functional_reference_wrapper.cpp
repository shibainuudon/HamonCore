/**
 *	@file	unit_test_functional_reference_wrapper.cpp
 *
 *	@brief	reference_wrapper のテスト
 */

#include <hamon/functional/reference_wrapper.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_trivially_copyable.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "constexpr_test.hpp"

namespace hamon_functional_test
{

namespace reference_wrapper_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct NonTrivial
{
	~NonTrivial() { }
};

using R = hamon::reference_wrapper<NonTrivial>;

static_assert(std::is_copy_constructible<R>::value, "copy constructible");
static_assert(std::is_copy_assignable<R>::value, "copy assignable");
static_assert(hamon::is_trivially_copyable<R>::value, "trivially copyable");

GTEST_TEST(ReferenceWrapperTest, DeductionTest)
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		int i = 0;
		hamon::reference_wrapper rw0(i);
		static_assert(hamon::is_same<decltype(rw0), hamon::reference_wrapper<int>>::value, "");

		hamon::reference_wrapper rw1(rw0);
		static_assert(hamon::is_same<decltype(rw1), hamon::reference_wrapper<int>>::value, "");
	}
	{
		int const i = 0;
		hamon::reference_wrapper rw0(i);
		static_assert(hamon::is_same<decltype(rw0), hamon::reference_wrapper<int const>>::value, "");

		hamon::reference_wrapper rw1(rw0);
		static_assert(hamon::is_same<decltype(rw1), hamon::reference_wrapper<int const>>::value, "");
	}
#endif
}

inline HAMON_CXX14_CONSTEXPR bool test_get()
{
	int i = 0;
	hamon::reference_wrapper<int> rw(i);
	VERIFY(rw.get() == 0);
	rw.get() = 23;
	int& j = rw;
	VERIFY(j == 23);

	return true;
}

GTEST_TEST(ReferenceWrapperTest, GetTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_get());
}

struct Foo
{
	HAMON_CONSTEXPR int operator()() const
	{
		return 1;
	}

	HAMON_CONSTEXPR int operator()(int) const
	{
		return 2;
	}

	HAMON_CONSTEXPR int operator()(float) const
	{
		return 3;
	}

	HAMON_CONSTEXPR int operator()(int, int) const
	{
		return 4;
	}
};

inline HAMON_CXX14_CONSTEXPR bool test_invoke()
{
	Foo f{};
	hamon::reference_wrapper<Foo> rw(f);
	VERIFY(rw() == 1);
	VERIFY(rw(0) == 2);
	VERIFY(rw(0.5f) == 3);
	VERIFY(rw(1, 1) == 4);
	return true;
}

GTEST_TEST(ReferenceWrapperTest, InvokeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_invoke());
}

#undef VERIFY

}	// namespace reference_wrapper_test

}	// namespace hamon_functional_test
