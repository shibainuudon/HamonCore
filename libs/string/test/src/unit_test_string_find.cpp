/**
 *	@file	unit_test_string_find.cpp
 *
 *	@brief	find のテスト
 *
 *	template<class T>
 *	constexpr size_type find(const T& t, size_type pos = 0) const noexcept(see below);
 *	constexpr size_type find(const basic_string& str, size_type pos = 0) const noexcept;
 *	constexpr size_type find(const charT* s, size_type pos, size_type n) const;
 *	constexpr size_type find(const charT* s, size_type pos = 0) const;
 *	constexpr size_type find(charT c, size_type pos = 0) const noexcept;
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
namespace find_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
FindTest()
{
	using string = hamon::basic_string<CharT>;
	using SizeType = typename string::size_type;
	using Helper = StringTestHelper<CharT>;

#if HAMON_CXX_STANDARD >= 17	// TODO
	using string_view = std::basic_string_view<CharT>;

	// template<class T>
	// constexpr size_type find(const T& t, size_type pos = 0) const noexcept(see below);
	{
		string const s1 = Helper::aababc();
		string_view const s2 = Helper::ab();
		string_view const s3 = Helper::abc();
		string_view const s4 = Helper::abcd();
		// TODO
		//static_assert(!noexcept(s1.find(s2)), "");
		//static_assert(!noexcept(s1.find(s2, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s1.find(s2)), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s1.find(s2, SizeType{})), SizeType>::value, "");

		VERIFY(s1.find(s2) == 1);
		VERIFY(s1.find(s3) == 3);
		VERIFY(s1.find(s4) == string::npos);

		VERIFY(s1.find(s2, 1) == 1);
		VERIFY(s1.find(s2, 2) == 3);
		VERIFY(s1.find(s2, 3) == 3);
		VERIFY(s1.find(s2, 4) == string::npos);
	}
#endif

	// constexpr size_type find(const basic_string& str, size_type pos = 0) const noexcept;
	{
		string const s1 = Helper::aababc();
		string const s2 = Helper::ab();
		string const s3 = Helper::abc();
		string const s4 = Helper::abcd();
		static_assert(noexcept(s1.find(s2)), "");
		static_assert(noexcept(s1.find(s2, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s1.find(s2)), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s1.find(s2, SizeType{})), SizeType>::value, "");

		VERIFY(s1.find(s2) == 1);
		VERIFY(s1.find(s3) == 3);
		VERIFY(s1.find(s4) == string::npos);

		VERIFY(s1.find(s2, 1) == 1);
		VERIFY(s1.find(s2, 2) == 3);
		VERIFY(s1.find(s2, 3) == 3);
		VERIFY(s1.find(s2, 4) == string::npos);
	}

	// constexpr size_type find(const charT* s, size_type pos, size_type n) const;
	// constexpr size_type find(const charT* s, size_type pos = 0) const;
	{
		string const s = Helper::aababc();
		auto p1 = Helper::ab();
		auto p2 = Helper::abc();
		auto p3 = Helper::abcd();
		static_assert(noexcept(s.find(p1)), "");
		static_assert(noexcept(s.find(p1, SizeType{})), "");
		static_assert(noexcept(s.find(p1, SizeType{}, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.find(p1)), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s.find(p1, SizeType{})), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s.find(p1, SizeType{}, SizeType{})), SizeType>::value, "");

		VERIFY(s.find(p1) == 1);
		VERIFY(s.find(p2) == 3);
		VERIFY(s.find(p3) == string::npos);

		VERIFY(s.find(p1, 1) == 1);
		VERIFY(s.find(p1, 2) == 3);
		VERIFY(s.find(p1, 3) == 3);
		VERIFY(s.find(p1, 4) == string::npos);

		VERIFY(s.find(p3, 1, 2) == 1);
		VERIFY(s.find(p3, 2, 2) == 3);
		VERIFY(s.find(p3, 3, 2) == 3);
		VERIFY(s.find(p3, 4, 2) == string::npos);
	}

	// constexpr size_type find(charT c, size_type pos = 0) const noexcept;
	{
		string const s = Helper::aababc();
		auto c1 = Helper::abcd()[0];
		auto c2 = Helper::abcd()[1];
		auto c3 = Helper::abcd()[2];
		auto c4 = Helper::abcd()[3];
		static_assert(noexcept(s.find(c1)), "");
		static_assert(noexcept(s.find(c1, SizeType{})), "");
		static_assert(hamon::is_same<decltype(s.find(c1)), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s.find(c1, SizeType{})), SizeType>::value, "");

		VERIFY(s.find(c1) == 0);
		VERIFY(s.find(c2) == 2);
		VERIFY(s.find(c3) == 5);
		VERIFY(s.find(c4) == string::npos);

		VERIFY(s.find(c1, 1) == 1);
		VERIFY(s.find(c1, 2) == 3);
		VERIFY(s.find(c1, 3) == 3);
		VERIFY(s.find(c1, 4) == string::npos);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, FindTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FindTest<TypeParam>());
}

}	// namespace find_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
