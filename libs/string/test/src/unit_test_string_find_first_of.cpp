/**
 *	@file	unit_test_string_find_first_of.cpp
 *
 *	@brief	find_first_of のテスト
 *
 *	template<class T>
 *	constexpr size_type find_first_of(const T& t, size_type pos = 0) const noexcept(see below);
 *	constexpr size_type find_first_of(const basic_string& str, size_type pos = 0) const noexcept;
 *	constexpr size_type find_first_of(const charT* s, size_type pos, size_type n) const;
 *	constexpr size_type find_first_of(const charT* s, size_type pos = 0) const;
 *	constexpr size_type find_first_of(charT c, size_type pos = 0) const noexcept;
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/string_view.hpp>
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
namespace find_first_of_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
FindFirstOfTest()
{
	using string = hamon::basic_string<CharT>;
	using SizeType = typename string::size_type;
	using Traits = typename string::traits_type;
	using string_view = hamon::basic_string_view<CharT, Traits>;
	using Helper = StringTestHelper<CharT>;

	// template<class T>
	// constexpr size_type find_first_of(const T& t, size_type pos = 0) const noexcept(see below);
	{
		string const s1 = Helper::edcba();
		string_view const s2 = Helper::ab();
		string_view const s3 = Helper::abc();
		string_view const s4 = Helper::abcd();
		string_view const s5 = Helper::ABCDE();
		static_assert(noexcept(s1.find_first_of(s2)), "");
		static_assert(noexcept(s1.find_first_of(s2, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s1.find_first_of(s2)), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s1.find_first_of(s2, SizeType{})), SizeType>::value, "");

		VERIFY(s1.find_first_of(s2) == 3);
		VERIFY(s1.find_first_of(s3) == 2);
		VERIFY(s1.find_first_of(s4) == 1);
		VERIFY(s1.find_first_of(s5) == string::npos);

		VERIFY(s1.find_first_of(s4, 0) == 1);
		VERIFY(s1.find_first_of(s4, 1) == 1);
		VERIFY(s1.find_first_of(s4, 2) == 2);
		VERIFY(s1.find_first_of(s4, 3) == 3);
		VERIFY(s1.find_first_of(s4, 4) == 4);
		VERIFY(s1.find_first_of(s4, 5) == string::npos);
	}

	// constexpr size_type find_first_of(const basic_string& str, size_type pos = 0) const noexcept;
	{
		string const s1 = Helper::edcba();
		string const s2 = Helper::ab();
		string const s3 = Helper::abc();
		string const s4 = Helper::abcd();
		string const s5 = Helper::ABCDE();
		static_assert(noexcept(s1.find_first_of(s2)), "");
		static_assert(noexcept(s1.find_first_of(s2, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s1.find_first_of(s2)), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s1.find_first_of(s2, SizeType{})), SizeType>::value, "");

		VERIFY(s1.find_first_of(s2) == 3);
		VERIFY(s1.find_first_of(s3) == 2);
		VERIFY(s1.find_first_of(s4) == 1);
		VERIFY(s1.find_first_of(s5) == string::npos);

		VERIFY(s1.find_first_of(s4, 0) == 1);
		VERIFY(s1.find_first_of(s4, 1) == 1);
		VERIFY(s1.find_first_of(s4, 2) == 2);
		VERIFY(s1.find_first_of(s4, 3) == 3);
		VERIFY(s1.find_first_of(s4, 4) == 4);
		VERIFY(s1.find_first_of(s4, 5) == string::npos);
	}

	// constexpr size_type find_first_of(const charT* s, size_type pos, size_type n) const;
	// constexpr size_type find_first_of(const charT* s, size_type pos = 0) const;
	{
		string const s = Helper::edcba();
		auto p1 = Helper::ab();
		auto p2 = Helper::abc();
		auto p3 = Helper::abcd();
		auto p4 = Helper::ABCDE();
		//static_assert(noexcept(s.find_first_of(p1)), "");
		//static_assert(noexcept(s.find_first_of(p1, SizeType{})), "");
		//static_assert(noexcept(s.find_first_of(p1, SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.find_first_of(p1)), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s.find_first_of(p1, SizeType{})), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s.find_first_of(p1, SizeType{}, SizeType{})), SizeType>::value, "");

		VERIFY(s.find_first_of(p1) == 3);
		VERIFY(s.find_first_of(p2) == 2);
		VERIFY(s.find_first_of(p3) == 1);
		VERIFY(s.find_first_of(p4) == string::npos);

		VERIFY(s.find_first_of(p3, 0) == 1);
		VERIFY(s.find_first_of(p3, 1) == 1);
		VERIFY(s.find_first_of(p3, 2) == 2);
		VERIFY(s.find_first_of(p3, 3) == 3);
		VERIFY(s.find_first_of(p3, 4) == 4);
		VERIFY(s.find_first_of(p3, 5) == string::npos);

		VERIFY(s.find_first_of(p3, 0, 0) == string::npos);
		VERIFY(s.find_first_of(p3, 0, 1) == 4);
		VERIFY(s.find_first_of(p3, 0, 2) == 3);
		VERIFY(s.find_first_of(p3, 0, 3) == 2);
		VERIFY(s.find_first_of(p3, 0, 4) == 1);
	}

	// constexpr size_type find_first_of(charT c, size_type pos = 0) const noexcept;
	{
		string const s = Helper::aababc();
		auto c1 = Helper::abcd()[0];
		auto c2 = Helper::abcd()[1];
		auto c3 = Helper::abcd()[2];
		auto c4 = Helper::abcd()[3];
		static_assert(noexcept(s.find_first_of(c1)), "");
		static_assert(noexcept(s.find_first_of(c1, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.find_first_of(c1)), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s.find_first_of(c1, SizeType{})), SizeType>::value, "");

		VERIFY(s.find_first_of(c1) == 0);
		VERIFY(s.find_first_of(c2) == 2);
		VERIFY(s.find_first_of(c3) == 5);
		VERIFY(s.find_first_of(c4) == string::npos);

		VERIFY(s.find_first_of(c2, 1) == 2);
		VERIFY(s.find_first_of(c2, 2) == 2);
		VERIFY(s.find_first_of(c2, 3) == 4);
		VERIFY(s.find_first_of(c2, 4) == 4);
		VERIFY(s.find_first_of(c2, 5) == string::npos);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, FindFirstOfTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(FindFirstOfTest<TypeParam>());
}

}	// namespace find_first_of_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
