/**
 *	@file	unit_test_string_iterators.cpp
 *
 *	@brief	イテレータのテスト
 *
 *	constexpr iterator       begin() noexcept;
 *	constexpr const_iterator begin() const noexcept;
 *	constexpr iterator       end() noexcept;
 *	constexpr const_iterator end() const noexcept;
 *	
 *	constexpr reverse_iterator       rbegin() noexcept;
 *	constexpr const_reverse_iterator rbegin() const noexcept;
 *	constexpr reverse_iterator       rend() noexcept;
 *	constexpr const_reverse_iterator rend() const noexcept;
 *	
 *	constexpr const_iterator         cbegin() const noexcept;
 *	constexpr const_iterator         cend() const noexcept;
 *	constexpr const_reverse_iterator crbegin() const noexcept;
 *	constexpr const_reverse_iterator crend() const noexcept;
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
namespace iterators_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
IteratorsTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		string s = Helper::abcde();
		static_assert(noexcept(s.begin()), "");
		static_assert(noexcept(s.end()), "");
		static_assert(noexcept(s.rbegin()), "");
		static_assert(noexcept(s.rend()), "");
		static_assert(noexcept(s.cbegin()), "");
		static_assert(noexcept(s.cend()), "");
		static_assert(noexcept(s.crbegin()), "");
		static_assert(noexcept(s.crend()), "");

		{
			auto it = s.begin();
			static_assert(hamon::is_same<decltype(*it), CharT&>::value, "");
			VERIFY(*it == Helper::abcde()[0]);
			VERIFY(it != s.end());
			VERIFY(*++it == Helper::abcde()[1]);
			VERIFY(it != s.end());
			VERIFY(*it++ == Helper::abcde()[1]);
			VERIFY(it != s.end());
			VERIFY(*it == Helper::abcde()[2]);
			++it;
			VERIFY(*it == Helper::abcde()[3]);
			VERIFY(it != s.end());
			++it;
			VERIFY(*it == Helper::abcde()[4]);
			VERIFY(it != s.end());
			++it;
			VERIFY(it == s.end());
		}
		{
			auto it = s.rbegin();
			static_assert(hamon::is_same<decltype(*it), CharT&>::value, "");
			VERIFY(*it == Helper::abcde()[4]);
			VERIFY(it != s.rend());
			VERIFY(*++it == Helper::abcde()[3]);
			VERIFY(it != s.rend());
			VERIFY(*it++ == Helper::abcde()[3]);
			VERIFY(it != s.rend());
			VERIFY(*it == Helper::abcde()[2]);
			++it;
			VERIFY(*it == Helper::abcde()[1]);
			VERIFY(it != s.rend());
			++it;
			VERIFY(*it == Helper::abcde()[0]);
			VERIFY(it != s.rend());
			++it;
			VERIFY(it == s.rend());
		}
		{
			auto it = s.cbegin();
			static_assert(hamon::is_same<decltype(*it), CharT const&>::value, "");
			VERIFY(*it == Helper::abcde()[0]);
			VERIFY(it != s.cend());
			VERIFY(*++it == Helper::abcde()[1]);
			VERIFY(it != s.cend());
			VERIFY(*it++ == Helper::abcde()[1]);
			VERIFY(it != s.cend());
			VERIFY(*it == Helper::abcde()[2]);
			++it;
			VERIFY(*it == Helper::abcde()[3]);
			VERIFY(it != s.cend());
			++it;
			VERIFY(*it == Helper::abcde()[4]);
			VERIFY(it != s.cend());
			++it;
			VERIFY(it == s.cend());
		}
		{
			auto it = s.crbegin();
			static_assert(hamon::is_same<decltype(*it), CharT const&>::value, "");
			VERIFY(*it == Helper::abcde()[4]);
			VERIFY(it != s.crend());
			VERIFY(*++it == Helper::abcde()[3]);
			VERIFY(it != s.crend());
			VERIFY(*it++ == Helper::abcde()[3]);
			VERIFY(it != s.crend());
			VERIFY(*it == Helper::abcde()[2]);
			++it;
			VERIFY(*it == Helper::abcde()[1]);
			VERIFY(it != s.crend());
			++it;
			VERIFY(*it == Helper::abcde()[0]);
			VERIFY(it != s.crend());
			++it;
			VERIFY(it == s.crend());
		}
	}
	{
		string const s = Helper::abcde();
		static_assert(noexcept(s.begin()), "");
		static_assert(noexcept(s.end()), "");
		static_assert(noexcept(s.rbegin()), "");
		static_assert(noexcept(s.rend()), "");
		static_assert(noexcept(s.cbegin()), "");
		static_assert(noexcept(s.cend()), "");
		static_assert(noexcept(s.crbegin()), "");
		static_assert(noexcept(s.crend()), "");

		{
			auto it = s.begin();
			static_assert(hamon::is_same<decltype(*it), CharT const&>::value, "");
			VERIFY(*it == Helper::abcde()[0]);
			VERIFY(it != s.end());
			VERIFY(*++it == Helper::abcde()[1]);
			VERIFY(it != s.end());
			VERIFY(*it++ == Helper::abcde()[1]);
			VERIFY(it != s.end());
			VERIFY(*it == Helper::abcde()[2]);
			++it;
			VERIFY(*it == Helper::abcde()[3]);
			VERIFY(it != s.end());
			++it;
			VERIFY(*it == Helper::abcde()[4]);
			VERIFY(it != s.end());
			++it;
			VERIFY(it == s.end());
		}
		{
			auto it = s.rbegin();
			static_assert(hamon::is_same<decltype(*it), CharT const&>::value, "");
			VERIFY(*it == Helper::abcde()[4]);
			VERIFY(it != s.rend());
			VERIFY(*++it == Helper::abcde()[3]);
			VERIFY(it != s.rend());
			VERIFY(*it++ == Helper::abcde()[3]);
			VERIFY(it != s.rend());
			VERIFY(*it == Helper::abcde()[2]);
			++it;
			VERIFY(*it == Helper::abcde()[1]);
			VERIFY(it != s.rend());
			++it;
			VERIFY(*it == Helper::abcde()[0]);
			VERIFY(it != s.rend());
			++it;
			VERIFY(it == s.rend());
		}
		{
			auto it = s.cbegin();
			static_assert(hamon::is_same<decltype(*it), CharT const&>::value, "");
			VERIFY(*it == Helper::abcde()[0]);
			VERIFY(it != s.cend());
			VERIFY(*++it == Helper::abcde()[1]);
			VERIFY(it != s.cend());
			VERIFY(*it++ == Helper::abcde()[1]);
			VERIFY(it != s.cend());
			VERIFY(*it == Helper::abcde()[2]);
			++it;
			VERIFY(*it == Helper::abcde()[3]);
			VERIFY(it != s.cend());
			++it;
			VERIFY(*it == Helper::abcde()[4]);
			VERIFY(it != s.cend());
			++it;
			VERIFY(it == s.cend());
		}
		{
			auto it = s.crbegin();
			static_assert(hamon::is_same<decltype(*it), CharT const&>::value, "");
			VERIFY(*it == Helper::abcde()[4]);
			VERIFY(it != s.crend());
			VERIFY(*++it == Helper::abcde()[3]);
			VERIFY(it != s.crend());
			VERIFY(*it++ == Helper::abcde()[3]);
			VERIFY(it != s.crend());
			VERIFY(*it == Helper::abcde()[2]);
			++it;
			VERIFY(*it == Helper::abcde()[1]);
			VERIFY(it != s.crend());
			++it;
			VERIFY(*it == Helper::abcde()[0]);
			VERIFY(it != s.crend());
			++it;
			VERIFY(it == s.crend());
		}
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, IteratorsTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(IteratorsTest<TypeParam>());
}

}	// namespace iterators_test
}	// namespace string_test
}	// namespace hamon_test
