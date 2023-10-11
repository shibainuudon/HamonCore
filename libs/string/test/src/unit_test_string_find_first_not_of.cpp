/**
 *	@file	unit_test_string_find_first_not_of.cpp
 *
 *	@brief	find_first_not_of のテスト
 *
 *	template<class T>
 *	constexpr size_type find_first_not_of(const T& t, size_type pos = 0) const noexcept(see below);
 *	constexpr size_type find_first_not_of(const basic_string& str, size_type pos = 0) const noexcept;
 *	constexpr size_type find_first_not_of(const charT* s, size_type pos, size_type n) const;
 *	constexpr size_type find_first_not_of(const charT* s, size_type pos = 0) const;
 *	constexpr size_type find_first_not_of(charT c, size_type pos = 0) const noexcept;
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
namespace find_first_not_of_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
FindFirstNotOfTest()
{
	using string = hamon::basic_string<CharT>;
	using SizeType = typename string::size_type;
	using Helper = StringTestHelper<CharT>;

#if HAMON_CXX_STANDARD >= 17	// TODO
	using string_view = std::basic_string_view<CharT>;

	// template<class T>
	// constexpr size_type find_first_not_of(const T& t, size_type pos = 0) const noexcept(see below);
	{
		string const s1 = Helper::abcde();
		string_view const s2 = Helper::ab();
		string_view const s3 = Helper::abc();
		string_view const s4 = Helper::abcd();
		string_view const s5 = Helper::abcde();
		// TODO
		//static_assert(!noexcept(s1.find_first_not_of(s2)), "");
		static_assert(hamon::is_same<decltype(s1.find_first_not_of(s2)), SizeType>::value, "");

		VERIFY(s1.find_first_not_of(s2) == 2);
		VERIFY(s1.find_first_not_of(s3) == 3);
		VERIFY(s1.find_first_not_of(s4) == 4);
		VERIFY(s1.find_first_not_of(s5) == string::npos);
	}
	{
		string const s1 = Helper::edcba();
		string_view const s2 = Helper::ab();
		// TODO
		//static_assert(!noexcept(s1.find_first_not_of(s2, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s1.find_first_not_of(s2, SizeType{})), SizeType>::value, "");

		VERIFY(s1.find_first_not_of(s2, 0) == 0);
		VERIFY(s1.find_first_not_of(s2, 1) == 1);
		VERIFY(s1.find_first_not_of(s2, 2) == 2);
		VERIFY(s1.find_first_not_of(s2, 3) == string::npos);
	}
#endif

	// constexpr size_type find_first_not_of(const basic_string& str, size_type pos = 0) const noexcept;
	{
		string const s1 = Helper::abcde();
		string const s2 = Helper::ab();
		string const s3 = Helper::abc();
		string const s4 = Helper::abcd();
		string const s5 = Helper::abcde();
		static_assert(noexcept(s1.find_first_not_of(s2)), "");
		static_assert(hamon::is_same<decltype(s1.find_first_not_of(s2)), SizeType>::value, "");

		VERIFY(s1.find_first_not_of(s2) == 2);
		VERIFY(s1.find_first_not_of(s3) == 3);
		VERIFY(s1.find_first_not_of(s4) == 4);
		VERIFY(s1.find_first_not_of(s5) == string::npos);
	}
	{
		string const s1 = Helper::edcba();
		string const s2 = Helper::ab();
		static_assert(noexcept(s1.find_first_not_of(s2, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s1.find_first_not_of(s2, SizeType{})), SizeType>::value, "");

		VERIFY(s1.find_first_not_of(s2, 0) == 0);
		VERIFY(s1.find_first_not_of(s2, 1) == 1);
		VERIFY(s1.find_first_not_of(s2, 2) == 2);
		VERIFY(s1.find_first_not_of(s2, 3) == string::npos);
	}

	// constexpr size_type find_first_not_of(const charT* s, size_type pos, size_type n) const;
	// constexpr size_type find_first_not_of(const charT* s, size_type pos = 0) const;
	{
		string const s = Helper::abcde();
		auto p1 = Helper::ab();
		auto p2 = Helper::abc();
		auto p3 = Helper::abcd();
		auto p4 = Helper::abcde();
		static_assert(noexcept(s.find_first_not_of(p1)), "");
		static_assert(hamon::is_same<decltype(s.find_first_not_of(p1)), SizeType>::value, "");

		VERIFY(s.find_first_not_of(p1) == 2);
		VERIFY(s.find_first_not_of(p2) == 3);
		VERIFY(s.find_first_not_of(p3) == 4);
		VERIFY(s.find_first_not_of(p4) == string::npos);
	}
	{
		string const s = Helper::edcba();
		auto p = Helper::ab();
		static_assert(noexcept(s.find_first_not_of(p, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.find_first_not_of(p, SizeType{})), SizeType>::value, "");

		VERIFY(s.find_first_not_of(p, 0) == 0);
		VERIFY(s.find_first_not_of(p, 1) == 1);
		VERIFY(s.find_first_not_of(p, 2) == 2);
		VERIFY(s.find_first_not_of(p, 3) == string::npos);
	}
	{
		string const s = Helper::abcde();
		auto p = Helper::abcde();
		static_assert(noexcept(s.find_first_not_of(p, SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.find_first_not_of(p, SizeType{}, SizeType{})), SizeType>::value, "");

		VERIFY(s.find_first_not_of(p, 1, 1) == 1);
		VERIFY(s.find_first_not_of(p, 1, 2) == 2);
		VERIFY(s.find_first_not_of(p, 1, 3) == 3);
		VERIFY(s.find_first_not_of(p, 1, 4) == 4);
		VERIFY(s.find_first_not_of(p, 1, 5) == string::npos);
	}

	// constexpr size_type find_first_not_of(charT c, size_type pos = 0) const noexcept;
	{
		string const s = Helper::aababc();
		auto c1 = Helper::abcd()[0];
		auto c2 = Helper::abcd()[1];
		auto c3 = Helper::abcd()[2];
		static_assert(noexcept(s.find_first_not_of(c1)), "");
		static_assert(noexcept(s.find_first_not_of(c1, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.find_first_not_of(c1)), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s.find_first_not_of(c1, SizeType{})), SizeType>::value, "");

		VERIFY(s.find_first_not_of(c1) == 2);
		VERIFY(s.find_first_not_of(c2) == 0);
		VERIFY(s.find_first_not_of(c3) == 0);

		VERIFY(s.find_first_not_of(c2, 1) == 1);
		VERIFY(s.find_first_not_of(c2, 2) == 3);
		VERIFY(s.find_first_not_of(c2, 3) == 3);
		VERIFY(s.find_first_not_of(c2, 4) == 5);
		VERIFY(s.find_first_not_of(c2, 5) == 5);
		VERIFY(s.find_first_not_of(c2, 6) == string::npos);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, FindFirstNotOfTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FindFirstNotOfTest<TypeParam>());
}

}	// namespace find_first_not_of_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
