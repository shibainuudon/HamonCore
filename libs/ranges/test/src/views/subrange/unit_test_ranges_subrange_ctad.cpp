/**
 *	@file	unit_test_ranges_subrange_ctad.cpp
 *
 *	@brief	ranges::subrange テンプレート引数推論のテスト
 */

#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/views/subrange_kind.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/iterator/unreachable_sentinel.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include <forward_list>
#include <vector>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace ctad_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

// Iterator, Sentinel
inline HAMON_CXX14_CONSTEXPR bool test01_1()
{
	{
		int a[] = {1, 2, 3};
		hamon::ranges::subrange sr(a, a+1);
		static_assert(std::is_same<decltype(sr), hamon::ranges::subrange<int*, int*, hamon::ranges::subrange_kind::sized>>::value, "");
		static_assert(hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin() == a);
		VERIFY(sr.end() == a+1);
		VERIFY(sr.size() == 1);
	}
	{
		using Iter = forward_iterator_wrapper<int>;
		using Sent = test_sentinel<Iter>;
		int a[] = {1, 2, 3};
		hamon::ranges::subrange sr(Iter{a}, Sent{a+2});
		static_assert(std::is_same<decltype(sr), hamon::ranges::subrange<Iter, Sent, hamon::ranges::subrange_kind::unsized>>::value, "");
		static_assert(!hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin().m_ptr == a);
		VERIFY(sr.end().m_it.m_ptr == a+2);
	}
	{
		using Iter = random_access_iterator_wrapper<int>;
		using Sent = test_sentinel<Iter>;
		int a[] = {1, 2, 3};
		hamon::ranges::subrange sr(Iter{a}, Sent{a+3});
		static_assert(std::is_same<decltype(sr), hamon::ranges::subrange<Iter, Sent, hamon::ranges::subrange_kind::sized>>::value, "");
		static_assert(hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin().m_ptr == a);
		VERIFY(sr.end().m_it.m_ptr == a+3);
		VERIFY(sr.size() == 3);
	}
	{
		int a[] = {1, 2, 3};
		hamon::ranges::subrange sr(a, hamon::unreachable_sentinel);
		static_assert(std::is_same<decltype(sr), hamon::ranges::subrange<int*, hamon::unreachable_sentinel_t, hamon::ranges::subrange_kind::unsized>>::value, "");
		static_assert(!hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin() == a);
		VERIFY(sr.end() != a+0);
		VERIFY(sr.end() != a+1);
		VERIFY(sr.end() != a+2);
	}
	return true;
}

inline bool test01_2()
{
	{
		const std::forward_list fwl = {1, 2, 3, 4};
		hamon::ranges::subrange sr(fwl.begin(), fwl.end());
		static_assert(!hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin() == fwl.begin());
		VERIFY(sr.end() == fwl.end());
	}
	{
		const std::vector vec = {1, 2, 3, 4, 5};
		hamon::ranges::subrange sr(vec.begin(), vec.end());
		static_assert(hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin() == vec.begin());
		VERIFY(sr.end() == vec.end());
		VERIFY(sr.size() == 5);
	}
	return true;
}

// Iterator, Sentinel, Size
inline HAMON_CXX14_CONSTEXPR bool test02_1()
{
	{
		int a[] = {1, 2, 3};
		hamon::ranges::subrange sr(a, a+1, 1);
		static_assert(std::is_same<decltype(sr), hamon::ranges::subrange<int*, int*, hamon::ranges::subrange_kind::sized>>::value, "");
		static_assert(hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin() == a);
		VERIFY(sr.end() == a+1);
		VERIFY(sr.size() == 1);
	}
	{
		using Iter = forward_iterator_wrapper<int>;
		using Sent = test_sentinel<Iter>;
		int a[] = {1, 2, 3};
		hamon::ranges::subrange sr(Iter{a}, Sent{a+2}, 2);
		static_assert(std::is_same<decltype(sr), hamon::ranges::subrange<Iter, Sent, hamon::ranges::subrange_kind::sized>>::value, "");
		static_assert(hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin().m_ptr == a);
		VERIFY(sr.end().m_it.m_ptr == a+2);
		VERIFY(sr.size() == 2);
	}
	{
		using Iter = random_access_iterator_wrapper<int>;
		using Sent = test_sentinel<Iter>;
		int a[] = {1, 2, 3};
		hamon::ranges::subrange sr(Iter{a}, Sent{a+3}, 3);
		static_assert(std::is_same<decltype(sr), hamon::ranges::subrange<Iter, Sent, hamon::ranges::subrange_kind::sized>>::value, "");
		static_assert(hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin().m_ptr == a);
		VERIFY(sr.end().m_it.m_ptr == a+3);
		VERIFY(sr.size() == 3);
	}
	{
		int a[] = {1, 2, 3};
		hamon::ranges::subrange sr(a, hamon::unreachable_sentinel, 3);
		static_assert(std::is_same<decltype(sr), hamon::ranges::subrange<int*, hamon::unreachable_sentinel_t, hamon::ranges::subrange_kind::sized>>::value, "");
		static_assert(hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin() == a);
		VERIFY(sr.end() != a+0);
		VERIFY(sr.end() != a+1);
		VERIFY(sr.end() != a+2);
		VERIFY(sr.size() == 3);
	}
	return true;
}

