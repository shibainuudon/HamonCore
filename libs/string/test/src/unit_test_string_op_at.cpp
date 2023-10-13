/**
 *	@file	unit_test_string_op_at.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	constexpr const_reference operator[](size_type pos) const;
 *	constexpr reference       operator[](size_type pos);
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
namespace op_at_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
OpAtTest()
{
	using string = hamon::basic_string<CharT>;
	using SizeType = typename string::size_type;
	using Reference = typename string::reference;
	using ConstReference = typename string::const_reference;
	using Helper = StringTestHelper<CharT>;

	{
		auto p = Helper::abcde();
		string const s = p;
		//static_assert(noexcept(s[SizeType{}]), "");
		static_assert(hamon::is_same<decltype(s[SizeType{}]), ConstReference>::value, "");
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[2]);
		VERIFY(s[3] == p[3]);
		VERIFY(s[4] == p[4]);
	}
	{
		auto p = Helper::abcde();
		string s = p;
//		static_assert(noexcept(s[SizeType{}]), "");
		static_assert(hamon::is_same<decltype(s[SizeType{}]), Reference>::value, "");
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[2]);
		VERIFY(s[3] == p[3]);
		VERIFY(s[4] == p[4]);
		s[2] = CharT{};
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == CharT{});
		VERIFY(s[3] == p[3]);
		VERIFY(s[4] == p[4]);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, OpAtTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(OpAtTest<TypeParam>());
}

}	// namespace op_at_test
}	// namespace string_test
}	// namespace hamon_test
