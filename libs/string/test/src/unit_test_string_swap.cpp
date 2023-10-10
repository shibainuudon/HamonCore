/**
 *	@file	unit_test_string_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	constexpr void swap(basic_string& str) noexcept(...);
 * 
 *	template<class charT, class traits, class Allocator>
 *	constexpr void swap(
 *		basic_string<charT, traits, Allocator>& lhs,
 *		basic_string<charT, traits, Allocator>& rhs)
 *			noexcept(noexcept(lhs.swap(rhs)));
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

HAMON_WARNING_PUSH()
#if defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION >= 120000)
HAMON_WARNING_DISABLE_GCC("-Wstringop-overflow")
#endif

namespace hamon_test
{
namespace string_test
{
namespace swap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
SwapTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;
	
	auto p1 = Helper::abcde();
	auto p2 = Helper::abb();

	string s1 = p1;
	string s2 = p2;

	static_assert(noexcept(s1.swap(s2)), "");
	static_assert(noexcept(swap(s1, s2)), "");
	static_assert(hamon::is_same<decltype(s1.swap(s2)), void>::value, "");
	static_assert(hamon::is_same<decltype(swap(s1, s2)), void>::value, "");

	VERIFY(s1.size() == 5);
	VERIFY(s1[0] == p1[0]);
	VERIFY(s1[1] == p1[1]);
	VERIFY(s1[2] == p1[2]);
	VERIFY(s1[3] == p1[3]);
	VERIFY(s1[4] == p1[4]);
	VERIFY(s2.size() == 3);
	VERIFY(s2[0] == p2[0]);
	VERIFY(s2[1] == p2[1]);
	VERIFY(s2[2] == p2[2]);

	s1.swap(s2);

	VERIFY(s1.size() == 3);
	VERIFY(s1[0] == p2[0]);
	VERIFY(s1[1] == p2[1]);
	VERIFY(s1[2] == p2[2]);
	VERIFY(s2.size() == 5);
	VERIFY(s2[0] == p1[0]);
	VERIFY(s2[1] == p1[1]);
	VERIFY(s2[2] == p1[2]);
	VERIFY(s2[3] == p1[3]);
	VERIFY(s2[4] == p1[4]);

	swap(s1, s2);

	VERIFY(s1.size() == 5);
	VERIFY(s1[0] == p1[0]);
	VERIFY(s1[1] == p1[1]);
	VERIFY(s1[2] == p1[2]);
	VERIFY(s1[3] == p1[3]);
	VERIFY(s1[4] == p1[4]);
	VERIFY(s2.size() == 3);
	VERIFY(s2[0] == p2[0]);
	VERIFY(s2[1] == p2[1]);
	VERIFY(s2[2] == p2[2]);

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, SwapTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SwapTest<TypeParam>());
}

}	// namespace swap_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
