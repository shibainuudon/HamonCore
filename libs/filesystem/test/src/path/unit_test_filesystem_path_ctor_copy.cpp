/**
 *	@file	unit_test_filesystem_path_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	path(const path& p);
 */

#include <hamon/filesystem/path.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

GTEST_TEST(FilesystemPathTest, CtorCopyTest)
{
	namespace fs = hamon::filesystem;
	static_assert( hamon::is_copy_constructible<fs::path>::value, "");
	static_assert(!hamon::is_nothrow_copy_constructible<fs::path>::value, "");
	static_assert(!hamon::is_trivially_copy_constructible<fs::path>::value, "");
	static_assert( hamon::is_implicitly_copy_constructible<fs::path>::value, "");
	const fs::path p = "foo/bar/baz";
	fs::path p2(p);
	EXPECT_TRUE(p.native() == p2.native());
}
