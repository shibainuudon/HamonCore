/**
 *	@file	unit_test_string_op_compare.cpp
 *
 *	@brief	operator==, operator<=> のテスト
 *
 *	template<class charT, class traits, class Allocator>
 *	constexpr bool operator==(
 *		const basic_string<charT, traits, Allocator>& lhs,
 *		const basic_string<charT, traits, Allocator>& rhs) noexcept;
 *	
 *	template<class charT, class traits, class Allocator>
 *	constexpr bool operator==(
 *		const basic_string<charT, traits, Allocator>& lhs,
 *		const charT* rhs);
 *	
 *	template<class charT, class traits, class Allocator>
 *	constexpr see below operator<=>(
 *		const basic_string<charT, traits, Allocator>& lhs,
 *		const basic_string<charT, traits, Allocator>& rhs) noexcept;
 *	
 *	template<class charT, class traits, class Allocator>
 *	constexpr see below operator<=>(
 *		const basic_string<charT, traits, Allocator>& lhs,
 *		const charT* rhs);
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/compare.hpp>
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
namespace op_compare_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
OpCompareTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// template<class charT, class traits, class Allocator>
	// constexpr bool operator==(
	// 	const basic_string<charT, traits, Allocator>& lhs,
	// 	const basic_string<charT, traits, Allocator>& rhs) noexcept;
	//
	// template<class charT, class traits, class Allocator>
	// constexpr see below operator<=>(
	// 	const basic_string<charT, traits, Allocator>& lhs,
	// 	const basic_string<charT, traits, Allocator>& rhs) noexcept;
	{
		string const s1{Helper::aababc(), 6};	// "aababc"
		string const s2 = s1;					// "aababc"
		string const s3 = s1.substr(0, 5);		// "aabab"
		string const s4 = s1.substr(1, 5);		// "ababc"

		static_assert(noexcept(s1 == s2), "");
		static_assert(noexcept(s1 != s2), "");
		static_assert(noexcept(s1 <  s2), "");
		static_assert(noexcept(s1 >  s2), "");
		static_assert(noexcept(s1 <= s2), "");
		static_assert(noexcept(s1 >= s2), "");
		static_assert(hamon::is_same<decltype(s1 == s2), bool>::value, "");
		static_assert(hamon::is_same<decltype(s1 != s2), bool>::value, "");
		static_assert(hamon::is_same<decltype(s1 <  s2), bool>::value, "");
		static_assert(hamon::is_same<decltype(s1 >  s2), bool>::value, "");
		static_assert(hamon::is_same<decltype(s1 <= s2), bool>::value, "");
		static_assert(hamon::is_same<decltype(s1 >= s2), bool>::value, "");

		VERIFY( (s1 == s1));
		VERIFY( (s1 == s2));
		VERIFY(!(s1 == s3));
		VERIFY(!(s1 == s4));

		VERIFY(!(s1 != s1));
		VERIFY(!(s1 != s2));
		VERIFY( (s1 != s3));
		VERIFY( (s1 != s4));

		VERIFY(!(s1 <  s1));
		VERIFY(!(s1 <  s2));
		VERIFY(!(s1 <  s3));
		VERIFY( (s1 <  s4));

		VERIFY(!(s1 >  s1));
		VERIFY(!(s1 >  s2));
		VERIFY( (s1 >  s3));
		VERIFY(!(s1 >  s4));

		VERIFY( (s1 <= s1));
		VERIFY( (s1 <= s2));
		VERIFY(!(s1 <= s3));
		VERIFY( (s1 <= s4));

		VERIFY( (s1 >= s1));
		VERIFY( (s1 >= s2));
		VERIFY( (s1 >= s3));
		VERIFY(!(s1 >= s4));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(noexcept(s1 <=> s2), "");
		//static_assert(hamon::is_same<decltype(s1 <=> s2), /* TODO */>::value, "");

		VERIFY(hamon::is_eq(s1 <=> s1));
		VERIFY(hamon::is_eq(s1 <=> s2));
		VERIFY(hamon::is_gt(s1 <=> s3));
		VERIFY(hamon::is_lt(s1 <=> s4));
