/**
 *	@file	unit_test_ranges_join_with_view_concepts.cpp
 *
 *	@brief	join_with_view のテスト
 */

#include <hamon/ranges/adaptors/join_with_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_with_view_test
{
namespace concepts_test
{

#if 1
template <template <typename> class V1, template <typename> class V2, template <typename> class P>
void test0()
{
	using T = int;
	using V = V1<V2<T>>;
	using IV = hamon::ranges::range_reference_t<V>;
	using Pattern = P<T>;
	using JWV = hamon::ranges::join_with_view<V, Pattern>;

	static_assert(hamon::ranges::range_t<JWV>::value                     == true, "");
	static_assert(hamon::ranges::borrowed_range_t<JWV>::value            == false, "");
	static_assert(hamon::ranges::sized_range_t<JWV>::value               == false, "");
	static_assert(hamon::ranges::approximately_sized_range<JWV> == false, "");
	static_assert(hamon::ranges::output_range_t<JWV, T>::value           ==
		(hamon::ranges::forward_range_t<V>::value &&
		 hamon::ranges::forward_range_t<IV>::value), "");
	static_assert(hamon::ranges::input_range_t<JWV>::value               == true, "");
	static_assert(hamon::ranges::forward_range_t<JWV>::value             ==
		(hamon::ranges::forward_range_t<V>::value &&
		 hamon::ranges::forward_range_t<IV>::value), "");
	static_assert(hamon::ranges::bidirectional_range<JWV> ==
		(hamon::ranges::bidirectional_range<V> &&
		 hamon::ranges::bidirectional_range<IV> &&
		 hamon::ranges::bidirectional_range<Pattern> &&
		 hamon::ranges::common_range_t<IV>::value &&
		 hamon::ranges::common_range_t<Pattern>::value), "");
	static_assert(hamon::ranges::random_access_range_t<JWV>::value       == false, "");
	static_assert(hamon::ranges::contiguous_range_t<JWV>::value          == false, "");
	static_assert(hamon::ranges::common_range_t<JWV>::value              ==
		(hamon::ranges::forward_range_t<V>::value &&
		 hamon::ranges::forward_range_t<IV>::value &&
		 hamon::ranges::common_range_t<V>::value &&
		 hamon::ranges::common_range_t<IV>::value), "");
	static_assert(hamon::ranges::viewable_range_t<JWV>::value            == true, "");
	static_assert(hamon::ranges::view_t<JWV>::value                      == true, "");
	static_assert(hamon::ranges::constant_range_t<JWV>::value            == false, "");
}

template <template <typename> class V1, template <typename> class V2>
void test1()
{
//	test0<V1, V2, test_input_view>();
	test0<V1, V2, test_forward_view>();
	test0<V1, V2, test_bidirectional_view>();
	test0<V1, V2, test_random_access_view>();
	//test0<V1, V2, test_contiguous_view>();

//	test0<V1, V2, test_input_common_view>();
	test0<V1, V2, test_forward_common_view>();
	test0<V1, V2, test_bidirectional_common_view>();
	//test0<V1, V2, test_random_access_common_view>();
	//test0<V1, V2, test_contiguous_common_view>();
}

template <template <typename> class V1>
void test2()
{
	test1<V1, test_input_view>();
	test1<V1, test_forward_view>();
	test1<V1, test_bidirectional_view>();
	test1<V1, test_random_access_view>();
	//test1<V1, test_contiguous_view>();

	//test1<V1, test_input_common_view>();
	test1<V1, test_forward_common_view>();
	test1<V1, test_bidirectional_common_view>();
	//test1<V1, test_random_access_common_view>();
	//test1<V1, test_contiguous_common_view>();

	//test1<V1, test_input_borrowed_view>();
	//test1<V1, test_forward_borrowed_view>();
	//test1<V1, test_bidirectional_borrowed_view>();
	//test1<V1, test_random_access_borrowed_view>();
	//test1<V1, test_contiguous_borrowed_view>();

	//test1<V1, test_input_sized_view>();
	//test1<V1, test_forward_sized_view>();
	//test1<V1, test_bidirectional_sized_view>();
	//test1<V1, test_random_access_sized_view>();
	//test1<V1, test_contiguous_sized_view>();
}

void test()
{
	test2<test_input_view>();
	test2<test_forward_view>();
	test2<test_bidirectional_view>();
	test2<test_random_access_view>();
	//test2<test_contiguous_view>();

	//test2<test_input_common_view>();
	test2<test_forward_common_view>();
	test2<test_bidirectional_common_view>();
	//test2<test_random_access_common_view>();
	//test2<test_contiguous_common_view>();

	//test2<test_input_borrowed_view>();
	//test2<test_forward_borrowed_view>();
	//test2<test_bidirectional_borrowed_view>();
	//test2<test_random_access_borrowed_view>();
	//test2<test_contiguous_borrowed_view>();

	//test2<test_input_sized_view>();
	//test2<test_forward_sized_view>();
	//test2<test_bidirectional_sized_view>();
	//test2<test_random_access_sized_view>();
	//test2<test_contiguous_sized_view>();
}

#endif

GTEST_TEST(RangesTest, JoinWithViewConceptsTest)
{
	test();

#if 0
	{
		using T = int;
		using V = test_input_view<test_input_view<T>>;
		using Pattern = test_forward_view<T>;
		using JWV = hamon::ranges::join_with_view<V, Pattern>;
		static_assert( hamon::ranges::range_t<JWV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<JWV>, "");
		static_assert(!hamon::ranges::output_range_t<JWV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::forward_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<JWV>, "");
		static_assert(!hamon::ranges::random_access_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::common_range_t<JWV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<JWV>::value, "");
		static_assert( hamon::ranges::view_t<JWV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<JWV>::value, "");
	}
	{
		using T = int;
		using V = test_forward_view<test_forward_view<T>>;
		using Pattern = test_forward_view<T>;
		using JWV = hamon::ranges::join_with_view<V, Pattern>;
		static_assert( hamon::ranges::range_t<JWV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<JWV>, "");
		static_assert( hamon::ranges::output_range_t<JWV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<JWV>::value, "");
		static_assert( hamon::ranges::forward_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<JWV>, "");
		static_assert(!hamon::ranges::random_access_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::common_range_t<JWV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<JWV>::value, "");
		static_assert( hamon::ranges::view_t<JWV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<JWV>::value, "");
	}
	{
		using T = int;
		using V = test_bidirectional_view<test_bidirectional_common_view<T>>;
		using Pattern = test_bidirectional_common_view<T>;
		using JWV = hamon::ranges::join_with_view<V, Pattern>;
		static_assert( hamon::ranges::range_t<JWV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<JWV>, "");
		static_assert( hamon::ranges::output_range_t<JWV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<JWV>::value, "");
		static_assert( hamon::ranges::forward_range_t<JWV>::value, "");
		static_assert( hamon::ranges::bidirectional_range<JWV>, "");
		static_assert(!hamon::ranges::random_access_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::common_range_t<JWV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<JWV>::value, "");
		static_assert( hamon::ranges::view_t<JWV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<JWV>::value, "");
	}
	{
		using T = int;
		using V = test_forward_common_view<test_forward_common_view<T>>;
		using Pattern = test_forward_view<T>;
		using JWV = hamon::ranges::join_with_view<V, Pattern>;
		static_assert( hamon::ranges::range_t<JWV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<JWV>, "");
		static_assert( hamon::ranges::output_range_t<JWV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<JWV>::value, "");
		static_assert( hamon::ranges::forward_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<JWV>, "");
		static_assert(!hamon::ranges::random_access_range_t<JWV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<JWV>::value, "");
		static_assert( hamon::ranges::common_range_t<JWV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<JWV>::value, "");
		static_assert( hamon::ranges::view_t<JWV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<JWV>::value, "");
	}
#endif
}

}	// namespace concepts_test
}	// namespace join_with_view_test
}	// namespace hamon_ranges_test
