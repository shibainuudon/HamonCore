/**
 *	@file	unit_test_static_typeinfo_static_type_info.cpp
 *
 *	@brief	static_type_info のテスト
 */

#include <hamon/static_typeinfo.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_static_typeinfo_test
{

static_assert(!hamon::is_default_constructible<hamon::static_type_info>::value, "");
static_assert( hamon::is_copy_constructible<hamon::static_type_info>::value, "");
static_assert( hamon::is_move_constructible<hamon::static_type_info>::value, "");
static_assert( hamon::is_copy_assignable<hamon::static_type_info>::value, "");
static_assert( hamon::is_move_assignable<hamon::static_type_info>::value, "");

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
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::static_typeid<S1>().name(),       "hamon_static_typeinfo_test::S1");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::static_typeid<S2>().name(),       "hamon_static_typeinfo_test::S2");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::static_typeid<TS<int>>().name(),  "hamon_static_typeinfo_test::TS<int>");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::static_typeid<TS<bool>>().name(), "hamon_static_typeinfo_test::TS<bool>");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::static_typeid<E1>().name(),       "hamon_static_typeinfo_test::E1");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::static_typeid<E2>().name(),       "hamon_static_typeinfo_test::E2");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::static_typeid<int>().name(),      "int");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::static_typeid<float>().name(),    "float");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::static_typeid<char>().name(),     "char");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::static_typeid<bool>().name(),     "bool");
}

GTEST_TEST(TypeInfoTest, HashTest)
{
	HAMON_CXX11_CONSTEXPR auto h1_1 = hamon::static_typeid<S1>().hash();
	HAMON_CXX11_CONSTEXPR auto h1_2 = hamon::static_typeid<S1>().hash();
	HAMON_CXX11_CONSTEXPR auto h2_1 = hamon::static_typeid<S2>().hash();
	HAMON_CXX11_CONSTEXPR auto h2_2 = hamon::static_typeid<S2>().hash();
	HAMON_CXX11_CONSTEXPR auto h3_1 = hamon::static_typeid<TS<int>>().hash();
	HAMON_CXX11_CONSTEXPR auto h3_2 = hamon::static_typeid<TS<int>>().hash();
	HAMON_CXX11_CONSTEXPR auto h4_1 = hamon::static_typeid<TS<bool>>().hash();
	HAMON_CXX11_CONSTEXPR auto h4_2 = hamon::static_typeid<TS<bool>>().hash();
	HAMON_CXX11_CONSTEXPR auto h5_1 = hamon::static_typeid<E1>().hash();
	HAMON_CXX11_CONSTEXPR auto h5_2 = hamon::static_typeid<E1>().hash();
	HAMON_CXX11_CONSTEXPR auto h6_1 = hamon::static_typeid<E2>().hash();
	HAMON_CXX11_CONSTEXPR auto h6_2 = hamon::static_typeid<E2>().hash();
	HAMON_CXX11_CONSTEXPR auto h7_1 = hamon::static_typeid<int>().hash();
	HAMON_CXX11_CONSTEXPR auto h7_2 = hamon::static_typeid<int>().hash();
	HAMON_CXX11_CONSTEXPR auto h8_1 = hamon::static_typeid<float>().hash();
	HAMON_CXX11_CONSTEXPR auto h8_2 = hamon::static_typeid<float>().hash();
	HAMON_CXX11_CONSTEXPR auto h9_1 = hamon::static_typeid<char>().hash();
	HAMON_CXX11_CONSTEXPR auto h9_2 = hamon::static_typeid<char>().hash();
	HAMON_CXX11_CONSTEXPR auto h10_1 = hamon::static_typeid<bool>().hash();
	HAMON_CXX11_CONSTEXPR auto h10_2 = hamon::static_typeid<bool>().hash();
	HAMON_CXX11_CONSTEXPR auto h11_1 = hamon::static_typeid<int const>().hash();
	HAMON_CXX11_CONSTEXPR auto h11_2 = hamon::static_typeid<int const>().hash();

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h1_1 == h1_2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h1_1 == h1_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h1_1 != h2_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h1_1 != h3_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h1_1 != h4_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h1_1 != h5_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h1_1 != h6_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h1_1 != h7_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h1_1 != h8_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h1_1 != h9_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h1_1 != h10_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h1_1 != h11_1);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h2_1 == h2_2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h2_1 != h1_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h2_1 == h2_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h2_1 != h3_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h2_1 != h4_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h2_1 != h5_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h2_1 != h6_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h2_1 != h7_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h2_1 != h8_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h2_1 != h9_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h2_1 != h10_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h2_1 != h11_1);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h3_1 == h3_2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h3_1 != h1_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h3_1 != h2_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h3_1 == h3_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h3_1 != h4_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h3_1 != h5_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h3_1 != h6_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h3_1 != h7_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h3_1 != h8_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h3_1 != h9_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h3_1 != h10_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h3_1 != h11_1);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h4_1 == h4_2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h4_1 != h1_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h4_1 != h2_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h4_1 != h3_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h4_1 == h4_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h4_1 != h5_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h4_1 != h6_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h4_1 != h7_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h4_1 != h8_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h4_1 != h9_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h4_1 != h10_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h4_1 != h11_1);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h5_1 == h5_2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h5_1 != h1_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h5_1 != h2_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h5_1 != h3_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h5_1 != h4_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h5_1 == h5_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h5_1 != h6_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h5_1 != h7_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h5_1 != h8_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h5_1 != h9_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h5_1 != h10_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h5_1 != h11_1);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h6_1 == h6_2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h6_1 != h1_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h6_1 != h2_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h6_1 != h3_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h6_1 != h4_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h6_1 != h5_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h6_1 == h6_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h6_1 != h7_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h6_1 != h8_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h6_1 != h9_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h6_1 != h10_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h6_1 != h11_1);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h7_1 == h7_2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h7_1 != h1_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h7_1 != h2_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h7_1 != h3_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h7_1 != h4_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h7_1 != h5_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h7_1 != h6_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h7_1 == h7_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h7_1 != h8_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h7_1 != h9_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h7_1 != h10_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h7_1 != h11_1);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h8_1 == h8_2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h8_1 != h1_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h8_1 != h2_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h8_1 != h3_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h8_1 != h4_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h8_1 != h5_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h8_1 != h6_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h8_1 != h7_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h8_1 == h8_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h8_1 != h9_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h8_1 != h10_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h8_1 != h11_1);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h9_1 == h9_2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h9_1 != h1_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h9_1 != h2_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h9_1 != h3_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h9_1 != h4_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h9_1 != h5_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h9_1 != h6_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h9_1 != h7_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h9_1 != h8_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h9_1 == h9_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h9_1 != h10_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h9_1 != h11_1);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h10_1 == h10_2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h10_1 != h1_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h10_1 != h2_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h10_1 != h3_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h10_1 != h4_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h10_1 != h5_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h10_1 != h6_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h10_1 != h7_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h10_1 != h8_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h10_1 != h9_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h10_1 == h10_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h10_1 != h11_1);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h11_1 == h11_2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h11_1 != h1_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h11_1 != h2_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h11_1 != h3_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h11_1 != h4_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h11_1 != h5_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h11_1 != h6_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h11_1 != h7_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h11_1 != h8_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h11_1 != h9_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h11_1 != h10_1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h11_1 == h11_1);
}

