/**
 *	@file	unit_test_string_data.cpp
 *
 *	@brief	data のテスト
 *
 *	constexpr const charT* data() const noexcept;
 *	constexpr charT* data() noexcept;
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

namespace hamon_test
{
namespace string_test
{
namespace data_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
DataTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		auto src = Helper::abcde();
		string const s = src;
		static_assert(noexcept(s.data()), "");
		static_assert(hamon::is_same<decltype(s.data()), const CharT*>::value, "");

		auto p = s.data();
		VERIFY(p + 0 == &s[0]);
		VERIFY(p + 1 == &s[1]);
		VERIFY(p + 2 == &s[2]);
		VERIFY(p + 3 == &s[3]);
		VERIFY(p + 4 == &s[4]);

		VERIFY(p[0] == src[0]);
		VERIFY(p[1] == src[1]);
		VERIFY(p[2] == src[2]);
		VERIFY(p[3] == src[3]);
		VERIFY(p[4] == src[4]);
		VERIFY(p[5] == CharT{});
	}
	{
		string const s{};
		auto p = s.data();
		VERIFY(p[0] == CharT{});
	}
#if HAMON_CXX_STANDARD >= 17
	{
		auto src = Helper::abcde();
		string s = src;
		static_assert(noexcept(s.data()), "");
		static_assert(hamon::is_same<decltype(s.data()), CharT*>::value, "");

		auto p = s.data();
		VERIFY(p + 0 == &s[0]);
		VERIFY(p + 1 == &s[1]);
		VERIFY(p + 2 == &s[2]);
		VERIFY(p + 3 == &s[3]);
		VERIFY(p + 4 == &s[4]);

		VERIFY(p[0] == src[0]);
		VERIFY(p[1] == src[1]);
		VERIFY(p[2] == src[2]);
		VERIFY(p[3] == src[3]);
		VERIFY(p[4] == src[4]);
		VERIFY(p[5] == CharT{});
	}
	{
		string s{};
		auto p = s.data();
		VERIFY(p[0] == CharT{});
	}
#endif

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, DataTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(DataTest<TypeParam>());
}

}	// namespace data_test
}	// namespace string_test
}	// namespace hamon_test
