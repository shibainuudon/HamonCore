/**
 *	@file	unit_test_bad_expected_access_error.cpp
 *
 *	@brief	error() のテスト
 *
 *	constexpr E& error() & noexcept;
 *	constexpr const E& error() const & noexcept;
 *	constexpr E&& error() && noexcept;
 *	constexpr const E&& error() const && noexcept;
 */

#include <hamon/expected/bad_expected_access.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bad_expected_access_test
{

namespace error_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename E>
/*HAMON_CXX14_CONSTEXPR*/ bool test()
{
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::bad_expected_access<E> &      >().error()), E&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::bad_expected_access<E> const& >().error()), E const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::bad_expected_access<E> &&     >().error()), E&&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::bad_expected_access<E> const&&>().error()), E const&&>::value, "");

	static_assert(noexcept(hamon::declval<hamon::bad_expected_access<E> &>().error()), "");
	static_assert(noexcept(hamon::declval<hamon::bad_expected_access<E> const&>().error()), "");
	static_assert(noexcept(hamon::declval<hamon::bad_expected_access<E> &&>().error()), "");
	static_assert(noexcept(hamon::declval<hamon::bad_expected_access<E> const&&>().error()), "");

	{
		hamon::bad_expected_access<E> unex{E{5}};
		VERIFY(unex.error() == E{5});
	}
	{
		hamon::bad_expected_access<E> const unex{E{6}};
		VERIFY(unex.error() == E{6});
	}
	{
		hamon::bad_expected_access<E> unex{E{7}};
		VERIFY(hamon::move(unex).error() == E{7});
	}
	{
		hamon::bad_expected_access<E> const unex{E{8}};
		VERIFY(hamon::move(unex).error() == E{8});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(BadExpectedAccessTest, ErrorTest)
{
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE((test<int>()));
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE((test<char>()));
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE((test<float>()));
}

}	// namespace error_test

}	// namespace hamon_bad_expected_access_test
