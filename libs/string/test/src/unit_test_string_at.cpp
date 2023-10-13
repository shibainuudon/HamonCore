/**
 *	@file	unit_test_string_at.cpp
 *
 *	@brief	at のテスト
 *
 *	constexpr const_reference at(size_type n) const;
 *	constexpr reference       at(size_type n);
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
namespace at_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
AtTest()
{
	using string = hamon::basic_string<CharT>;
	using SizeType = typename string::size_type;
	using Reference = typename string::reference;
	using ConstReference = typename string::const_reference;
	using Helper = StringTestHelper<CharT>;

	{
		auto p = Helper::abcde();
		string const s = p;
		static_assert(!noexcept(s.at(SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.at(SizeType{})), ConstReference>::value, "");
		VERIFY(s.at(0) == p[0]);
		VERIFY(s.at(1) == p[1]);
		VERIFY(s.at(2) == p[2]);
		VERIFY(s.at(3) == p[3]);
		VERIFY(s.at(4) == p[4]);
	}
	{
		auto p = Helper::abcde();
		string s = p;
		static_assert(!noexcept(s.at(SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.at(SizeType{})), Reference>::value, "");
		VERIFY(s.at(0) == p[0]);
		VERIFY(s.at(1) == p[1]);
		VERIFY(s.at(2) == p[2]);
		VERIFY(s.at(3) == p[3]);
		VERIFY(s.at(4) == p[4]);
		s.at(2) = CharT{};
		VERIFY(s.at(0) == p[0]);
		VERIFY(s.at(1) == p[1]);
		VERIFY(s.at(2) == CharT{});
		VERIFY(s.at(3) == p[3]);
		VERIFY(s.at(4) == p[4]);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, AtTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(AtTest<TypeParam>());

#if !defined(HAMON_NO_EXCEPTIONS)
	using CharT = TypeParam;
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		string const s{Helper::abcde()};
		EXPECT_NO_THROW((void)s.at(4));
		EXPECT_THROW((void)s.at(5);, std::out_of_range);
	}
	{
		string s{Helper::abcde()};
		EXPECT_NO_THROW((void)s.at(4));
		EXPECT_THROW((void)s.at(5);, std::out_of_range);
	}
#endif
}

}	// namespace at_test
}	// namespace string_test
}	// namespace hamon_test
