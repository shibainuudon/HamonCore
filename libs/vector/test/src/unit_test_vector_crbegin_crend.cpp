/**
 *	@file	unit_test_vector_crbegin_crend.cpp
 *
 *	@brief	crbegin, crend のテスト
 *
 *	constexpr const_reverse_iterator crbegin() const noexcept;
 *	constexpr const_reverse_iterator crend() const noexcept;
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace crbegin_crend_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Vector = hamon::vector<T>;
	using ConstReverseIterator = typename Vector::const_reverse_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().crbegin()),
		ConstReverseIterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector const&>().crbegin()),
		ConstReverseIterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().crend()),
		ConstReverseIterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector const&>().crend()),
		ConstReverseIterator
	>::value, "");

	static_assert(noexcept(
		hamon::declval<Vector&>().crbegin()), "");
	static_assert(noexcept(
		hamon::declval<Vector const&>().crbegin()), "");
	static_assert(noexcept(
		hamon::declval<Vector&>().crend()), "");
	static_assert(noexcept(
		hamon::declval<Vector const&>().crend()), "");

	{
		Vector v;
		auto it = v.crbegin();
		VERIFY(it == v.crbegin());
		VERIFY(it == v.crend());
	}
	{
		Vector const v;
		auto it = v.crbegin();
		VERIFY(it == v.crbegin());
		VERIFY(it == v.crend());
	}
	{
		Vector v{1,2,3};
		auto it = v.crbegin();
		VERIFY(it == v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it == v.crend());
	}
	{
		Vector const v{11,12,13,14};
		auto it = v.crbegin();
		VERIFY(it == v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 14);
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 13);
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 12);
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 11);
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it == v.crend());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, CRBeginCREndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace crbegin_crend_test

}	// namespace hamon_vector_test
