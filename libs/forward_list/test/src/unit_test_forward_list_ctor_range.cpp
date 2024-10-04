/**
 *	@file	unit_test_forward_list_ctor_range.cpp
 *
 *	@brief	Rangeを引数に取るコンストラクタのテスト
 *
 *	template<container-compatible-range<T> R>
 *	forward_list(from_range_t, R&& rg, const Allocator& = Allocator());
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_forward_list_test
{

namespace ctor_range_test
{
#if 0	// TODO
struct S1
{
	int value;
};

HAMON_CXX11_CONSTEXPR bool
operator==(S1 const& lhs, S1 const& rhs)
{
	return lhs.value == rhs.value;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, template <typename> class RangeWrapper, typename Allocator>
HAMON_CXX20_CONSTEXPR bool test1(Allocator const& alloc)
{
	using ForwardList = hamon::forward_list<T, Allocator>;
	using Range = RangeWrapper<T>;

	static_assert(!hamon::is_constructible<ForwardList, Range>::value, "");
	static_assert(!hamon::is_constructible<ForwardList, Range, Allocator>::value, "");
	static_assert( hamon::is_constructible<ForwardList, hamon::from_range_t, Range>::value, "");
	static_assert( hamon::is_constructible<ForwardList, hamon::from_range_t, Range, Allocator>::value, "");
	static_assert(!hamon::is_nothrow_constructible<ForwardList, hamon::from_range_t, Range>::value, "");
	static_assert(!hamon::is_nothrow_constructible<ForwardList, hamon::from_range_t, Range, Allocator>::value, "");
	static_assert( hamon::is_implicitly_constructible<ForwardList, hamon::from_range_t, Range>::value, "");
	static_assert( hamon::is_implicitly_constructible<ForwardList, hamon::from_range_t, Range, Allocator>::value, "");
	static_assert(!hamon::is_trivially_constructible<ForwardList, hamon::from_range_t, Range>::value, "");
	static_assert(!hamon::is_trivially_constructible<ForwardList, hamon::from_range_t, Range, Allocator>::value, "");

	{
		T a[] = {{1},{2},{3},{4}};
		Range r(a);
		ForwardList v(hamon::from_range, r);
		VERIFY(!v.empty());
		auto it = v.begin();
		VERIFY(*it++ == a[0]);
		VERIFY(*it++ == a[1]);
		VERIFY(*it++ == a[2]);
		VERIFY(*it++ == a[3]);
		VERIFY(it == v.end());
	}
	{
		T a[] = {{3},{1},{4}};
		Range r(a);
		ForwardList v(hamon::from_range, r, alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(!v.empty());
		auto it = v.begin();
		VERIFY(*it++ == a[0]);
		VERIFY(*it++ == a[1]);
		VERIFY(*it++ == a[2]);
		VERIFY(it == v.end());
	}

	return true;
}

template <typename T, typename Allocator>
HAMON_CXX20_CONSTEXPR bool test(Allocator const& alloc)
{
	return
		test1<T, test_input_range>(alloc) &&
		test1<T, test_forward_range>(alloc) &&
		test1<T, test_bidirectional_range>(alloc) &&
		test1<T, test_random_access_range>(alloc) &&
		test1<T, test_contiguous_range>(alloc) &&
		test1<T, test_input_sized_range>(alloc) &&
		test1<T, test_forward_sized_range>(alloc) &&
		test1<T, test_bidirectional_sized_range>(alloc) &&
		test1<T, test_random_access_sized_range>(alloc) &&
		test1<T, test_contiguous_sized_range>(alloc);
}

#undef VERIFY

GTEST_TEST(ForwardListTest, CtorRangeTest)
{
	{
		hamon::allocator<char> alloc;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>(alloc));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>(alloc));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>(alloc));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>(alloc));
	}
}
#endif
}	// namespace ctor_range_test

}	// namespace hamon_forward_list_test
