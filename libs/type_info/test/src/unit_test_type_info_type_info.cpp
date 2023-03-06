/**
 *	@file	unit_test_type_info_type_info.cpp
 *
 *	@brief	type_info のテスト
 */

#include <hamon/type_info.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "constexpr_test.hpp"

namespace hamon_type_info_test
{

static_assert(!hamon::is_default_constructible<hamon::type_info>::value, "");
static_assert( hamon::is_copy_constructible<hamon::type_info>::value, "");
static_assert( hamon::is_move_constructible<hamon::type_info>::value, "");
static_assert( hamon::is_copy_assignable<hamon::type_info>::value, "");
static_assert( hamon::is_move_assignable<hamon::type_info>::value, "");

struct S1
{};

class S2
{};

template <typename T>
class TS
{};

enum E1
{};

enum class E2
{};

GTEST_TEST(TypeInfoTest, NameTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<S1>().name(),       "hamon_type_info_test::S1");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<S2>().name(),       "hamon_type_info_test::S2");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<TS<int>>().name(),  "hamon_type_info_test::TS<int>");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<TS<bool>>().name(), "hamon_type_info_test::TS<bool>");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<E1>().name(),       "hamon_type_info_test::E1");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<E2>().name(),       "hamon_type_info_test::E2");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<int>().name(),      "int");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<float>().name(),    "float");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<char>().name(),     "char");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<bool>().name(),     "bool");
}

GTEST_TEST(TypeInfoTest, HashTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<S1>().hash(),       sizeof(std::size_t) == 4 ? 1956626883U :  6699969198750557557U);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<S2>().hash(),       sizeof(std::size_t) == 4 ? 1956626892U :  6699969198750557556U);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<TS<int>>().hash(),  sizeof(std::size_t) == 4 ?  868323736U : 10761259580242164917U);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<TS<bool>>().hash(), sizeof(std::size_t) == 4 ? 2537226284U : 13014479217681382996U);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<E1>().hash(),       sizeof(std::size_t) == 4 ? 1956628053U :  6699969198750516603U);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<E2>().hash(),       sizeof(std::size_t) == 4 ? 1956628050U :  6699969198750516602U);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<int>().hash(),      sizeof(std::size_t) == 4 ? 4216848189U :  4962777938083703864U);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<float>().hash(),    sizeof(std::size_t) == 4 ? 1366422933U : 16012993614398985859U);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<char>().hash(),     sizeof(std::size_t) == 4 ? 1256964356U : 15210376380126533734U);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::type_id<bool>().hash(),     sizeof(std::size_t) == 4 ? 1256663585U : 15210376311425452431U);
}

