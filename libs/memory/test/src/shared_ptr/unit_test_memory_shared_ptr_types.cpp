/**
 *	@file	unit_test_memory_shared_ptr_types.cpp
 *
 *	@brief
 *
 *	using element_type = remove_extent_t<T>;
 *	using weak_type    = weak_ptr<T>;
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace shared_ptr_test
{

namespace types_test
{

GTEST_TEST(SharedPtrTest, TypesTest)
{
	{
		using SP = hamon::shared_ptr<int>;
		static_assert(hamon::is_same<typename SP::element_type, int>::value, "");
		static_assert(hamon::is_same<typename SP::weak_type, hamon::weak_ptr<int>>::value, "");
	}
	{
		using SP = hamon::shared_ptr<float const>;
		static_assert(hamon::is_same<typename SP::element_type, float const>::value, "");
		static_assert(hamon::is_same<typename SP::weak_type, hamon::weak_ptr<float const>>::value, "");
	}
	{
		using SP = hamon::shared_ptr<int const[]>;
		static_assert(hamon::is_same<typename SP::element_type, int const>::value, "");
		static_assert(hamon::is_same<typename SP::weak_type, hamon::weak_ptr<int const[]>>::value, "");
	}
	{
		using SP = hamon::shared_ptr<long[3]>;
		static_assert(hamon::is_same<typename SP::element_type, long>::value, "");
		static_assert(hamon::is_same<typename SP::weak_type, hamon::weak_ptr<long[3]>>::value, "");
	}
}

}	// namespace types_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
