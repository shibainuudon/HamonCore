/**
 *	@file	unit_test_string_find_last_of.cpp
 *
 *	@brief	find_last_of のテスト
 *
 *	template<class T>
 *	constexpr size_type find_last_of(const T& t, size_type pos = npos) const noexcept(see below);
 *	constexpr size_type find_last_of(const basic_string& str, size_type pos = npos) const noexcept;
 *	constexpr size_type find_last_of(const charT* s, size_type pos, size_type n) const;
 *	constexpr size_type find_last_of(const charT* s, size_type pos = npos) const;
 *	constexpr size_type find_last_of(charT c, size_type pos = npos) const noexcept;
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
namespace find_last_of_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
FindLastOfTest()
{
	using string = hamon::basic_string<CharT>;
	using SizeType = typename string::size_type;
	using Helper = StringTestHelper<CharT>;

#if HAMON_CXX_STANDARD >= 17	// TODO
	using string_view = std::basic_string_view<CharT>;

	// template<class T>
	// constexpr size_type find_last_of(const T& t, size_type pos = npos) const noexcept(see below);
	{
		string const s1 = Helper::abcde();
		string_view const s2 = Helper::ab();
		string_view const s3 = Helper::abc();
		string_view const s4 = Helper::abcd();
		string_view const s5 = Helper::ABCDE();
		// TODO
		//static_assert(!noexcept(s1.find_last_of(s2)), "");
		//static_assert(!noexcept(s1.find_last_of(s2, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s1.find_last_of(s2)), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s1.find_last_of(s2, SizeType{})), SizeType>::value, "");

		VERIFY(s1.find_last_of(s2) == 1);
		VERIFY(s1.find_last_of(s3) == 2);
		VERIFY(s1.find_last_of(s4) == 3);
		VERIFY(s1.find_last_of(s5) == string::npos);

		VERIFY(s1.find_last_of(s3, 0) == 0);
		VERIFY(s1.find_last_of(s3, 1) == 1);
		VERIFY(s1.find_last_of(s3, 2) == 2);
		VERIFY(s1.find_last_of(s3, 3) == 2);
		VERIFY(s1.find_last_of(s3, 4) == 2);
	}
#endif

	// constexpr size_type find_last_of(const basic_string& str, size_type pos = npos) const noexcept;
	{
		string const s1 = Helper::abcde();
		string const s2 = Helper::ab();
		string const s3 = Helper::abc();
		string const s4 = Helper::abcd();
		string const s5 = Helper::ABCDE();
		static_assert(noexcept(s1.find_last_of(s2)), "");
		static_assert(noexcept(s1.find_last_of(s2, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s1.find_last_of(s2)), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s1.find_last_of(s2, SizeType{})), SizeType>::value, "");

		VERIFY(s1.find_last_of(s2) == 1);
		VERIFY(s1.find_last_of(s3) == 2);
		VERIFY(s1.find_last_of(s4) == 3);
		VERIFY(s1.find_last_of(s5) == string::npos);

		VERIFY(s1.find_last_of(s3, 0) == 0);
		VERIFY(s1.find_last_of(s3, 1) == 1);
		VERIFY(s1.find_last_of(s3, 2) == 2);
		VERIFY(s1.find_last_of(s3, 3) == 2);
		VERIFY(s1.find_last_of(s3, 4) == 2);
	}

	// constexpr size_type find_last_of(const charT* s, size_type pos, size_type n) const;
	// constexpr size_type find_last_of(const charT* s, size_type pos = npos) const;
	{
		string const s = Helper::abcde();
		auto p1 = Helper::ab();
		auto p2 = Helper::abc();
		auto p3 = Helper::abcd();
		auto p4 = Helper::ABCDE();
		static_assert(noexcept(s.find_last_of(p1)), "");
		static_assert(noexcept(s.find_last_of(p1, SizeType{})), "");
		static_assert(noexcept(s.find_last_of(p1, SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.find_last_of(p1)), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s.find_last_of(p1, SizeType{})), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s.find_last_of(p1, SizeType{}, SizeType{})), SizeType>::value, "");

		VERIFY(s.find_last_of(p1) == 1);
		VERIFY(s.find_last_of(p2) == 2);
		VERIFY(s.find_last_of(p3) == 3);
		VERIFY(s.find_last_of(p4) == string::npos);

		VERIFY(s.find_last_of(p2, 0) == 0);
		VERIFY(s.find_last_of(p2, 1) == 1);
		VERIFY(s.find_last_of(p2, 2) == 2);
		VERIFY(s.find_last_of(p2, 3) == 2);
		VERIFY(s.find_last_of(p2, 4) == 2);

		VERIFY(s.find_last_of(p2, string::npos, 0) == string::npos);
		VERIFY(s.find_last_of(p2, string::npos, 1) == 0);
		VERIFY(s.find_last_of(p2, string::npos, 2) == 1);
		VERIFY(s.find_last_of(p2, string::npos, 3) == 2);
		VERIFY(s.find_last_of(p2, string::npos, 4) == 2);
	}

	// constexpr size_type find_last_of(charT c, size_type pos = npos) const noexcept;
	{
		string const s = Helper::aababc();
		auto c1 = Helper::abcd()[0];
		auto c2 = Helper::abcd()[1];
		auto c3 = Helper::abcd()[2];
		auto c4 = Helper::abcd()[3];
		static_assert(noexcept(s.find_last_of(c1)), "");
		static_assert(noexcept(s.find_last_of(c1, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.find_last_of(c1)), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s.find_last_of(c1, SizeType{})), SizeType>::value, "");

		VERIFY(s.find_last_of(c1) == 3);
		VERIFY(s.find_last_of(c2) == 4);
		VERIFY(s.find_last_of(c3) == 5);
		VERIFY(s.find_last_of(c4) == string::npos);

		VERIFY(s.find_last_of(c2, 0) == string::npos);
		VERIFY(s.find_last_of(c2, 1) == string::npos);
		VERIFY(s.find_last_of(c2, 2) == 2);
		VERIFY(s.find_last_of(c2, 3) == 2);
		VERIFY(s.find_last_of(c2, 4) == 4);
		VERIFY(s.find_last_of(c2, 5) == 4);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, FindLastOfTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FindLastOfTest<TypeParam>());
}

}	// namespace find_last_of_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
