/**
 *	@file	unit_test_memory_detail_pointer_of_or.cpp
 *
 *	@brief	POINTER_OF_OR のテスト
 */

#include <hamon/memory/detail/pointer_of_or.hpp>
#include <hamon/type_traits/is_same.hpp>

namespace hamon_memory_test
{

namespace pointer_of_or_test
{

template <typename T>
struct S1
{
	using element_type = T;
	using pointer = T const*;
};

template <typename T>
struct S2
{
	using element_type = T;
};

template <typename T>
struct S3
{
};

struct S4
{
};

static_assert(hamon::is_same<hamon::detail::POINTER_OF_OR<S1<int>, void*>, int const*>::value, "");
static_assert(hamon::is_same<hamon::detail::POINTER_OF_OR<S2<int>, void*>, int*>::value, "");
static_assert(hamon::is_same<hamon::detail::POINTER_OF_OR<S3<int>, void*>, int*>::value, "");
static_assert(hamon::is_same<hamon::detail::POINTER_OF_OR<S4, void*>, void*>::value, "");
static_assert(hamon::is_same<hamon::detail::POINTER_OF_OR<float*, void*>, float*>::value, "");
static_assert(hamon::is_same<hamon::detail::POINTER_OF_OR<float, void*>, void*>::value, "");

}	// namespace pointer_of_or_test

}	// namespace hamon_memory_test
