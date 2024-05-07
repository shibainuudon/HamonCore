/**
 *	@file	unit_test_vector_begin_end.cpp
 *
 *	@brief	begin, end のテスト
 *
 *	constexpr iterator               begin() noexcept;
 *	constexpr const_iterator         begin() const noexcept;
 *	constexpr iterator               end() noexcept;
 *	constexpr const_iterator         end() const noexcept;
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace begin_end_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Vector = hamon::vector<T>;
	using Iterator = typename Vector::iterator;
	using ConstIterator = typename Vector::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().begin()),
		Iterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector const&>().begin()),
		ConstIterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().end()),
		Iterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector const&>().end()),
		ConstIterator
	>::value, "");

	static_assert(noexcept(
		hamon::declval<Vector&>().begin()), "");
	static_assert(noexcept(
		hamon::declval<Vector const&>().begin()), "");
	static_assert(noexcept(
		hamon::declval<Vector&>().end()), "");
	static_assert(noexcept(
		hamon::declval<Vector const&>().end()), "");

	{
		Vector v;
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
	}
	{
		Vector const v;
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
	}
	{
		Vector v{1,2,3};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
	}
	{
		Vector const v{11,12,13,14};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 11);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 12);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 13);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 14);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, BeginEndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace begin_end_test

}	// namespace hamon_vector_test
