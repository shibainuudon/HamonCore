/**
 *	@file	unit_test_bad_expected_access_what.cpp
 *
 *	@brief	what() のテスト
 *
 *	constexpr const char* what() const noexcept override;
 */

#include <hamon/expected/bad_expected_access.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bad_expected_access_test
{

namespace what_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename E>
/*HAMON_CXX14_CONSTEXPR*/ bool test()
{
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::bad_expected_access<E> &      >().what()), const char*>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::bad_expected_access<E> const& >().what()), const char*>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::bad_expected_access<E> &&     >().what()), const char*>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::bad_expected_access<E> const&&>().what()), const char*>::value, "");

	static_assert(noexcept(hamon::declval<hamon::bad_expected_access<E> &      >().what()), "");
	static_assert(noexcept(hamon::declval<hamon::bad_expected_access<E> const& >().what()), "");
	static_assert(noexcept(hamon::declval<hamon::bad_expected_access<E> &&     >().what()), "");
	static_assert(noexcept(hamon::declval<hamon::bad_expected_access<E> const&&>().what()), "");

	{
		hamon::bad_expected_access<E> unex{E{5}};
		VERIFY(unex.what() != nullptr);
	}
	{
		hamon::bad_expected_access<E> const unex{E{6}};
		VERIFY(unex.what() != nullptr);
	}
	{
		hamon::bad_expected_access<E> unex{E{7}};
		VERIFY(hamon::move(unex).what() != nullptr);
	}
	{
		hamon::bad_expected_access<E> const unex{E{8}};
		VERIFY(hamon::move(unex).what() != nullptr);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(BadExpectedAccessTest, WhatTest)
{
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE((test<int>()));
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE((test<char>()));
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE((test<float>()));
}

}	// namespace what_test

}	// namespace hamon_bad_expected_access_test
