/**
 *	@file	unit_test_ranges_subrange_begin_end.cpp
 *
 *	@brief	ranges::subrange::begin, end のテスト
 */

#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/views/subrange_kind.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/as_const.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <iterator>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace begin_end_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename S>
struct HasBeginImpl
{
private:
	template <typename S2,
		typename = decltype(hamon::declval<S2>().begin())
	>
	static auto test(int) -> hamon::true_type;

	template <typename S2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<S>(0));
};

template <typename S>
using HasBegin = typename HasBeginImpl<S>::type;

template <typename T>
struct MoveOnlyForwardIterator
{
	T*	m_ptr;
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using reference         = T&;
	HAMON_CXX14_CONSTEXPR MoveOnlyForwardIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR MoveOnlyForwardIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR T&                       operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const MoveOnlyForwardIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const MoveOnlyForwardIterator& rhs) const { return !(*this == rhs); }

	friend HAMON_CXX11_CONSTEXPR bool operator==(const MoveOnlyForwardIterator& lhs, T* rhs) { return lhs.m_ptr == rhs; }
	friend HAMON_CXX11_CONSTEXPR bool operator!=(const MoveOnlyForwardIterator& lhs, T* rhs) { return !(lhs == rhs); }
	friend HAMON_CXX11_CONSTEXPR bool operator==(T* rhs, const MoveOnlyForwardIterator& lhs) { return lhs.m_ptr == rhs; }
	friend HAMON_CXX11_CONSTEXPR bool operator!=(T* rhs, const MoveOnlyForwardIterator& lhs) { return !(lhs == rhs); }

	MoveOnlyForwardIterator() = default;
	MoveOnlyForwardIterator(MoveOnlyForwardIterator &&) = default;
	MoveOnlyForwardIterator &operator=(MoveOnlyForwardIterator&&) = default;
	MoveOnlyForwardIterator(MoveOnlyForwardIterator const&) = delete;
	HAMON_CXX11_CONSTEXPR MoveOnlyForwardIterator(T* ptr) : m_ptr(ptr) { }
};

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using ForwardIter = forward_iterator_wrapper<int>;
		int x[] = {1, 2, 3, 4, 5};
		hamon::ranges::subrange<ForwardIter, ForwardIter> sr(ForwardIter{x}, ForwardIter{x+5});
		VERIFY(sr.begin().m_ptr == x);
		VERIFY(sr.end().m_ptr == x+5);

		int i = 1;
		for (int a : sr)
		{
			VERIFY(a == i);
			i++;
		}

		static_assert( HasBegin<decltype(sr)>::value, "");
		static_assert( HasBegin<decltype(sr) &>::value, "");
		static_assert( HasBegin<decltype(sr) const&>::value, "");
		static_assert( HasBegin<decltype(sr) &&>::value, "");
		static_assert( HasBegin<decltype(sr) const&&>::value, "");
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		using MoveOnlyForwardIterator = MoveOnlyForwardIterator<int>;
		int x[] = {1, 2, 3, 4, 5};
		hamon::ranges::subrange<MoveOnlyForwardIterator, int*> sr(MoveOnlyForwardIterator{x}, x+5);
		VERIFY(sr.begin().m_ptr == x);
		VERIFY(sr.end() == x+5);

#if defined(HAMON_HAS_CXX17_RANGE_BASED_FOR)
		int i = 1;
		for (int a : sr)
		{
			VERIFY(a == i);
			i++;
		}
#endif

		static_assert( HasBegin<decltype(sr)>::value, "");
		static_assert( HasBegin<decltype(sr) &>::value, "");
		static_assert(!HasBegin<decltype(sr) const&>::value, "");
		static_assert( HasBegin<decltype(sr) &&>::value, "");
		static_assert(!HasBegin<decltype(sr) const&&>::value, "");
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	{
		int a[] = {1, 2, 3};
		hamon::ranges::subrange<int*, hamon::unreachable_sentinel_t> sr(a, hamon::unreachable_sentinel);
		auto first = sr.begin();
		auto last  = sr.end();
		VERIFY(first == a);
		VERIFY(last != a + 0);
		VERIFY(last != a + 1);
		VERIFY(last != a + 2);
		static_assert(hamon::is_same<decltype(last), hamon::unreachable_sentinel_t>::value, "");

		static_assert( HasBegin<decltype(sr)>::value, "");
		static_assert( HasBegin<decltype(sr) &>::value, "");
		static_assert( HasBegin<decltype(sr) const&>::value, "");
		static_assert( HasBegin<decltype(sr) &&>::value, "");
		static_assert( HasBegin<decltype(sr) const&&>::value, "");
	}
	return true;
}

GTEST_TEST(RangesTest, SubrangeBeginEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

#undef VERIFY

}	// namespace begin_end_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
