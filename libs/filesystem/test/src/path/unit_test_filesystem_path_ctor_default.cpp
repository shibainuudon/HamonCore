/**
 *	@file	unit_test_filesystem_path_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	path() noexcept;
 */

#include <hamon/filesystem/path.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

GTEST_TEST(FilesystemPathTest, CtorDefaultTest)
{
	namespace fs = hamon::filesystem;
	static_assert( hamon::is_default_constructible<fs::path>::value, "");
	static_assert( hamon::is_nothrow_default_constructible<fs::path>::value, "");
	static_assert(!hamon::is_trivially_default_constructible<fs::path>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<fs::path>::value, "");
	fs::path p;
	EXPECT_TRUE(p.empty());
}
