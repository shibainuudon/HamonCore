/**
 *	@file	unit_test_filesystem_path_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	path(path&& p) noexcept;
 */

#include <hamon/filesystem/path.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>

GTEST_TEST(FilesystemPathTest, CtorMoveTest)
{
	namespace fs = hamon::filesystem;
	static_assert( hamon::is_move_constructible<fs::path>::value, "");
	static_assert( hamon::is_nothrow_move_constructible<fs::path>::value, "");
	static_assert(!hamon::is_trivially_move_constructible<fs::path>::value, "");
	static_assert( hamon::is_implicitly_move_constructible<fs::path>::value, "");
	fs::path p = "foo/bar/baz";
	fs::path p2(hamon::move(p));
	EXPECT_TRUE(p2.string<char>() == "foo/bar/baz");
}