GTEST_TEST(TypeInfoTest, CompareOperatorTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S1>() == hamon::static_typeid<S1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S1>() != hamon::static_typeid<S2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S1>() != hamon::static_typeid<TS<int>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S1>() != hamon::static_typeid<TS<bool>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S1>() != hamon::static_typeid<E1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S1>() != hamon::static_typeid<E2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S1>() != hamon::static_typeid<int>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S1>() != hamon::static_typeid<float>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S1>() != hamon::static_typeid<bool>());

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S2>() != hamon::static_typeid<S1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S2>() == hamon::static_typeid<S2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S2>() != hamon::static_typeid<TS<int>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S2>() != hamon::static_typeid<TS<bool>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S2>() != hamon::static_typeid<E1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S2>() != hamon::static_typeid<E2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S2>() != hamon::static_typeid<int>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S2>() != hamon::static_typeid<float>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S2>() != hamon::static_typeid<bool>());

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<int>>() != hamon::static_typeid<S1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<int>>() != hamon::static_typeid<S2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<int>>() == hamon::static_typeid<TS<int>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<int>>() != hamon::static_typeid<TS<bool>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<int>>() != hamon::static_typeid<E1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<int>>() != hamon::static_typeid<E2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<int>>() != hamon::static_typeid<int>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<int>>() != hamon::static_typeid<float>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<int>>() != hamon::static_typeid<bool>());

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<bool>>() != hamon::static_typeid<S1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<bool>>() != hamon::static_typeid<S2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<bool>>() != hamon::static_typeid<TS<int>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<bool>>() == hamon::static_typeid<TS<bool>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<bool>>() != hamon::static_typeid<E1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<bool>>() != hamon::static_typeid<E2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<bool>>() != hamon::static_typeid<int>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<bool>>() != hamon::static_typeid<float>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<bool>>() != hamon::static_typeid<bool>());

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E1>() != hamon::static_typeid<S1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E1>() != hamon::static_typeid<S2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E1>() != hamon::static_typeid<TS<int>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E1>() != hamon::static_typeid<TS<bool>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E1>() == hamon::static_typeid<E1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E1>() != hamon::static_typeid<E2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E1>() != hamon::static_typeid<int>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E1>() != hamon::static_typeid<float>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E1>() != hamon::static_typeid<bool>());

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E2>() != hamon::static_typeid<S1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E2>() != hamon::static_typeid<S2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E2>() != hamon::static_typeid<TS<int>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E2>() != hamon::static_typeid<TS<bool>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E2>() != hamon::static_typeid<E1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E2>() == hamon::static_typeid<E2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E2>() != hamon::static_typeid<int>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E2>() != hamon::static_typeid<float>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E2>() != hamon::static_typeid<bool>());

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<int>() != hamon::static_typeid<S1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<int>() != hamon::static_typeid<S2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<int>() != hamon::static_typeid<TS<int>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<int>() != hamon::static_typeid<TS<bool>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<int>() != hamon::static_typeid<E1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<int>() != hamon::static_typeid<E2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<int>() == hamon::static_typeid<int>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<int>() != hamon::static_typeid<float>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<int>() != hamon::static_typeid<bool>());

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<float>() != hamon::static_typeid<S1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<float>() != hamon::static_typeid<S2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<float>() != hamon::static_typeid<TS<int>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<float>() != hamon::static_typeid<TS<bool>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<float>() != hamon::static_typeid<E1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<float>() != hamon::static_typeid<E2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<float>() != hamon::static_typeid<int>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<float>() == hamon::static_typeid<float>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<float>() != hamon::static_typeid<bool>());

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<bool>() != hamon::static_typeid<S1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<bool>() != hamon::static_typeid<S2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<bool>() != hamon::static_typeid<TS<int>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<bool>() != hamon::static_typeid<TS<bool>>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<bool>() != hamon::static_typeid<E1>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<bool>() != hamon::static_typeid<E2>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<bool>() != hamon::static_typeid<int>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<bool>() != hamon::static_typeid<float>());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<bool>() == hamon::static_typeid<bool>());

	//
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S1>() == hamon::static_typeid(S1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S1>() != hamon::static_typeid(S2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S1>() != hamon::static_typeid(TS<int>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S1>() != hamon::static_typeid(TS<bool>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S1>() != hamon::static_typeid(E1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S1>() != hamon::static_typeid(E2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S1>() != hamon::static_typeid(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S1>() != hamon::static_typeid(1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S1>() != hamon::static_typeid(false));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S2>() != hamon::static_typeid(S1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S2>() == hamon::static_typeid(S2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S2>() != hamon::static_typeid(TS<int>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S2>() != hamon::static_typeid(TS<bool>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S2>() != hamon::static_typeid(E1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S2>() != hamon::static_typeid(E2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S2>() != hamon::static_typeid(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S2>() != hamon::static_typeid(1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<S2>() != hamon::static_typeid(false));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<int>>() != hamon::static_typeid(S1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<int>>() != hamon::static_typeid(S2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<int>>() == hamon::static_typeid(TS<int>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<int>>() != hamon::static_typeid(TS<bool>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<int>>() != hamon::static_typeid(E1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<int>>() != hamon::static_typeid(E2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<int>>() != hamon::static_typeid(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<int>>() != hamon::static_typeid(1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<int>>() != hamon::static_typeid(false));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<bool>>() != hamon::static_typeid(S1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<bool>>() != hamon::static_typeid(S2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<bool>>() != hamon::static_typeid(TS<int>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<bool>>() == hamon::static_typeid(TS<bool>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<bool>>() != hamon::static_typeid(E1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<bool>>() != hamon::static_typeid(E2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<bool>>() != hamon::static_typeid(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<bool>>() != hamon::static_typeid(1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<TS<bool>>() != hamon::static_typeid(false));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E1>() != hamon::static_typeid(S1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E1>() != hamon::static_typeid(S2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E1>() != hamon::static_typeid(TS<int>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E1>() != hamon::static_typeid(TS<bool>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E1>() == hamon::static_typeid(E1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E1>() != hamon::static_typeid(E2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E1>() != hamon::static_typeid(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E1>() != hamon::static_typeid(1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E1>() != hamon::static_typeid(false));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E2>() != hamon::static_typeid(S1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E2>() != hamon::static_typeid(S2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E2>() != hamon::static_typeid(TS<int>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E2>() != hamon::static_typeid(TS<bool>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E2>() != hamon::static_typeid(E1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E2>() == hamon::static_typeid(E2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E2>() != hamon::static_typeid(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E2>() != hamon::static_typeid(1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<E2>() != hamon::static_typeid(false));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<int>() != hamon::static_typeid(S1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<int>() != hamon::static_typeid(S2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<int>() != hamon::static_typeid(TS<int>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<int>() != hamon::static_typeid(TS<bool>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<int>() != hamon::static_typeid(E1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<int>() != hamon::static_typeid(E2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<int>() == hamon::static_typeid(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<int>() != hamon::static_typeid(1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<int>() != hamon::static_typeid(false));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<float>() != hamon::static_typeid(S1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<float>() != hamon::static_typeid(S2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<float>() != hamon::static_typeid(TS<int>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<float>() != hamon::static_typeid(TS<bool>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<float>() != hamon::static_typeid(E1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<float>() != hamon::static_typeid(E2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<float>() != hamon::static_typeid(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<float>() == hamon::static_typeid(1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<float>() != hamon::static_typeid(false));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<bool>() != hamon::static_typeid(S1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<bool>() != hamon::static_typeid(S2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<bool>() != hamon::static_typeid(TS<int>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<bool>() != hamon::static_typeid(TS<bool>{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<bool>() != hamon::static_typeid(E1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<bool>() != hamon::static_typeid(E2{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<bool>() != hamon::static_typeid(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<bool>() != hamon::static_typeid(1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::static_typeid<bool>() == hamon::static_typeid(false));
}

}	// namespace hamon_static_typeinfo_test