GTEST_TEST(TypeInfoTest, CompareOperatorTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S1>() == hamon::type_id<S1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S1>() != hamon::type_id<S2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S1>() != hamon::type_id<TS<int>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S1>() != hamon::type_id<TS<bool>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S1>() != hamon::type_id<E1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S1>() != hamon::type_id<E2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S1>() != hamon::type_id<int>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S1>() != hamon::type_id<float>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S1>() != hamon::type_id<bool>());

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S2>() != hamon::type_id<S1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S2>() == hamon::type_id<S2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S2>() != hamon::type_id<TS<int>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S2>() != hamon::type_id<TS<bool>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S2>() != hamon::type_id<E1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S2>() != hamon::type_id<E2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S2>() != hamon::type_id<int>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S2>() != hamon::type_id<float>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S2>() != hamon::type_id<bool>());

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<int>>() != hamon::type_id<S1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<int>>() != hamon::type_id<S2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<int>>() == hamon::type_id<TS<int>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<int>>() != hamon::type_id<TS<bool>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<int>>() != hamon::type_id<E1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<int>>() != hamon::type_id<E2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<int>>() != hamon::type_id<int>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<int>>() != hamon::type_id<float>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<int>>() != hamon::type_id<bool>());

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<bool>>() != hamon::type_id<S1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<bool>>() != hamon::type_id<S2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<bool>>() != hamon::type_id<TS<int>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<bool>>() == hamon::type_id<TS<bool>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<bool>>() != hamon::type_id<E1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<bool>>() != hamon::type_id<E2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<bool>>() != hamon::type_id<int>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<bool>>() != hamon::type_id<float>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<bool>>() != hamon::type_id<bool>());

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E1>() != hamon::type_id<S1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E1>() != hamon::type_id<S2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E1>() != hamon::type_id<TS<int>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E1>() != hamon::type_id<TS<bool>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E1>() == hamon::type_id<E1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E1>() != hamon::type_id<E2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E1>() != hamon::type_id<int>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E1>() != hamon::type_id<float>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E1>() != hamon::type_id<bool>());

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E2>() != hamon::type_id<S1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E2>() != hamon::type_id<S2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E2>() != hamon::type_id<TS<int>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E2>() != hamon::type_id<TS<bool>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E2>() != hamon::type_id<E1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E2>() == hamon::type_id<E2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E2>() != hamon::type_id<int>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E2>() != hamon::type_id<float>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E2>() != hamon::type_id<bool>());

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<int>() != hamon::type_id<S1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<int>() != hamon::type_id<S2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<int>() != hamon::type_id<TS<int>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<int>() != hamon::type_id<TS<bool>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<int>() != hamon::type_id<E1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<int>() != hamon::type_id<E2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<int>() == hamon::type_id<int>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<int>() != hamon::type_id<float>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<int>() != hamon::type_id<bool>());

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<float>() != hamon::type_id<S1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<float>() != hamon::type_id<S2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<float>() != hamon::type_id<TS<int>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<float>() != hamon::type_id<TS<bool>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<float>() != hamon::type_id<E1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<float>() != hamon::type_id<E2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<float>() != hamon::type_id<int>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<float>() == hamon::type_id<float>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<float>() != hamon::type_id<bool>());

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<bool>() != hamon::type_id<S1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<bool>() != hamon::type_id<S2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<bool>() != hamon::type_id<TS<int>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<bool>() != hamon::type_id<TS<bool>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<bool>() != hamon::type_id<E1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<bool>() != hamon::type_id<E2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<bool>() != hamon::type_id<int>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<bool>() != hamon::type_id<float>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<bool>() == hamon::type_id<bool>());

	//
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S1>() == hamon::type_id(S1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S1>() != hamon::type_id(S2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S1>() != hamon::type_id(TS<int>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S1>() != hamon::type_id(TS<bool>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S1>() != hamon::type_id(E1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S1>() != hamon::type_id(E2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S1>() != hamon::type_id(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S1>() != hamon::type_id(1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S1>() != hamon::type_id(false));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S2>() != hamon::type_id(S1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S2>() == hamon::type_id(S2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S2>() != hamon::type_id(TS<int>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S2>() != hamon::type_id(TS<bool>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S2>() != hamon::type_id(E1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S2>() != hamon::type_id(E2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S2>() != hamon::type_id(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S2>() != hamon::type_id(1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<S2>() != hamon::type_id(false));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<int>>() != hamon::type_id(S1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<int>>() != hamon::type_id(S2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<int>>() == hamon::type_id(TS<int>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<int>>() != hamon::type_id(TS<bool>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<int>>() != hamon::type_id(E1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<int>>() != hamon::type_id(E2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<int>>() != hamon::type_id(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<int>>() != hamon::type_id(1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<int>>() != hamon::type_id(false));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<bool>>() != hamon::type_id(S1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<bool>>() != hamon::type_id(S2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<bool>>() != hamon::type_id(TS<int>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<bool>>() == hamon::type_id(TS<bool>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<bool>>() != hamon::type_id(E1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<bool>>() != hamon::type_id(E2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<bool>>() != hamon::type_id(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<bool>>() != hamon::type_id(1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<TS<bool>>() != hamon::type_id(false));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E1>() != hamon::type_id(S1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E1>() != hamon::type_id(S2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E1>() != hamon::type_id(TS<int>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E1>() != hamon::type_id(TS<bool>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E1>() == hamon::type_id(E1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E1>() != hamon::type_id(E2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E1>() != hamon::type_id(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E1>() != hamon::type_id(1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E1>() != hamon::type_id(false));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E2>() != hamon::type_id(S1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E2>() != hamon::type_id(S2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E2>() != hamon::type_id(TS<int>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E2>() != hamon::type_id(TS<bool>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E2>() != hamon::type_id(E1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E2>() == hamon::type_id(E2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E2>() != hamon::type_id(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E2>() != hamon::type_id(1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<E2>() != hamon::type_id(false));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<int>() != hamon::type_id(S1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<int>() != hamon::type_id(S2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<int>() != hamon::type_id(TS<int>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<int>() != hamon::type_id(TS<bool>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<int>() != hamon::type_id(E1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<int>() != hamon::type_id(E2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<int>() == hamon::type_id(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<int>() != hamon::type_id(1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<int>() != hamon::type_id(false));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<float>() != hamon::type_id(S1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<float>() != hamon::type_id(S2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<float>() != hamon::type_id(TS<int>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<float>() != hamon::type_id(TS<bool>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<float>() != hamon::type_id(E1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<float>() != hamon::type_id(E2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<float>() != hamon::type_id(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<float>() == hamon::type_id(1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<float>() != hamon::type_id(false));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<bool>() != hamon::type_id(S1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<bool>() != hamon::type_id(S2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<bool>() != hamon::type_id(TS<int>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<bool>() != hamon::type_id(TS<bool>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<bool>() != hamon::type_id(E1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<bool>() != hamon::type_id(E2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<bool>() != hamon::type_id(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<bool>() != hamon::type_id(1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::type_id<bool>() == hamon::type_id(false));
}

}	// namespace hamon_type_info_test
