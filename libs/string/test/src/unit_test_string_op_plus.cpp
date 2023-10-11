/**
 *	@file	unit_test_string_op_plus.cpp
 *
 *	@brief	operator+ のテスト
 *
 *	template<class charT, class traits, class Allocator>
 *	constexpr basic_string<charT, traits, Allocator>
 *	operator+(
 *		const basic_string<charT, traits, Allocator>& lhs,
 *		const basic_string<charT, traits, Allocator>& rhs);
 *
 *	template<class charT, class traits, class Allocator>
 *	constexpr basic_string<charT, traits, Allocator>
 *	operator+(
 *		basic_string<charT, traits, Allocator>&& lhs,
 *		const basic_string<charT, traits, Allocator>& rhs);
 *	
 *	template<class charT, class traits, class Allocator>
 *	constexpr basic_string<charT, traits, Allocator>
 *	operator+(
 *		const basic_string<charT, traits, Allocator>& lhs,
 *		basic_string<charT, traits, Allocator>&& rhs);
 *	
 *	template<class charT, class traits, class Allocator>
 *	constexpr basic_string<charT, traits, Allocator>
 *	operator+(
 *		basic_string<charT, traits, Allocator>&& lhs,
 *		basic_string<charT, traits, Allocator>&& rhs);
 *	
 *	template<class charT, class traits, class Allocator>
 *	constexpr basic_string<charT, traits, Allocator>
 *	operator+(
 *		const charT* lhs,
 *		const basic_string<charT, traits, Allocator>& rhs);
 *	
 *	template<class charT, class traits, class Allocator>
 *	constexpr basic_string<charT, traits, Allocator>
 *	operator+(
 *		const charT* lhs,
 *		basic_string<charT, traits, Allocator>&& rhs);
 *	
 *	template<class charT, class traits, class Allocator>
 *	constexpr basic_string<charT, traits, Allocator>
 *	operator+(
 *		charT lhs,
 *		const basic_string<charT, traits, Allocator>& rhs);
 *	
 *	template<class charT, class traits, class Allocator>
 *	constexpr basic_string<charT, traits, Allocator>
 *	operator+(
 *		charT lhs,
 *		basic_string<charT, traits, Allocator>&& rhs);
 *	
 *	template<class charT, class traits, class Allocator>
 *	constexpr basic_string<charT, traits, Allocator>
 *	operator+(
 *		const basic_string<charT, traits, Allocator>& lhs,
 *		const charT* rhs);
 *	
 *	template<class charT, class traits, class Allocator>
 *	constexpr basic_string<charT, traits, Allocator>
 *	operator+(
 *		basic_string<charT, traits, Allocator>&& lhs,
 *		const charT* rhs);
 *	
 *	template<class charT, class traits, class Allocator>
 *	constexpr basic_string<charT, traits, Allocator>
 *	operator+(
 *		const basic_string<charT, traits, Allocator>& lhs,
 *		charT rhs);
 *	
 *	template<class charT, class traits, class Allocator>
 *	constexpr basic_string<charT, traits, Allocator>
 *	operator+(
 *		basic_string<charT, traits, Allocator>&& lhs,
 *		charT rhs);
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
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
namespace op_plus_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
OpPlusTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// template<class charT, class traits, class Allocator>
	// constexpr basic_string<charT, traits, Allocator>
	// operator+(
	// 	const basic_string<charT, traits, Allocator>& lhs,
	// 	const basic_string<charT, traits, Allocator>& rhs);
	{
		string const lhs = Helper::abc();
		string const rhs = Helper::edcba();
		static_assert(!noexcept(lhs + rhs), "");
		static_assert(hamon::is_same<decltype(lhs + rhs), string>::value, "");
		auto r = lhs + rhs;
		VERIFY(r.size() == 8);
		VERIFY(r[0] == Helper::abc()[0]);
		VERIFY(r[1] == Helper::abc()[1]);
		VERIFY(r[2] == Helper::abc()[2]);
		VERIFY(r[3] == Helper::edcba()[0]);
		VERIFY(r[4] == Helper::edcba()[1]);
		VERIFY(r[5] == Helper::edcba()[2]);
		VERIFY(r[6] == Helper::edcba()[3]);
		VERIFY(r[7] == Helper::edcba()[4]);
		VERIFY(r[8] == CharT{});
	}

	// template<class charT, class traits, class Allocator>
	// constexpr basic_string<charT, traits, Allocator>
	// operator+(
	// 	basic_string<charT, traits, Allocator>&& lhs,
	// 	const basic_string<charT, traits, Allocator>& rhs);
	{
		string lhs = Helper::abc();
		string const rhs = Helper::edcba();
		static_assert(!noexcept(hamon::move(lhs) + rhs), "");
		static_assert(hamon::is_same<decltype(hamon::move(lhs) + rhs), string>::value, "");
		auto r = hamon::move(lhs) + rhs;
		VERIFY(r.size() == 8);
		VERIFY(r[0] == Helper::abc()[0]);
		VERIFY(r[1] == Helper::abc()[1]);
		VERIFY(r[2] == Helper::abc()[2]);
		VERIFY(r[3] == Helper::edcba()[0]);
		VERIFY(r[4] == Helper::edcba()[1]);
		VERIFY(r[5] == Helper::edcba()[2]);
		VERIFY(r[6] == Helper::edcba()[3]);
		VERIFY(r[7] == Helper::edcba()[4]);
		VERIFY(r[8] == CharT{});
	}

	// template<class charT, class traits, class Allocator>
	// constexpr basic_string<charT, traits, Allocator>
	// operator+(
	// 	const basic_string<charT, traits, Allocator>& lhs,
	// 	basic_string<charT, traits, Allocator>&& rhs);
	{
		string const lhs = Helper::abc();
		string rhs = Helper::edcba();
		static_assert(!noexcept(lhs + hamon::move(rhs)), "");
		static_assert(hamon::is_same<decltype(lhs + hamon::move(rhs)), string>::value, "");
		auto r = lhs + hamon::move(rhs);
		VERIFY(r.size() == 8);
		VERIFY(r[0] == Helper::abc()[0]);
		VERIFY(r[1] == Helper::abc()[1]);
		VERIFY(r[2] == Helper::abc()[2]);
		VERIFY(r[3] == Helper::edcba()[0]);
		VERIFY(r[4] == Helper::edcba()[1]);
		VERIFY(r[5] == Helper::edcba()[2]);
		VERIFY(r[6] == Helper::edcba()[3]);
		VERIFY(r[7] == Helper::edcba()[4]);
		VERIFY(r[8] == CharT{});
	}

	// template<class charT, class traits, class Allocator>
	// constexpr basic_string<charT, traits, Allocator>
	// operator+(
	// 	basic_string<charT, traits, Allocator>&& lhs,
	// 	basic_string<charT, traits, Allocator>&& rhs);
	{
		string lhs = Helper::abc();
		string rhs = Helper::edcba();
		static_assert(!noexcept(hamon::move(lhs) + hamon::move(rhs)), "");
		static_assert(hamon::is_same<decltype(hamon::move(lhs) + hamon::move(rhs)), string>::value, "");
		auto r = hamon::move(lhs) + hamon::move(rhs);
		VERIFY(r.size() == 8);
		VERIFY(r[0] == Helper::abc()[0]);
		VERIFY(r[1] == Helper::abc()[1]);
		VERIFY(r[2] == Helper::abc()[2]);
		VERIFY(r[3] == Helper::edcba()[0]);
		VERIFY(r[4] == Helper::edcba()[1]);
		VERIFY(r[5] == Helper::edcba()[2]);
		VERIFY(r[6] == Helper::edcba()[3]);
		VERIFY(r[7] == Helper::edcba()[4]);
		VERIFY(r[8] == CharT{});
	}

	// template<class charT, class traits, class Allocator>
	// constexpr basic_string<charT, traits, Allocator>
	// operator+(
	// 	const charT* lhs,
	// 	const basic_string<charT, traits, Allocator>& rhs);
	{
		const CharT* lhs = Helper::bcd();
		string const rhs = Helper::ab();
		static_assert(!noexcept(lhs + rhs), "");
		static_assert(hamon::is_same<decltype(lhs + rhs), string>::value, "");
		auto r = lhs + rhs;
		VERIFY(r.size() == 5);
		VERIFY(r[0] == Helper::bcd()[0]);
		VERIFY(r[1] == Helper::bcd()[1]);
		VERIFY(r[2] == Helper::bcd()[2]);
		VERIFY(r[3] == Helper::ab()[0]);
		VERIFY(r[4] == Helper::ab()[1]);
		VERIFY(r[5] == CharT{});
	}

	// template<class charT, class traits, class Allocator>
	// constexpr basic_string<charT, traits, Allocator>
	// operator+(
	// 	const charT* lhs,
	// 	basic_string<charT, traits, Allocator>&& rhs);
	{
		const CharT* lhs = Helper::bcd();
		string rhs = Helper::ab();
		static_assert(!noexcept(lhs + hamon::move(rhs)), "");
		static_assert(hamon::is_same<decltype(lhs + hamon::move(rhs)), string>::value, "");
		auto r = lhs + hamon::move(rhs);
		VERIFY(r.size() == 5);
		VERIFY(r[0] == Helper::bcd()[0]);
		VERIFY(r[1] == Helper::bcd()[1]);
		VERIFY(r[2] == Helper::bcd()[2]);
		VERIFY(r[3] == Helper::ab()[0]);
		VERIFY(r[4] == Helper::ab()[1]);
		VERIFY(r[5] == CharT{});
	}

	// template<class charT, class traits, class Allocator>
	// constexpr basic_string<charT, traits, Allocator>
	// operator+(
	// 	charT lhs,
	// 	const basic_string<charT, traits, Allocator>& rhs);
	{
		const CharT lhs = Helper::bcd()[1];
		string const rhs = Helper::ab();
		static_assert(!noexcept(lhs + rhs), "");
		static_assert(hamon::is_same<decltype(lhs + rhs), string>::value, "");
		auto r = lhs + rhs;
		VERIFY(r.size() == 3);
		VERIFY(r[0] == Helper::bcd()[1]);
		VERIFY(r[1] == Helper::ab()[0]);
		VERIFY(r[2] == Helper::ab()[1]);
		VERIFY(r[3] == CharT{});
	}

	// template<class charT, class traits, class Allocator>
	// constexpr basic_string<charT, traits, Allocator>
	// operator+(
	// 	charT lhs,
	// 	basic_string<charT, traits, Allocator>&& rhs);
	{
		const CharT lhs = Helper::bcd()[1];
		string rhs = Helper::ab();
		static_assert(!noexcept(lhs + hamon::move(rhs)), "");
		static_assert(hamon::is_same<decltype(lhs + hamon::move(rhs)), string>::value, "");
		auto r = lhs + hamon::move(rhs);
		VERIFY(r.size() == 3);
		VERIFY(r[0] == Helper::bcd()[1]);
		VERIFY(r[1] == Helper::ab()[0]);
		VERIFY(r[2] == Helper::ab()[1]);
		VERIFY(r[3] == CharT{});
	}

	// template<class charT, class traits, class Allocator>
	// constexpr basic_string<charT, traits, Allocator>
	// operator+(
	// 	const basic_string<charT, traits, Allocator>& lhs,
	// 	const charT* rhs);
	{
		string const lhs = Helper::bcd();
		const CharT* rhs = Helper::ab();
		static_assert(!noexcept(lhs + rhs), "");
		static_assert(hamon::is_same<decltype(lhs + rhs), string>::value, "");
		auto r = lhs + rhs;
		VERIFY(r.size() == 5);
		VERIFY(r[0] == Helper::bcd()[0]);
		VERIFY(r[1] == Helper::bcd()[1]);
		VERIFY(r[2] == Helper::bcd()[2]);
		VERIFY(r[3] == Helper::ab()[0]);
		VERIFY(r[4] == Helper::ab()[1]);
		VERIFY(r[5] == CharT{});
	}

	// template<class charT, class traits, class Allocator>
	// constexpr basic_string<charT, traits, Allocator>
	// operator+(
	// 	basic_string<charT, traits, Allocator>&& lhs,
	// 	const charT* rhs);
	{
		string lhs = Helper::bcd();
		const CharT* rhs = Helper::ab();
		static_assert(!noexcept(hamon::move(lhs) + rhs), "");
		static_assert(hamon::is_same<decltype(hamon::move(lhs) + rhs), string>::value, "");
		auto r = hamon::move(lhs) + rhs;
		VERIFY(r.size() == 5);
		VERIFY(r[0] == Helper::bcd()[0]);
		VERIFY(r[1] == Helper::bcd()[1]);
		VERIFY(r[2] == Helper::bcd()[2]);
		VERIFY(r[3] == Helper::ab()[0]);
		VERIFY(r[4] == Helper::ab()[1]);
		VERIFY(r[5] == CharT{});
	}

	// template<class charT, class traits, class Allocator>
	// constexpr basic_string<charT, traits, Allocator>
	// operator+(
	// 	const basic_string<charT, traits, Allocator>& lhs,
	// 	charT rhs);
	{
		string const lhs = Helper::abc();
		const CharT rhs = Helper::bcd()[2];
		static_assert(!noexcept(lhs + rhs), "");
		static_assert(hamon::is_same<decltype(lhs + rhs), string>::value, "");
		auto r = lhs + rhs;
		VERIFY(r.size() == 4);
		VERIFY(r[0] == Helper::abc()[0]);
		VERIFY(r[1] == Helper::abc()[1]);
		VERIFY(r[2] == Helper::abc()[2]);
		VERIFY(r[3] == Helper::bcd()[2]);
		VERIFY(r[4] == CharT{});
	}

	// template<class charT, class traits, class Allocator>
	// constexpr basic_string<charT, traits, Allocator>
	// operator+(
	// 	basic_string<charT, traits, Allocator>&& lhs,
	// 	charT rhs);
	{
		string lhs = Helper::abc();
		const CharT rhs = Helper::bcd()[2];
		static_assert(!noexcept(hamon::move(lhs) + rhs), "");
		static_assert(hamon::is_same<decltype(hamon::move(lhs) + rhs), string>::value, "");
		auto r = hamon::move(lhs) + rhs;
		VERIFY(r.size() == 4);
		VERIFY(r[0] == Helper::abc()[0]);
		VERIFY(r[1] == Helper::abc()[1]);
		VERIFY(r[2] == Helper::abc()[2]);
		VERIFY(r[3] == Helper::bcd()[2]);
		VERIFY(r[4] == CharT{});
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, OpPlusTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(OpPlusTest<TypeParam>());
}

}	// namespace op_plus_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
