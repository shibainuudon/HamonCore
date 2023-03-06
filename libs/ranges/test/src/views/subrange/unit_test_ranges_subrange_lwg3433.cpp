/**
 *	@file	unit_test_ranges_subrange_lwg3433.cpp
 *
 *	@brief	https://cplusplus.github.io/LWG/issue3433
 */

#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace lwg3433_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template<typename T, typename Iterator>
struct test_sized_range_sized_sent : test_sized_range<T, Iterator>
{
	using test_sized_range<T, Iterator>::test_sized_range;

	template<typename I>
	struct sentinel
	{
		T* m_end;

		friend HAMON_CXX14_CONSTEXPR bool
		operator==(const sentinel& s, const I& i) noexcept
		{
			return s.m_end == i.m_ptr;
		}

		friend HAMON_CXX14_CONSTEXPR bool
		operator!=(const sentinel& s, const I& i) noexcept
		{
			return !(s == i);
		}

		friend HAMON_CXX14_CONSTEXPR bool
		operator==(const I& i, const sentinel& s) noexcept
		{
			return s.m_end == i.m_ptr;
		}

		friend HAMON_CXX14_CONSTEXPR bool
		operator!=(const I& i, const sentinel& s) noexcept
		{
			return !(s == i);
		}

		friend HAMON_CXX14_CONSTEXPR hamon::iter_difference_t<I>
		operator-(const sentinel& s, const I& i) noexcept
		{
			return s.m_end - i.m_ptr;
		}

		friend HAMON_CXX14_CONSTEXPR hamon::iter_difference_t<I>
		operator-(const I& i, const sentinel& s) noexcept
		{
			return i.m_ptr - s.m_end;
		}
	};

	HAMON_CXX14_CONSTEXPR sentinel<Iterator> end() &
	{
		return sentinel<Iterator>{this->m_last};
	}
};

template <typename Container, typename Subrange>
inline HAMON_CXX14_CONSTEXPR bool
test01_impl(Container& r, Subrange& sr, hamon::true_type /*sized*/, hamon::true_type /*bidirectional*/)
{
	namespace ranges = hamon::ranges;
	(void)r;
	{
		int y[] = { 1, 2, 3, 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}
	VERIFY(sr.size() == 5);

	sr = sr.next();

	{
		int y[] = { 2, 3, 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}
	VERIFY(sr.size() == 4);

	sr = hamon::move(sr).next(2);

	{
		int y[] = { 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}
	VERIFY(sr.size() == 2);

	sr = sr.prev(2);
	{
		int y[] = { 2, 3, 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}
	VERIFY(sr.size() == 4);

	sr = sr.prev();
	{
		int y[] = { 1, 2, 3, 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}
	VERIFY(sr.size() == 5);

	sr.advance(1);
	{
		int y[] = { 2, 3, 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}
	VERIFY(sr.size() == 4);

	sr.advance(-1);
	{
		int y[] = { 1, 2, 3, 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}
	VERIFY(sr.size() == 5);

	return true;
}

template <typename Container, typename Subrange>
inline HAMON_CXX14_CONSTEXPR bool
test01_impl(Container& r, Subrange& sr, hamon::true_type /*sized*/, hamon::false_type /*bidirectional*/)
{
	namespace ranges = hamon::ranges;
	{
		int y[] = { 1, 2, 3, 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}
	VERIFY(sr.size() == 5);

	sr = sr.next();

	{
		int y[] = { 2, 3, 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}
	VERIFY(sr.size() == 4);

	sr = hamon::move(sr).next(2);

	{
		int y[] = { 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}
	VERIFY(sr.size() == 2);

	sr = r;

	sr.advance(1);
	{
		int y[] = { 2, 3, 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}
	VERIFY(sr.size() == 4);

	return true;
}

template <typename Container, typename Subrange>
inline HAMON_CXX14_CONSTEXPR bool
test01_impl(Container& r, Subrange& sr, hamon::false_type /*sized*/, hamon::true_type /*bidirectional*/)
{
	namespace ranges = hamon::ranges;
	(void)r;
	{
		int y[] = { 1, 2, 3, 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}

	sr = sr.next();

	{
		int y[] = { 2, 3, 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}

	sr = hamon::move(sr).next(2);

	{
		int y[] = { 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}

	sr = sr.prev(2);
	{
		int y[] = { 2, 3, 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}

	sr = sr.prev();
	{
		int y[] = { 1, 2, 3, 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}

	sr.advance(1);
	{
		int y[] = { 2, 3, 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}

	sr.advance(-1);
	{
		int y[] = { 1, 2, 3, 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}

	return true;
}

template <typename Container, typename Subrange>
inline HAMON_CXX14_CONSTEXPR bool
test01_impl(Container& r, Subrange& sr, hamon::false_type /*sized*/, hamon::false_type /*bidirectional*/)
{
	namespace ranges = hamon::ranges;
	{
		int y[] = { 1, 2, 3, 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}

	sr = sr.next();

	{
		int y[] = { 2, 3, 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}

	sr = hamon::move(sr).next(2);

	{
		int y[] = { 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}

	sr = r;

	sr.advance(1);
	{
		int y[] = { 2, 3, 4, 5 };
		VERIFY(ranges::equal(sr, y));
	}

	return true;
}

template <typename Container>
inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;

	int x[] = { 1,2,3,4,5 };
	Container r{ x };
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	ranges::subrange sr = r;
#else
	using Subrange = hamon::ranges::subrange<
		ranges::iterator_t<Container>,
		ranges::sentinel_t<Container>,
		ranges::sized_range_t<Container>::value ? ranges::subrange_kind::sized : ranges::subrange_kind::unsized
	>;
	Subrange sr = r;
#endif

	return test01_impl(
		r,
		sr,
		ranges::sized_range_t<decltype(sr)>{},
		ranges::bidirectional_range_t<decltype(sr)>{});
}

GTEST_TEST(RangesTest, SubrangeLWG3433Test)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test01<test_sized_range_sized_sent<int, bidirectional_iterator_wrapper<int>>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test01<test_sized_range<int, bidirectional_iterator_wrapper<int>>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test01<test_range<int, bidirectional_iterator_wrapper<int>>>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test01<test_sized_range_sized_sent<int, forward_iterator_wrapper<int>>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test01<test_sized_range<int, forward_iterator_wrapper<int>>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test01<test_range<int, forward_iterator_wrapper<int>>>()));
}

#undef VERIFY

}	// namespace lwg3433_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
