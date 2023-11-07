/**
 *	@file	unit_test_tuple_get_type.cpp
 *
 *	@brief	get<T> のテスト
 *
 *	template<class T, class... Types>
 *	constexpr T& get(tuple<Types...>& t) noexcept;
 *
 *	template<class T, class... Types>
 *	constexpr T&& get(tuple<Types...>&& t) noexcept;
 *
 *	template<class T, class... Types>
 *	constexpr const T& get(const tuple<Types...>& t) noexcept;
 *
 *	template<class T, class... Types>
 *	constexpr const T&& get(const tuple<Types...>&& t) noexcept;
 */

#include <hamon/tuple.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace get_type_test
{

GTEST_TEST(TupleTest, GetTypeTest)
{
	using hamon::get;
	{
		hamon::tuple<int> t(3);
		int& i = get<int>(t);
		EXPECT_TRUE(i == 3);
		int&& j = get<int>(hamon::move(t));
		EXPECT_TRUE(j == 3);
	}
	{
		hamon::tuple<char, float const, int> t('a', 2.5f, 4);
		{
			auto&& r0 = get<char>(t);
			auto&& r1 = get<float const>(t);
			auto&& r2 = get<int>(t);
			static_assert(hamon::is_same<decltype(r0), char&>::value, "");
			static_assert(hamon::is_same<decltype(r1), float const&>::value, "");
			static_assert(hamon::is_same<decltype(r2), int&>::value, "");
			EXPECT_TRUE(r0 == 'a');
			EXPECT_TRUE(r1 == 2.5f);
			EXPECT_TRUE(r2 == 4);
		}
		{
			auto&& r0 = get<char>(hamon::move(t));
			auto&& r1 = get<float const>(hamon::move(t));
			auto&& r2 = get<int>(hamon::move(t));
			static_assert(hamon::is_same<decltype(r0), char&&>::value, "");
			static_assert(hamon::is_same<decltype(r1), float const&&>::value, "");
			static_assert(hamon::is_same<decltype(r2), int&&>::value, "");
			EXPECT_TRUE(r0 == 'a');
			EXPECT_TRUE(r1 == 2.5f);
			EXPECT_TRUE(r2 == 4);
		}
	}
	{
		hamon::tuple<char, float const, int> const t('a', 2.5f, 4);
		{
			auto&& r0 = get<char>(t);
			auto&& r1 = get<float const>(t);
			auto&& r2 = get<int>(t);
			static_assert(hamon::is_same<decltype(r0), char const&>::value, "");
			static_assert(hamon::is_same<decltype(r1), float const&>::value, "");
			static_assert(hamon::is_same<decltype(r2), int const&>::value, "");
			EXPECT_TRUE(r0 == 'a');
			EXPECT_TRUE(r1 == 2.5f);
			EXPECT_TRUE(r2 == 4);
		}
		{
			auto&& r0 = get<char>(hamon::move(t));
			auto&& r1 = get<float const>(hamon::move(t));
			auto&& r2 = get<int>(hamon::move(t));
			static_assert(hamon::is_same<decltype(r0), char const&&>::value, "");
			static_assert(hamon::is_same<decltype(r1), float const&&>::value, "");
			static_assert(hamon::is_same<decltype(r2), int const&&>::value, "");
			EXPECT_TRUE(r0 == 'a');
			EXPECT_TRUE(r1 == 2.5f);
			EXPECT_TRUE(r2 == 4);
		}
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<float, int> const t(1.5f, 2);

		HAMON_CXX11_CONSTEXPR auto f1 = get<float>(t);
		HAMON_CXX11_CONSTEXPR auto i1 = get<int>(t);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(f1 == 1.5f);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(i1 == 2);

		HAMON_CXX11_CONSTEXPR auto f2 = get<float>(hamon::move(t));
		HAMON_CXX11_CONSTEXPR auto i2 = get<int>(hamon::move(t));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(f2 == 1.5f);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(i2 == 2);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<char, float, int> const t('a', 2.5f, 4);

		HAMON_CXX11_CONSTEXPR auto c1 = get<char>(t);
		HAMON_CXX11_CONSTEXPR auto f1 = get<float>(t);
		HAMON_CXX11_CONSTEXPR auto i1 = get<int>(t);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(c1 == 'a');
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(f1 == 2.5f);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(i1 == 4);

		HAMON_CXX11_CONSTEXPR auto c2 = get<char>(hamon::move(t));
		HAMON_CXX11_CONSTEXPR auto f2 = get<float>(hamon::move(t));
		HAMON_CXX11_CONSTEXPR auto i2 = get<int>(hamon::move(t));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(c2 == 'a');
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(f2 == 2.5f);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(i2 == 4);
	}
}

}	// namespace get_type_test

}	// namespace hamon_tuple_test
