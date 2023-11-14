/**
 *	@file	unit_test_iterator_iter_const_reference_t.cpp
 *
 *	@brief	iter_const_reference_t のテスト
 */

#include <hamon/iterator/iter_const_reference_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/vector.hpp>

namespace hamon_iterator_test
{

namespace iter_const_reference_t_test
{

template <typename R, typename V>
struct test
{
	using value_type = V;
	using difference = std::ptrdiff_t;

	auto operator*() const->R;
};

static_assert(hamon::is_same<hamon::iter_const_reference_t<test<int&, int>>, const int&>::value, "");
static_assert(hamon::is_same<hamon::iter_const_reference_t<test<int&&, int>>, const int&&>::value, "");
static_assert(hamon::is_same<hamon::iter_const_reference_t<test<const int&, int>>, const int&>::value, "");
static_assert(hamon::is_same<hamon::iter_const_reference_t<test<const int&&, int>>, const int&&>::value, "");
static_assert(hamon::is_same<hamon::iter_const_reference_t<test<int, int>>, int>::value, "");
static_assert(hamon::is_same<hamon::iter_const_reference_t<test<const int, int>>, int>::value, "");

}	// namespace iter_const_reference_t_test

}	// namespace hamon_iterator_test
