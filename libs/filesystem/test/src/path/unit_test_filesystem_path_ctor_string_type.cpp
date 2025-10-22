/**
 *	@file	unit_test_filesystem_path_ctor_string_type.cpp
 *
 *	@brief	string_typeを引数に取るコンストラクタのテスト
 *
 *	path(string_type&& source, format fmt = auto_format);
 */

#include <hamon/filesystem/path.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <gtest/gtest.h>

GTEST_TEST(FilesystemPathTest, CtorStringTypeTest)
{
	namespace fs = hamon::filesystem;
	using value_type = fs::path::value_type;
	using string_type = fs::path::string_type;
	{
		static_assert( hamon::is_constructible<fs::path, string_type&&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<fs::path, string_type&&>::value, "");
		static_assert(!hamon::is_trivially_constructible<fs::path, string_type&&>::value, "");
		static_assert( hamon::is_implicitly_constructible<fs::path, string_type&&>::value, "");
		string_type s = HAMON_STATICALLY_WIDEN(value_type, "foo/bar/baz");
		fs::path p = hamon::move(s);
		EXPECT_TRUE(p.native() == HAMON_STATICALLY_WIDEN(value_type, "foo/bar/baz"));
	}
	{
		static_assert( hamon::is_constructible<fs::path, string_type&&, fs::path::format>::value, "");
		static_assert(!hamon::is_nothrow_constructible<fs::path, string_type&&, fs::path::format>::value, "");
		static_assert(!hamon::is_trivially_constructible<fs::path, string_type&&, fs::path::format>::value, "");
		static_assert( hamon::is_implicitly_constructible<fs::path, string_type&&, fs::path::format>::value, "");
		string_type s = HAMON_STATICALLY_WIDEN(value_type, "foo/bar/baz");
		fs::path p{hamon::move(s), fs::path::format::native_format};
		EXPECT_TRUE(p.native() == HAMON_STATICALLY_WIDEN(value_type, "foo/bar/baz"));
	}
}
