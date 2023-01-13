/**
 *	@file	unit_test_string_view_iterator.cpp
 *
 *	@brief
 */

#include <hamon/string_view/basic_string_view.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "string_view_test_helper.hpp"

namespace hamon_test
{
namespace string_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX14_CONSTEXPR bool BeginEndTest()
{
	using string_view = hamon::basic_string_view<CharT>;
	using iterator = typename string_view::iterator;

	{
		const auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str, 7};
		const iterator first = sv.begin();
		const iterator last = sv.end();
		iterator it = first;
		VERIFY(*it == str[0]);
		VERIFY(it != last);
		++it;
		VERIFY(*it == str[1]);
		VERIFY(it != last);
		it++;
		VERIFY(*it == str[2]);
		VERIFY(it != last);
		it += 4;
		VERIFY(*it == str[6]);
		VERIFY(it != last);
		it--;
		VERIFY(*it == str[5]);
		VERIFY(it != last);
		--it;
		VERIFY(*it == str[4]);
		VERIFY(it != last);
		it -= 1;
		VERIFY(*it == str[3]);
		VERIFY(it != last);
		it += 4;
		VERIFY(it == last);

		VERIFY(str[0] == first[0]);
		VERIFY(str[1] == first[1]);
		VERIFY(str[2] == first[2]);
		VERIFY(str[3] == first[3]);
		VERIFY(str[4] == first[4]);
		VERIFY(str[5] == first[5]);
		VERIFY(str[6] == first[6]);
	}
	return true;
}

template <typename CharT>
inline HAMON_CXX14_CONSTEXPR bool CBeginCEndTest()
{
	using string_view = hamon::basic_string_view<CharT>;
	using const_iterator = typename string_view::const_iterator;

	{
		const auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str, 7};
		const const_iterator first = sv.cbegin();
		const const_iterator last = sv.cend();
		const_iterator it = first;
		VERIFY(*it == str[0]);
		VERIFY(it != last);
		++it;
		VERIFY(*it == str[1]);
		VERIFY(it != last);
		it++;
		VERIFY(*it == str[2]);
		VERIFY(it != last);
		it += 4;
		VERIFY(*it == str[6]);
		VERIFY(it != last);
		it--;
		VERIFY(*it == str[5]);
		VERIFY(it != last);
		--it;
		VERIFY(*it == str[4]);
		VERIFY(it != last);
		it -= 1;
		VERIFY(*it == str[3]);
		VERIFY(it != last);
		it += 4;
		VERIFY(it == last);

		VERIFY(str[0] == first[0]);
		VERIFY(str[1] == first[1]);
		VERIFY(str[2] == first[2]);
		VERIFY(str[3] == first[3]);
		VERIFY(str[4] == first[4]);
		VERIFY(str[5] == first[5]);
		VERIFY(str[6] == first[6]);
	}
	return true;
}

template <typename CharT>
inline HAMON_CXX14_CONSTEXPR bool RBeginREndTest()
{
	using string_view = hamon::basic_string_view<CharT>;
	using reverse_iterator = typename string_view::reverse_iterator;

	{
		const auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str, 7};
		const reverse_iterator first = sv.rbegin();
		const reverse_iterator last = sv.rend();
		reverse_iterator it = first;
		VERIFY(*it == str[6]);
		VERIFY(it != last);
		++it;
		VERIFY(*it == str[5]);
		VERIFY(it != last);
		it++;
		VERIFY(*it == str[4]);
		VERIFY(it != last);
		it += 4;
		VERIFY(*it == str[0]);
		VERIFY(it != last);
		it--;
		VERIFY(*it == str[1]);
		VERIFY(it != last);
		--it;
		VERIFY(*it == str[2]);
		VERIFY(it != last);
		it -= 1;
		VERIFY(*it == str[3]);
		VERIFY(it != last);
		it += 4;
		VERIFY(it == last);

		VERIFY(str[6] == first[0]);
		VERIFY(str[5] == first[1]);
		VERIFY(str[4] == first[2]);
		VERIFY(str[3] == first[3]);
		VERIFY(str[2] == first[4]);
		VERIFY(str[1] == first[5]);
		VERIFY(str[0] == first[6]);
	}
	return true;
}

template <typename CharT>
inline HAMON_CXX14_CONSTEXPR bool CRBeginCREndTest()
{
	using string_view = hamon::basic_string_view<CharT>;
	using const_reverse_iterator = typename string_view::const_reverse_iterator;

	{
		const auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str, 7};
		const const_reverse_iterator first = sv.crbegin();
		const const_reverse_iterator last = sv.crend();
		const_reverse_iterator it = first;
		VERIFY(*it == str[6]);
		VERIFY(it != last);
		++it;
		VERIFY(*it == str[5]);
		VERIFY(it != last);
		it++;
		VERIFY(*it == str[4]);
		VERIFY(it != last);
		it += 4;
		VERIFY(*it == str[0]);
		VERIFY(it != last);
		it--;
		VERIFY(*it == str[1]);
		VERIFY(it != last);
		--it;
		VERIFY(*it == str[2]);
		VERIFY(it != last);
		it -= 1;
		VERIFY(*it == str[3]);
		VERIFY(it != last);
		it += 4;
		VERIFY(it == last);

		VERIFY(str[6] == first[0]);
		VERIFY(str[5] == first[1]);
		VERIFY(str[4] == first[2]);
		VERIFY(str[3] == first[3]);
		VERIFY(str[2] == first[4]);
		VERIFY(str[1] == first[5]);
		VERIFY(str[0] == first[6]);
	}
	return true;
}

TYPED_TEST(StringViewTest, IteratorTest)
{
	using CharT = TypeParam;
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BeginEndTest<CharT>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CBeginCEndTest<CharT>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RBeginREndTest<CharT>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CRBeginCREndTest<CharT>());
}

#undef VERIFY

}	// namespace string_view_test
}	// namespace hamon_test
