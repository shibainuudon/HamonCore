/**
 *	@file	unit_test_string_shrink_to_fit.cpp
 *
 *	@brief	shrink_to_fit のテスト
 *
 *	constexpr void shrink_to_fit();
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

HAMON_WARNING_PUSH()
#if defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION >= 120000)
HAMON_WARNING_DISABLE_GCC("-Wstringop-overread")
#endif

namespace hamon_test
{
namespace string_test
{
namespace shrink_to_fit_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
ShrinkToFitTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		string s = Helper::abcde();
//		static_assert(!noexcept(s.shrink_to_fit()), "");
		static_assert(hamon::is_same<decltype(s.shrink_to_fit()), void>::value, "");

		s.reserve(128);
		VERIFY(s.length() == 5);
		VERIFY(s.capacity() >= 128);

		s.shrink_to_fit();
		VERIFY(s.length() == 5);
		VERIFY(s.capacity() >= 5);	// 実際にcapacity が減っているかどうかは実装依存
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, ShrinkToFitTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ShrinkToFitTest<TypeParam>());
}

}	// namespace shrink_to_fit_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
