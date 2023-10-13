/**
 *	@file	unit_test_string_clear.cpp
 *
 *	@brief	clear のテスト
 *
 *	constexpr void clear() noexcept;
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
namespace clear_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
ClearTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		string s = Helper::abcde();
		static_assert(noexcept(s.clear()), "");
		static_assert(hamon::is_same<decltype(s.clear()), void>::value, "");

		VERIFY(GeneralCheck(s));
		VERIFY(s.empty() == false);
		
		s.clear();
		
		VERIFY(GeneralCheck(s));
		VERIFY(s.empty() == true);

		s = Helper::long_str();

		VERIFY(GeneralCheck(s));
		VERIFY(s.empty() == false);
		
		s.clear();
		
		VERIFY(GeneralCheck(s));
		VERIFY(s.empty() == true);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, ClearTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ClearTest<TypeParam>());
}

}	// namespace clear_test
}	// namespace string_test
}	// namespace hamon_test
