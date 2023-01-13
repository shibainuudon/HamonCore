/**
 *	@file	unit_test_string_char_traits.cpp
 *
 *	@brief	hamon::char_traits のテスト
 */

#include <hamon/string/char_traits.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_string_test
{

namespace char_traits_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct C
{
	unsigned char c;

	HAMON_CXX11_CONSTEXPR C()
		: c() {}

	HAMON_CXX11_CONSTEXPR C(unsigned long l)
		: c(static_cast<unsigned char>(l)) {}

	HAMON_CXX11_CONSTEXPR operator unsigned long() const
	{
		return static_cast<unsigned long>(c);
	}
};

HAMON_CXX11_CONSTEXPR bool operator==(C const& c1, C const& c2) { return c1.c == c2.c; }
HAMON_CXX11_CONSTEXPR bool operator< (C const& c1, C const& c2) { return c1.c <  c2.c; }


template <typename T>
class CharTraitsTest : public ::testing::Test {};

using CharTraitsTestTypes = ::testing::Types<
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	char16_t,
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	char32_t,
#endif
#if defined(HAMON_HAS_CXX20_CHAR8_T) && !defined(HAMON_PLATFORM_MACOS)
	char8_t,
#endif
	char,
	wchar_t,
	C
>;

TYPED_TEST_SUITE(CharTraitsTest, CharTraitsTestTypes);

TYPED_TEST(CharTraitsTest, TypedefsTest)
{
	using CharTraits = hamon::char_traits<TypeParam>;
	using char_type  = typename CharTraits::char_type;
	using int_type   = typename CharTraits::int_type;
	using off_type   = typename CharTraits::off_type;
	using pos_type   = typename CharTraits::pos_type;
	using state_type = typename CharTraits::state_type;
	char_type c;
	int_type i;
	off_type o;
	pos_type p;
	state_type s;
	(void)c;
	(void)i;
	(void)o;
	(void)p;
	(void)s;
}

TYPED_TEST(CharTraitsTest, EqTest)
{
	using CharTraits = hamon::char_traits<TypeParam>;
	using char_type  = typename CharTraits::char_type;
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( CharTraits::eq(char_type{0}, char_type{0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!CharTraits::eq(char_type{1}, char_type{0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!CharTraits::eq(char_type{0}, char_type{1}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( CharTraits::eq(char_type{1}, char_type{1}));
}

TYPED_TEST(CharTraitsTest, LtTest)
{
	using CharTraits = hamon::char_traits<TypeParam>;
	using char_type = typename CharTraits::char_type;
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!CharTraits::lt(char_type{0}, char_type{0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!CharTraits::lt(char_type{1}, char_type{0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( CharTraits::lt(char_type{0}, char_type{1}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!CharTraits::lt(char_type{1}, char_type{1}));
}

TYPED_TEST(CharTraitsTest, ToCharTypeTest)
{
	using CharTraits = hamon::char_traits<TypeParam>;
	using int_type  = typename CharTraits::int_type;
	using char_type = typename CharTraits::char_type;
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::to_char_type(int_type(0)) == char_type{0});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::to_char_type(int_type(1)) == char_type{1});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::to_char_type(int_type(2)) == char_type{2});
}

TYPED_TEST(CharTraitsTest, ToIntTypeTest)
{
	using CharTraits = hamon::char_traits<TypeParam>;
	using int_type  = typename CharTraits::int_type;
	using char_type = typename CharTraits::char_type;
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::to_int_type(char_type{0}) == int_type(0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::to_int_type(char_type{1}) == int_type(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::to_int_type(char_type{2}) == int_type(2));
}

TYPED_TEST(CharTraitsTest, EqIntTypeTest)
{
	using CharTraits = hamon::char_traits<TypeParam>;
	using int_type  = typename CharTraits::int_type;
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( CharTraits::eq_int_type(int_type(0), int_type(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!CharTraits::eq_int_type(int_type(1), int_type(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!CharTraits::eq_int_type(int_type(0), int_type(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( CharTraits::eq_int_type(int_type(1), int_type(1)));
}

TYPED_TEST(CharTraitsTest, EofTest)
{
	using CharTraits = hamon::char_traits<TypeParam>;
	using int_type  = typename CharTraits::int_type;
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!CharTraits::eq_int_type(CharTraits::eof(), int_type(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!CharTraits::eq_int_type(CharTraits::eof(), int_type(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!CharTraits::eq_int_type(CharTraits::eof(), int_type(2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!CharTraits::eq_int_type(CharTraits::eof(), int_type(3)));
}

TYPED_TEST(CharTraitsTest, NotEofTest)
{
	using CharTraits = hamon::char_traits<TypeParam>;
	using int_type  = typename CharTraits::int_type;
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::not_eof(CharTraits::eof()) != CharTraits::eof());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::not_eof(int_type(0)) == int_type(0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::not_eof(int_type(1)) == int_type(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::not_eof(int_type(2)) == int_type(2));
}

template <typename CharTraits>
inline HAMON_CXX14_CONSTEXPR bool AssignTest()
{
	using char_type = typename CharTraits::char_type;
	{
		char_type c{0};
		CharTraits::assign(c, char_type{1});
		VERIFY(c == char_type{1});
	}
	{
		char_type s[5] {};
		CharTraits::assign(s, 3, char_type{2});
		VERIFY(s[0] == char_type{2});
		VERIFY(s[1] == char_type{2});
		VERIFY(s[2] == char_type{2});
		VERIFY(s[3] == char_type{0});
		VERIFY(s[4] == char_type{0});
	}
	return true;
}

TYPED_TEST(CharTraitsTest, AssignTest)
{
	using CharTraits = hamon::char_traits<TypeParam>;
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AssignTest<CharTraits>());
}

TYPED_TEST(CharTraitsTest, CompareTest)
{
	using CharTraits = hamon::char_traits<TypeParam>;
	using char_type = typename CharTraits::char_type;
	{
		HAMON_CXX11_CONSTEXPR char_type s1[] = {1,2,3};
		HAMON_CXX11_CONSTEXPR char_type s2[] = {1,2,3};
		HAMON_CXX11_CONSTEXPR char_type s3[] = {1,2,4};
		HAMON_CXX11_CONSTEXPR char_type s4[] = {1,2,0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::compare(s1, s2, 3) == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::compare(s1, s3, 3) <  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::compare(s1, s4, 3) >  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::compare(s1, s2, 2) == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::compare(s1, s3, 2) == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::compare(s1, s4, 2) == 0);
	}
}

TYPED_TEST(CharTraitsTest, LengthTest)
{
	using CharTraits = hamon::char_traits<TypeParam>;
	using char_type = typename CharTraits::char_type;
	{
		HAMON_CXX11_CONSTEXPR char_type s1[] = {0};
		HAMON_CXX11_CONSTEXPR char_type s2[] = {3,0};
		HAMON_CXX11_CONSTEXPR char_type s3[] = {3,1,0};
		HAMON_CXX11_CONSTEXPR char_type s4[] = {3,1,4,1,5,9,2,0,6,5,3,5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::length(s1) == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::length(s2) == 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::length(s3) == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::length(s4) == 7);
	}
}

TYPED_TEST(CharTraitsTest, FindTest)
{
	using CharTraits = hamon::char_traits<TypeParam>;
	using char_type = typename CharTraits::char_type;
	{
		HAMON_CXX11_CONSTEXPR char_type s1[] = {1,2,3};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::find(s1, 3, char_type{1}) == s1+0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::find(s1, 3, char_type{2}) == s1+1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::find(s1, 3, char_type{3}) == s1+2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::find(s1, 3, char_type{4}) == nullptr);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::find(s1, 2, char_type{1}) == s1+0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::find(s1, 2, char_type{2}) == s1+1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::find(s1, 2, char_type{3}) == nullptr);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(CharTraits::find(s1, 2, char_type{4}) == nullptr);
	}
}

template <typename CharTraits>
inline HAMON_CXX14_CONSTEXPR bool CopyTest()
{
	using char_type = typename CharTraits::char_type;
	{
		char_type s1[] = {0,0,0};
		char_type const s2[] = {1,2,3};
		auto ret = CharTraits::copy(s1, s2, 3);
		VERIFY(ret == s1);
		VERIFY(s1[0] == char_type{1});
		VERIFY(s1[1] == char_type{2});
		VERIFY(s1[2] == char_type{3});
	}
	{
		char_type s1[] = {0,0,0};
		char_type const s2[] = {1,2,3};
		auto ret = CharTraits::copy(s1, s2, 2);
		VERIFY(ret == s1);
		VERIFY(s1[0] == char_type{1});
		VERIFY(s1[1] == char_type{2});
		VERIFY(s1[2] == char_type{0});
	}
	{
		char_type s1[] = {0,0,0};
		char_type const s2[] = {1,2,3};
		auto ret = CharTraits::copy(s1, s2, 0);
		VERIFY(ret == s1);
		VERIFY(s1[0] == char_type{0});
		VERIFY(s1[1] == char_type{0});
		VERIFY(s1[2] == char_type{0});
	}
	return true;
}

TYPED_TEST(CharTraitsTest, CopyTest)
{
	using CharTraits = hamon::char_traits<TypeParam>;
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CopyTest<CharTraits>());
}

template <typename CharTraits>
inline HAMON_CXX14_CONSTEXPR bool MoveTest()
{
	using char_type = typename CharTraits::char_type;
	{
		char_type s1[] = {1,2,3};
		auto ret = CharTraits::move(s1+1, s1, 2);
		VERIFY(ret == s1+1);
		VERIFY(s1[0] == char_type{1});
		VERIFY(s1[1] == char_type{1});
		VERIFY(s1[2] == char_type{2});
	}
	{
		char_type s1[] = {1,2,3};
		auto ret = CharTraits::move(s1+1, s1, 0);
		VERIFY(ret == s1+1);
		VERIFY(s1[0] == char_type{1});
		VERIFY(s1[1] == char_type{2});
		VERIFY(s1[2] == char_type{3});
	}
	{
		char_type s1[] = {1,2,3};
		auto ret = CharTraits::move(s1, s1+1, 2);
		VERIFY(ret == s1);
		VERIFY(s1[0] == char_type{2});
		VERIFY(s1[1] == char_type{3});
		VERIFY(s1[2] == char_type{3});
	}
	return true;
}

TYPED_TEST(CharTraitsTest, MoveTest)
{
	using CharTraits = hamon::char_traits<TypeParam>;
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MoveTest<CharTraits>());
}

#undef VERIFY

}	// namespace char_traits_test

}	// namespace hamon_string_test
