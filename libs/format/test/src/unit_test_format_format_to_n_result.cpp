/**
 *	@file	unit_test_format_format_to_n_result.cpp
 *
 *	@brief	format_to_n_result のテスト
 *
 *	template<class Out> struct format_to_n_result {
 *		Out out;
 *		iter_difference_t<Out> size;
 *	};
 */

#include <hamon/format/format_to_n_result.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_format_test
{

namespace format_to_n_result_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <class CharT>
constexpr bool test()
{
	hamon::format_to_n_result<CharT*> v{ nullptr, hamon::iter_difference_t<CharT*>{42} };

	auto [out, size] = v;
	static_assert(hamon::same_as<decltype(out), CharT*>);
	VERIFY(out == v.out);
	static_assert(hamon::same_as<decltype(size), hamon::iter_difference_t<CharT*>>);
	VERIFY(size == v.size);

	return true;
}

#undef VERIFY

GTEST_TEST(FormatTest, FormatToNResultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<wchar_t>());
}

}	// namespace format_to_n_result_test

}	// namespace hamon_format_test
