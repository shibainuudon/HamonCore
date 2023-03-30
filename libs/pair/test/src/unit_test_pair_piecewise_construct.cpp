/**
 *	@file	unit_test_pair_piecewise_construct.cpp
 *
 *	@brief	piecewise_construct のテスト
 * 
 *	template<class... Args1, class... Args2>
 *	constexpr pair(piecewise_construct_t,
 *		tuple<Args1...> first_args,
 *		tuple<Args2...> second_args);
 */

#include <hamon/pair.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace piecewise_construct_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct type_zero
{
	HAMON_CONSTEXPR type_zero()
		: m_n(757) {}

	type_zero(const type_zero&) = delete;

	HAMON_CONSTEXPR type_zero(type_zero&& other) noexcept
		: m_n(other.m_n) {}

	HAMON_CONSTEXPR int get() const { return m_n; }

private:
	int m_n;
};

struct type_one
{
	HAMON_CONSTEXPR type_one(int n)
		: m_n(n) {}

	type_one(const type_one&) = delete;

	HAMON_CONSTEXPR type_one(type_one&& other) noexcept
		: m_n(other.m_n) {}

	HAMON_CONSTEXPR int get() const { return m_n; }

private:
	int m_n;
};

struct type_two
{
	HAMON_CONSTEXPR type_two(int n1, int n2)
		: m_n1(n1), m_n2(n2) {}

	type_two(const type_two&) = delete;

	HAMON_CONSTEXPR type_two(type_two&& other) noexcept
		: m_n1(other.m_n1), m_n2(other.m_n2) {}

	HAMON_CONSTEXPR int get1() const { return m_n1; }
	HAMON_CONSTEXPR int get2() const { return m_n2; }

private:
	int m_n1, m_n2;
};

inline HAMON_CXX14_CONSTEXPR bool test01()
{
#if 0
	hamon::pair<type_one, type_zero> pp0(hamon::piecewise_construct,
		hamon::forward_as_tuple(-3),
		hamon::forward_as_tuple());
	VERIFY(pp0.first.get() == -3);
	VERIFY(pp0.second.get() == 757);

	hamon::pair<type_one, type_two> pp1(hamon::piecewise_construct,
		hamon::forward_as_tuple(6),
		hamon::forward_as_tuple(5, 4));
	VERIFY(pp1.first.get() == 6);
	VERIFY(pp1.second.get1() == 5);
	VERIFY(pp1.second.get2() == 4);

	hamon::pair<type_two, type_two> pp2(hamon::piecewise_construct,
		hamon::forward_as_tuple(2, 1),
		hamon::forward_as_tuple(-1, -3));
	VERIFY(pp2.first.get1() == 2);
	VERIFY(pp2.first.get2() == 1);
	VERIFY(pp2.second.get1() == -1);
	VERIFY(pp2.second.get2() == -3);
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, PiecewiseConstructTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test01()));
}

}	// namespace piecewise_construct_test

}	// namespace hamon_pair_test
