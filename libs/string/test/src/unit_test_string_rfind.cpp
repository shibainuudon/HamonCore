/**
 *	@file	unit_test_string_rfind.cpp
 *
 *	@brief	rfind のテスト
 *
 *	template<class T>
 *	constexpr size_type rfind(const T& t, size_type pos = npos) const noexcept(see below);
 *	constexpr size_type rfind(const basic_string& str, size_type pos = npos) const noexcept;
 *	constexpr size_type rfind(const charT* s, size_type pos, size_type n) const;
 *	constexpr size_type rfind(const charT* s, size_type pos = npos) const;
 *	constexpr size_type rfind(charT c, size_type pos = npos) const noexcept;
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
namespace rfind_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
RFindTest()
{
	using string = hamon::basic_string<CharT>;
	using SizeType = typename string::size_type;
	using Traits = typename string::traits_type;
	using string_view = hamon::basic_string_view<CharT, Traits>;
	using Helper = StringTestHelper<CharT>;

	// template<class T>
	// constexpr size_type rfind(const T& t, size_type pos = npos) const noexcept(see below);
	{
		string const s1 = Helper::aababc();
		string_view const s2 = Helper::ab();
		string_view const s3 = Helper::abc();
		string_view const s4 = Helper::abcd();
		static_assert(noexcept(s1.rfind(s2)), "");
		static_assert(noexcept(s1.rfind(s2, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s1.rfind(s2)), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s1.rfind(s2, SizeType{})), SizeType>::value, "");

		VERIFY(s1.rfind(s2) == 3);
		VERIFY(s1.rfind(s3) == 3);
		VERIFY(s1.rfind(s4) == string::npos);

		VERIFY(s1.rfind(s2, 0) == string::npos);
		VERIFY(s1.rfind(s2, 1) == 1);
		VERIFY(s1.rfind(s2, 2) == 1);
		VERIFY(s1.rfind(s2, 3) == 3);
		VERIFY(s1.rfind(s2, 4) == 3);
	}

	// constexpr size_type rfind(const basic_string& str, size_type pos = npos) const noexcept;
	{
		string const s1 = Helper::aababc();
		string const s2 = Helper::ab();
		string const s3 = Helper::abc();
		string const s4 = Helper::abcd();
		static_assert(noexcept(s1.rfind(s2)), "");
		static_assert(noexcept(s1.rfind(s2, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s1.rfind(s2)), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s1.rfind(s2, SizeType{})), SizeType>::value, "");

		VERIFY(s1.rfind(s2) == 3);
		VERIFY(s1.rfind(s3) == 3);
		VERIFY(s1.rfind(s4) == string::npos);

		VERIFY(s1.rfind(s2, 0) == string::npos);
		VERIFY(s1.rfind(s2, 1) == 1);
		VERIFY(s1.rfind(s2, 2) == 1);
		VERIFY(s1.rfind(s2, 3) == 3);
		VERIFY(s1.rfind(s2, 4) == 3);
	}

	// constexpr size_type rfind(const charT* s, size_type pos, size_type n) const;
	// constexpr size_type rfind(const charT* s, size_type pos = npos) const;
	{
		string const s = Helper::aababc();
		auto p1 = Helper::ab();
		auto p2 = Helper::abc();
		auto p3 = Helper::abcd();
		//static_assert(noexcept(s.rfind(p1)), "");
		//static_assert(noexcept(s.rfind(p1, SizeType{})), "");
		//static_assert(noexcept(s.rfind(p1, SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.rfind(p1)), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s.rfind(p1, SizeType{})), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s.rfind(p1, SizeType{}, SizeType{})), SizeType>::value, "");

		VERIFY(s.rfind(p1) == 3);
		VERIFY(s.rfind(p2) == 3);
		VERIFY(s.rfind(p3) == string::npos);

		VERIFY(s.rfind(p1, 0) == string::npos);
		VERIFY(s.rfind(p1, 1) == 1);
		VERIFY(s.rfind(p1, 2) == 1);
		VERIFY(s.rfind(p1, 3) == 3);
		VERIFY(s.rfind(p1, 4) == 3);

		VERIFY(s.rfind(p3, string::npos, 0) == 6);
		VERIFY(s.rfind(p3, string::npos, 1) == 3);
		VERIFY(s.rfind(p3, string::npos, 2) == 3);
		VERIFY(s.rfind(p3, string::npos, 3) == 3);
		VERIFY(s.rfind(p3, string::npos, 4) == string::npos);
	}

	// constexpr size_type rfind(charT c, size_type pos = npos) const noexcept;
	{
		string const s = Helper::aababc();
		auto c1 = Helper::abcd()[0];
		auto c2 = Helper::abcd()[1];
		auto c3 = Helper::abcd()[2];
		auto c4 = Helper::abcd()[3];
		static_assert(noexcept(s.rfind(c1)), "");
		static_assert(noexcept(s.rfind(c1, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.rfind(c1)), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s.rfind(c1, SizeType{})), SizeType>::value, "");

		VERIFY(s.rfind(c1) == 3);
		VERIFY(s.rfind(c2) == 4);
		VERIFY(s.rfind(c3) == 5);
		VERIFY(s.rfind(c4) == string::npos);

		VERIFY(s.rfind(c2, 0) == string::npos);
		VERIFY(s.rfind(c2, 1) == string::npos);
		VERIFY(s.rfind(c2, 2) == 2);
		VERIFY(s.rfind(c2, 3) == 2);
		VERIFY(s.rfind(c2, 4) == 4);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, RFindTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(RFindTest<TypeParam>());
}

}	// namespace rfind_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
