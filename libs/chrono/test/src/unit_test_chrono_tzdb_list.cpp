/**
 *	@file	unit_test_chrono_tzdb_list.cpp
 *
 *	@brief	tzdb_list のテスト
 */

#include <hamon/chrono/tzdb_list.hpp>
#include <hamon/chrono/get_tzdb_list.hpp>
#include <hamon/concepts.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

static_assert(!hamon::copyable_t<hamon::chrono::tzdb_list>::value, "");
static_assert(!hamon::movable_t<hamon::chrono::tzdb_list>::value, "");
static_assert(!hamon::default_initializable_t<hamon::chrono::tzdb_list>::value, "");

GTEST_TEST(ChronoTest, TzdbListTest)
{
	hamon::chrono::tzdb_list& list = hamon::chrono::get_tzdb_list();
	using it = hamon::chrono::tzdb_list::const_iterator;

	// front
	static_assert(hamon::is_same<decltype(list.front()), hamon::chrono::tzdb const&>::value, "");
	static_assert(noexcept(list.front()), "");

	// erase_after
	static_assert(hamon::is_same<decltype(list.erase_after(it{})), it>::value, "");
	static_assert(!noexcept(list.erase_after(it{})), "");

	// begin
	static_assert(hamon::is_same<decltype(list.begin()), it>::value, "");
	static_assert(noexcept(list.begin()), "");

	// end
	static_assert(hamon::is_same<decltype(list.end()), it>::value, "");
	static_assert(noexcept(list.end()), "");

	// cbegin
	static_assert(hamon::is_same<decltype(list.cbegin()), it>::value, "");
	static_assert(noexcept(list.cbegin()), "");

	// cend
	static_assert(hamon::is_same<decltype(list.cend()), it>::value, "");
	static_assert(noexcept(list.cend()), "");

	auto begin = list.begin();
	auto end = list.end();
	EXPECT_TRUE(hamon::distance(begin, end) == 1);

	auto cbegin = list.cbegin();
	EXPECT_TRUE(begin == cbegin);

	auto cend = list.cend();
	EXPECT_TRUE(end == cend);
}

}	// namespace hamon_chrono_test