inline bool test02_2()
{
	{
		const std::forward_list fwl = {1, 2, 3, 4};
		hamon::ranges::subrange sr(fwl.begin(), fwl.end(), 4);
		static_assert(hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin() == fwl.begin());
		VERIFY(sr.end() == fwl.end());
		VERIFY(sr.size() == 4);
	}
	{
		const std::vector vec = {1, 2, 3, 4, 5};
		hamon::ranges::subrange sr(vec.begin(), vec.end(), 5);
		static_assert(hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin() == vec.begin());
		VERIFY(sr.end() == vec.end());
		VERIFY(sr.size() == 5);
	}
	return true;
}

// Range
inline HAMON_CXX14_CONSTEXPR bool test03_1()
{
	{
		int a[] = {1, 2, 3};
		hamon::ranges::subrange sr(a);
		static_assert(std::is_same<decltype(sr), hamon::ranges::subrange<int*, int*, hamon::ranges::subrange_kind::sized>>::value, "");
		static_assert(hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin() == a);
		VERIFY(sr.end() == a+3);
		VERIFY(sr.size() == 3);
	}
	{
		int a[] = {1, 2, 3, 4, 5};
		test_forward_range<int> r(a, a+5);
		using Iter = test_forward_range<int>::iterator;
		using Sent = test_forward_range<int>::sentinel;
		hamon::ranges::subrange sr(r);
		static_assert(std::is_same<decltype(sr), hamon::ranges::subrange<Iter, Sent, hamon::ranges::subrange_kind::unsized>>::value, "");
		static_assert(!hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin().m_ptr == a);
		VERIFY(sr.end().m_it.m_ptr == a+5);
	}
	{
		int a[] = {1, 2, 3, 4, 5};
		test_random_access_range<int> r(a, a+5);
		using Iter = test_random_access_range<int>::iterator;
		using Sent = test_random_access_range<int>::sentinel;
		hamon::ranges::subrange sr(r);
		static_assert(std::is_same<decltype(sr), hamon::ranges::subrange<Iter, Sent, hamon::ranges::subrange_kind::sized>>::value, "");
		static_assert(hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin().m_ptr == a);
		VERIFY(sr.end().m_it.m_ptr == a+5);
		VERIFY(sr.size() == 5);
	}
	return true;
}

inline bool test03_2()
{
	{
		const std::forward_list fwl = {1, 2, 3, 4};
		hamon::ranges::subrange sr(fwl);
		static_assert(!hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin() == fwl.begin());
		VERIFY(sr.end() == fwl.end());
	}
	{
		const std::vector vec = {1, 2, 3, 4, 5};
		hamon::ranges::subrange sr(vec);
		static_assert(hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin() == vec.begin());
		VERIFY(sr.end() == vec.end());
		VERIFY(sr.size() == 5);
	}
	return true;
}

// Range
inline HAMON_CXX14_CONSTEXPR bool test04_1()
{
	{
		int a[] = {1, 2, 3};
		hamon::ranges::subrange sr(a, 3);
		static_assert(std::is_same<decltype(sr), hamon::ranges::subrange<int*, int*, hamon::ranges::subrange_kind::sized>>::value, "");
		static_assert(hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin() == a);
		VERIFY(sr.end() == a+3);
		VERIFY(sr.size() == 3);
	}
	{
		int a[] = {1, 2, 3, 4, 5};
		test_forward_range<int> r(a, a+5);
		using Iter = test_forward_range<int>::iterator;
		using Sent = test_forward_range<int>::sentinel;
		hamon::ranges::subrange sr(r, 5);
		static_assert(std::is_same<decltype(sr), hamon::ranges::subrange<Iter, Sent, hamon::ranges::subrange_kind::sized>>::value, "");
		static_assert(hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin().m_ptr == a);
		VERIFY(sr.end().m_it.m_ptr == a+5);
		VERIFY(sr.size() == 5);
	}
	{
		int a[] = {1, 2, 3, 4, 5};
		test_random_access_range<int> r(a, a+5);
		using Iter = test_random_access_range<int>::iterator;
		using Sent = test_random_access_range<int>::sentinel;
		hamon::ranges::subrange sr(r, 5);
		static_assert(std::is_same<decltype(sr), hamon::ranges::subrange<Iter, Sent, hamon::ranges::subrange_kind::sized>>::value, "");
		static_assert(hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin().m_ptr == a);
		VERIFY(sr.end().m_it.m_ptr == a+5);
		VERIFY(sr.size() == 5);
	}
	return true;
}

inline bool test04_2()
{
	{
		const std::forward_list fwl = {1, 2, 3, 4};
		hamon::ranges::subrange sr(fwl, 4);
		static_assert(hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin() == fwl.begin());
		VERIFY(sr.end() == fwl.end());
		VERIFY(sr.size() == 4);
	}
	{
		const std::vector vec = {1, 2, 3, 4, 5};
		hamon::ranges::subrange sr(vec, 5);
		static_assert(hamon::ranges::sized_range_t<decltype(sr)>::value, "");
		VERIFY(sr.begin() == vec.begin());
		VERIFY(sr.end() == vec.end());
		VERIFY(sr.size() == 5);
	}
	return true;
}

GTEST_TEST(RangesTest, SubrangeCTADTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01_1());
	                      EXPECT_TRUE(test01_2());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02_1());
	                      EXPECT_TRUE(test02_2());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03_1());
	                      EXPECT_TRUE(test03_2());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04_1());
	                      EXPECT_TRUE(test04_2());
}

#endif	// defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

#undef VERIFY

}	// namespace ctad_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
