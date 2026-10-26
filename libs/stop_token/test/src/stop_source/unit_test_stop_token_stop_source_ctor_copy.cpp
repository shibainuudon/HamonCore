/**
 *	@file	unit_test_stop_token_stop_source_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 */

#include <hamon/stop_token/stop_source.hpp>
#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_source_test
{

namespace ctor_copy_test
{

static_assert( hamon::is_copy_constructible_v<hamon::stop_source>, "");
static_assert( hamon::is_nothrow_copy_constructible_v<hamon::stop_source>, "");
static_assert(!hamon::is_trivially_copy_constructible_v<hamon::stop_source>, "");
static_assert( hamon::is_implicitly_copy_constructible_v<hamon::stop_source>, "");

GTEST_TEST(StopSourceTest, CtorCopyTest)
{
	{
		hamon::stop_source source;
		hamon::stop_source copy{ source };

		EXPECT_TRUE(source == copy);

		EXPECT_TRUE(source.stop_possible());
		EXPECT_FALSE(source.stop_requested());

		EXPECT_TRUE(copy.stop_possible());
		EXPECT_FALSE(copy.stop_requested());

		source.request_stop();
		EXPECT_TRUE(source.stop_possible());
		EXPECT_TRUE(source.stop_requested());

		EXPECT_TRUE(copy.stop_possible());
		EXPECT_TRUE(copy.stop_requested());
	}

	// source counter incremented
	{
		hamon::optional<hamon::stop_source> source(hamon::in_place);
		auto st = source->get_token();
		EXPECT_TRUE(st.stop_possible());

		hamon::optional<hamon::stop_source> copy{ source };
		source.reset();

		EXPECT_TRUE(st.stop_possible());

		copy.reset();
		EXPECT_FALSE(st.stop_possible());
	}

	// copy from empty
	{
		hamon::stop_source ss1{ hamon::nostopstate };
		hamon::stop_source copy{ ss1 };
		EXPECT_FALSE(copy.stop_possible());
	}
}

}	// namespace ctor_copy_test

}	// namespace hamon_stop_token_test
