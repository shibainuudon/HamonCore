/**
 *	@file	unit_test_vector_rbegin_rend.cpp
 *
 *	@brief	rbegin, rend のテスト
 *
 *	constexpr reverse_iterator       rbegin() noexcept;
 *	constexpr const_reverse_iterator rbegin() const noexcept;
 *	constexpr reverse_iterator       rend() noexcept;
 *	constexpr const_reverse_iterator rend() const noexcept;
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace rbegin_rend_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Vector = hamon::vector<T>;
	using ReverseIterator = typename Vector::reverse_iterator;
	using ConstReverseIterator = typename Vector::const_reverse_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().rbegin()),
		ReverseIterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector const&>().rbegin()),
		ConstReverseIterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().rend()),
		ReverseIterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector const&>().rend()),
		ConstReverseIterator
	>::value, "");

	static_assert(noexcept(
		hamon::declval<Vector&>().rbegin()), "");
	static_assert(noexcept(
		hamon::declval<Vector const&>().rbegin()), "");
	static_assert(noexcept(
		hamon::declval<Vector&>().rend()), "");
	static_assert(noexcept(
		hamon::declval<Vector const&>().rend()), "");

	{
		Vector v;
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it == v.rend());
	}
	{
		Vector const v;
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it == v.rend());
	}
	{
		Vector v{1,2,3};
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it == v.rend());
	}
	{
		Vector const v{11,12,13,14};
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(*it == 14);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(*it == 13);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(*it == 12);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(*it == 11);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it == v.rend());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, RBeginREndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace rbegin_rend_test

}	// namespace hamon_vector_test
