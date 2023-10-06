/**
 *	@file	unit_test_string_reserve.cpp
 *
 *	@brief	reserve のテスト
 *
 *	constexpr void reserve(size_type res_arg);
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
namespace reserve_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
ReserveTest()
{
	using string = hamon::basic_string<CharT>;
	using SizeType = typename string::size_type;
	using Helper = StringTestHelper<CharT>;

	{
		string s = Helper::abcde();
		static_assert(!noexcept(s.reserve(SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.reserve(SizeType{})), void>::value, "");

		s.reserve(10);
		VERIFY(s.length() == 5);
		VERIFY(s.capacity() >= 10);

		s.reserve(128);
		VERIFY(s.length() == 5);
		VERIFY(s.capacity() >= 128);

#if 0	// TODO P0966R1
		s.reserve(0);
		VERIFY(s.length() == 5);
		VERIFY(s.capacity() >= 128);
#endif
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, ReserveTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ReserveTest<TypeParam>());
}

}	// namespace reserve_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
