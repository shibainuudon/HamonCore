/**
 *	@file	unit_test_iterator_projected.cpp
 *
 *	@brief	projected のテスト
 */

#include <hamon/iterator/projected.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>
#include <hamon/iterator/iter_common_reference_t.hpp>
#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/forward.hpp>
#include <cstddef>
#include <vector>

namespace hamon_iterator_test
{

namespace projected_test
{

struct Identity
{
	template <typename T>
	T&& operator()(T&& t) const
	{
		return hamon::forward<T>(t);
	}
};

using vec_iterator = std::vector<int>::iterator;
using vecitr_proj = hamon::projected<vec_iterator, Identity>;

static_assert(hamon::indirectly_readable_t<vecitr_proj>::value, "");
static_assert(hamon::is_same<vecitr_proj::value_type, int>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<vecitr_proj>, std::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<vecitr_proj>, int>::value, "");
static_assert(hamon::is_same<hamon::iter_reference_t<vecitr_proj>, int&>::value, "");
static_assert(hamon::is_same<hamon::iter_rvalue_reference_t<vecitr_proj>, int&&>::value, "");
static_assert(hamon::is_same<hamon::iter_common_reference_t<vecitr_proj>, int&>::value, "");

struct Proj
{
	double operator()(int) const { return 0.0; }
};
using vecitr_proj2 = hamon::projected<vec_iterator, Proj>;

static_assert(hamon::indirectly_readable_t<vecitr_proj2>::value, "");
static_assert(hamon::is_same<vecitr_proj2::value_type, double>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<vecitr_proj2>, std::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<vecitr_proj2>, double>::value, "");
static_assert(hamon::is_same<hamon::iter_reference_t<vecitr_proj2>, double>::value, "");
static_assert(hamon::is_same<hamon::iter_rvalue_reference_t<vecitr_proj2>, double>::value, "");
static_assert(hamon::is_same<hamon::iter_common_reference_t<vecitr_proj2>, double>::value, "");

}	// namespace projected_test

}	// namespace hamon_iterator_test
