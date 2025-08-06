/**
 *	@file	unit_test_hive_reserve.cpp
 *
 *	@brief	reserve のテスト
 *
 *	void reserve(size_type n);
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/stdexcept/length_error.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace reserve_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using SizeType = typename Hive::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().reserve(hamon::declval<SizeType>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Hive>().reserve(hamon::declval<SizeType>())), "");

	Hive v;

	v.reserve(50);
	VERIFY(v.capacity() >= 50u);
	VERIFY(v.size() == 0u);

	v.reserve(10);
	VERIFY(v.capacity() >= 50u);
	VERIFY(v.size() == 0u);

	v.insert(30, T{42});
	auto first = v.begin();
	auto last = v.end();

	v.reserve(200);
	VERIFY(v.capacity() >= 200u);
	VERIFY(v.size() == 30u);

	// [hive.capacity]/7
	// Remarks: All references, pointers, and iterators referring to elements in *this,
	// as well as the past-the-end iterator, remain valid.
	VERIFY(hamon::accumulate(first, last, T{}, hamon::plus<T>{}) == T{1260});

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, ReserveTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<short>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::hive<int> v;
		EXPECT_THROW(v.reserve(v.max_size() + 1), hamon::length_error);
		EXPECT_EQ(0u, v.capacity());
	}
#endif
}

}	// namespace reserve_test

}	// namespace hamon_hive_test
