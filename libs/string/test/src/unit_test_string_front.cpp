/**
 *	@file	unit_test_string_front.cpp
 *
 *	@brief	front のテスト
 *
 *	constexpr const charT& front() const;
 *	constexpr charT&       front();
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
namespace front_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
FrontTest()
{
	using string = hamon::basic_string<CharT>;
	using Reference = typename string::reference;
	using ConstReference = typename string::const_reference;
	using Helper = StringTestHelper<CharT>;

	{
		auto p = Helper::abcde();
		string const s = p;
		static_assert(noexcept(s.front()), "");
		static_assert(hamon::is_same<decltype(s.front()), ConstReference>::value, "");
		VERIFY(s.front() == p[0]);
		VERIFY(s.front() == s[0]);
	}
	{
		auto p = Helper::abcde();
		string s = p;
		static_assert(noexcept(s.front()), "");
		static_assert(hamon::is_same<decltype(s.front()), Reference>::value, "");
		VERIFY(s.front() == p[0]);
		VERIFY(s.front() == s[0]);
		s.front() = CharT{};
		VERIFY(s.front() != p[0]);
		VERIFY(s.front() == CharT{});
		VERIFY(s.front() == s[0]);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, FrontTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FrontTest<TypeParam>());
}

}	// namespace front_test
}	// namespace string_test
}	// namespace hamon_test
