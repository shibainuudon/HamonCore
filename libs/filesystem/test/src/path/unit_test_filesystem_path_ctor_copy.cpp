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
	static_assert( hamon::is_copy_constructible<hamon::filesystem::path>::value, "");
	static_assert(!hamon::is_nothrow_copy_constructible<hamon::filesystem::path>::value, "");
	static_assert(!hamon::is_trivially_copy_constructible<hamon::filesystem::path>::value, "");
	static_assert( hamon::is_implicitly_copy_constructible<hamon::filesystem::path>::value, "");
	const hamon::filesystem::path::string_type s(L"foo");
	const hamon::filesystem::path p(s);
	hamon::filesystem::path p2(p);
	EXPECT_TRUE(p.native() == s);
	EXPECT_TRUE(p2.native() == s);
}