#endif
	}

	// template<class charT, class traits, class Allocator>
	// constexpr bool operator==(
	// 	const basic_string<charT, traits, Allocator>& lhs,
	// 	const charT* rhs);
	//
	// template<class charT, class traits, class Allocator>
	// constexpr see below operator<=>(
	// 	const basic_string<charT, traits, Allocator>& lhs,
	// 	const charT* rhs);
	{
		string const s1{Helper::abcd()};		// "abcd"
		CharT const* p1 = Helper::abcd();		// "abcd"
		CharT const* p2 = Helper::aababc();		// "aababc"
		CharT const* p3 = Helper::bcd();		// "bcd"

		//static_assert(!noexcept(s1 == p1), "");
		//static_assert(!noexcept(s1 != p1), "");
		//static_assert(!noexcept(s1 <  p1), "");
		//static_assert(!noexcept(s1 >  p1), "");
		//static_assert(!noexcept(s1 <= p1), "");
		//static_assert(!noexcept(s1 >= p1), "");
		static_assert(hamon::is_same<decltype(s1 == p1), bool>::value, "");
		static_assert(hamon::is_same<decltype(s1 != p1), bool>::value, "");
		static_assert(hamon::is_same<decltype(s1 <  p1), bool>::value, "");
		static_assert(hamon::is_same<decltype(s1 >  p1), bool>::value, "");
		static_assert(hamon::is_same<decltype(s1 <= p1), bool>::value, "");
		static_assert(hamon::is_same<decltype(s1 >= p1), bool>::value, "");

		VERIFY( (s1 == p1));
		VERIFY(!(s1 == p2));
		VERIFY(!(s1 == p3));

		VERIFY(!(s1 != p1));
		VERIFY( (s1 != p2));
		VERIFY( (s1 != p3));

		VERIFY(!(s1 <  p1));
		VERIFY(!(s1 <  p2));
		VERIFY( (s1 <  p3));

		VERIFY(!(s1 >  p1));
		VERIFY( (s1 >  p2));
		VERIFY(!(s1 >  p3));

		VERIFY( (s1 <= p1));
		VERIFY(!(s1 <= p2));
		VERIFY( (s1 <= p3));

		VERIFY( (s1 >= p1));
		VERIFY( (s1 >= p2));
		VERIFY(!(s1 >= p3));

		VERIFY( (p1 == s1));
		VERIFY(!(p2 == s1));
		VERIFY(!(p3 == s1));

		VERIFY(!(p1 != s1));
		VERIFY( (p2 != s1));
		VERIFY( (p3 != s1));

		VERIFY(!(p1 <  s1));
		VERIFY( (p2 <  s1));
		VERIFY(!(p3 <  s1));

		VERIFY(!(p1 >  s1));
		VERIFY(!(p2 >  s1));
		VERIFY( (p3 >  s1));

		VERIFY( (p1 <= s1));
		VERIFY( (p2 <= s1));
		VERIFY(!(p3 <= s1));

		VERIFY( (p1 >= s1));
		VERIFY(!(p2 >= s1));
		VERIFY( (p3 >= s1));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		//static_assert(!noexcept(s1 <=> p1), "");
		//static_assert(hamon::is_same<decltype(s1 <=> p1), /* TODO */>::value, "");

		VERIFY(hamon::is_eq(s1 <=> p1));
		VERIFY(hamon::is_gt(s1 <=> p2));
		VERIFY(hamon::is_lt(s1 <=> p3));

		VERIFY(hamon::is_eq(p1 <=> s1));
		VERIFY(hamon::is_lt(p2 <=> s1));
		VERIFY(hamon::is_gt(p3 <=> s1));
#endif
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, OpCompareTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(OpCompareTest<TypeParam>());
}

}	// namespace op_compare_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
