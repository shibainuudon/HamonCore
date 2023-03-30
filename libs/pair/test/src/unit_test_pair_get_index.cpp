/**
 *	@file	unit_test_pair_get_index.cpp
 *
 *	@brief	get<I> のテスト
 *
 *	template<size_t I, class T1, class T2>
 *	constexpr tuple_element_t<I, pair<T1, T2>>&
 *	get(pair<T1, T2>& p) noexcept;
 *
 *	template<size_t I, class T1, class T2>
 *	constexpr const tuple_element_t<I, pair<T1, T2>>&
 *	get(const pair<T1, T2>& p) noexcept;
 *
 *	template<size_t I, class T1, class T2>
 *	constexpr tuple_element_t<I, pair<T1, T2>>&&
 *	get(pair<T1, T2>&& p) noexcept;
 *
 *	template<size_t I, class T1, class T2>
 *	constexpr const tuple_element_t<I, pair<T1, T2>>&&
 *	get(const pair<T1, T2>&& p) noexcept;
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace get_index_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	using std::get;
	{
		hamon::pair<float, int> p(1, 2);
		auto&& f = get<0>(p);
		static_assert(hamon::is_same<decltype(f), float&>::value, "");
		VERIFY(f == 1);
		auto&& i = get<1>(p);
		static_assert(hamon::is_same<decltype(i), int&>::value, "");
		VERIFY(i == 2);
	}
	{
		hamon::pair<float, int> p(1, 2);
		auto&& f = get<0>(hamon::move(p));
		static_assert(hamon::is_same<decltype(f), float&&>::value, "");
		VERIFY(f == 1);
		auto&& i = get<1>(hamon::move(p));
		static_assert(hamon::is_same<decltype(i), int&&>::value, "");
		VERIFY(i == 2);
	}
	{
		hamon::pair<float, int> const p(1, 2);
		auto&& f = get<0>(p);
		static_assert(hamon::is_same<decltype(f), float const&>::value, "");
		VERIFY(f == 1);
		auto&& i = get<1>(p);
		static_assert(hamon::is_same<decltype(i), int const&>::value, "");
		VERIFY(i == 2);
	}
	{
		hamon::pair<float, int> const p(1, 2);
		auto&& f = get<0>(hamon::move(p));
		static_assert(hamon::is_same<decltype(f), float const&&>::value, "");
		VERIFY(f == 1);
		auto&& i = get<1>(hamon::move(p));
		static_assert(hamon::is_same<decltype(i), int const&&>::value, "");
		VERIFY(i == 2);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, GetIndexTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace get_index_test

}	// namespace hamon_pair_test
