/**
 *	@file	unit_test_any_ctor_in_place_type_args.cpp
 *
 *	@brief	in_place_type_tと引数をとるコンストラクタのテスト
 *
 *	template<class T, class... Args>
 *	explicit any(in_place_type_t<T>, Args&&... args);
 */

#include <hamon/any.hpp>
#include <hamon/utility/in_place_type.hpp>
#include <gtest/gtest.h>
#include <string>

GTEST_TEST(AnyTest, CtorInPlaceTypeArgsTest)
{
	{
		hamon::any a { hamon::in_place_type_t<double>{}, 42};
		EXPECT_TRUE(a.has_value());
		EXPECT_EQ(42, hamon::any_cast<double>(a));
	}
	{
		hamon::any a { hamon::in_place_type_t<std::string>{}, 3u, 'X'};
		EXPECT_TRUE(a.has_value());
		EXPECT_EQ("XXX", hamon::any_cast<std::string>(a));
	}
}
