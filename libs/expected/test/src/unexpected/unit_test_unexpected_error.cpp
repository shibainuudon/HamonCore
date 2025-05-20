/**
 *	@file	unit_test_unexpected_error.cpp
 *
 *	@brief	error() のテスト
 *
 *	constexpr const E& error() const & noexcept;
 *	constexpr E& error() & noexcept;
 *	constexpr const E&& error() const && noexcept;
 *	constexpr E&& error() && noexcept;
 */

#include <hamon/expected/unexpected.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unexpected_test
{

namespace error_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::unexpected<E> &      >().error()), E&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::unexpected<E> const& >().error()), E const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::unexpected<E> &&     >().error()), E&&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::unexpected<E> const&&>().error()), E const&&>::value, "");

	static_assert(noexcept(hamon::declval<hamon::unexpected<E> &>().error()), "");
	static_assert(noexcept(hamon::declval<hamon::unexpected<E> const&>().error()), "");
	static_assert(noexcept(hamon::declval<hamon::unexpected<E> &&>().error()), "");
	static_assert(noexcept(hamon::declval<hamon::unexpected<E> const&&>().error()), "");

	{
		hamon::unexpected<E> unex{E{5}};
		VERIFY(unex.error() == E{5});
	}
	{
		hamon::unexpected<E> const unex{E{6}};
		VERIFY(unex.error() == E{6});
	}
	{
		hamon::unexpected<E> unex{E{7}};
		VERIFY(hamon::move(unex).error() == E{7});
	}
	{
		hamon::unexpected<E> const unex{E{8}};
		VERIFY(hamon::move(unex).error() == E{8});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnexpectedTest, ErrorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace error_test

}	// namespace hamon_unexpected_test
