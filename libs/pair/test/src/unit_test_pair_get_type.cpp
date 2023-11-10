/**
 *	@file	unit_test_pair_get_type.cpp
 *
 *	@brief	get<T> のテスト
 *
 *	template<class T1, class T2>
 *	constexpr T1& get(pair<T1, T2>& p) noexcept;
 *
 *	template<class T1, class T2>
 *	constexpr const T1& get(const pair<T1, T2>& p) noexcept;
 *
 *	template<class T1, class T2>
 *	constexpr T1&& get(pair<T1, T2>&& p) noexcept;
 *
 *	template<class T1, class T2>
 *	constexpr const T1&& get(const pair<T1, T2>&& p) noexcept;
 *	
 *	template<class T2, class T1>
 *	constexpr T2& get(pair<T1, T2>& p) noexcept;
 *
 *	template<class T2, class T1>
 *	constexpr const T2& get(const pair<T1, T2>& p) noexcept;
 *
 *	template<class T2, class T1>
 *	constexpr T2&& get(pair<T1, T2>&& p) noexcept;
 *
 *	template<class T2, class T1>
 *	constexpr const T2&& get(const pair<T1, T2>&& p) noexcept;
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace get_type_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	using std::get;
	{
		hamon::pair<float, int> p(1.0f, 2);
		auto&& f = get<float>(p);
		static_assert(hamon::is_same<decltype(f), float&>::value, "");
		VERIFY(f == 1);
		auto&& i = get<int>(p);
		static_assert(hamon::is_same<decltype(i), int&>::value, "");
		VERIFY(i == 2);
	}
	{
		hamon::pair<float, int> p(1.0f, 2);
		auto&& f = get<float>(hamon::move(p));
		static_assert(hamon::is_same<decltype(f), float&&>::value, "");
		VERIFY(f == 1);
		auto&& i = get<int>(hamon::move(p));
		static_assert(hamon::is_same<decltype(i), int&&>::value, "");
		VERIFY(i == 2);
	}
	{
		hamon::pair<float, int> const p(1.0f, 2);
		auto&& f = get<float>(p);
		static_assert(hamon::is_same<decltype(f), float const&>::value, "");
		VERIFY(f == 1);
		auto&& i = get<int>(p);
		static_assert(hamon::is_same<decltype(i), int const&>::value, "");
		VERIFY(i == 2);
	}
	{
		hamon::pair<float, int> const p(1.0f, 2);
		auto&& f = get<float>(hamon::move(p));
		static_assert(hamon::is_same<decltype(f), float const&&>::value, "");
		VERIFY(f == 1);
		auto&& i = get<int>(hamon::move(p));
		static_assert(hamon::is_same<decltype(i), int const&&>::value, "");
		VERIFY(i == 2);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, GetTypeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace get_type_test

}	// namespace hamon_pair_test
