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
	static_assert( hamon::is_move_constructible<hamon::filesystem::path>::value, "");
	static_assert( hamon::is_nothrow_move_constructible<hamon::filesystem::path>::value, "");
	static_assert(!hamon::is_trivially_move_constructible<hamon::filesystem::path>::value, "");
	static_assert( hamon::is_implicitly_move_constructible<hamon::filesystem::path>::value, "");
	const hamon::filesystem::path::string_type s(L"foo");
	const hamon::filesystem::path p(s);
	hamon::filesystem::path p2(hamon::move(p));
	EXPECT_TRUE(p2.native() == s);
}
