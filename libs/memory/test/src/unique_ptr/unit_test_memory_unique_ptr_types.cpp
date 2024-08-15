/**
 *	@file	unit_test_memory_unique_ptr_types.cpp
 *
 *	@brief
 *
 *	using pointer      = see below;
 *	using element_type = T;
 *	using deleter_type = D;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/memory/default_delete.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_memory_test
{

namespace unique_ptr_test
{

namespace types_test
{

struct D
{
	using pointer = void*;
};

GTEST_TEST(UniquePtrTest, TypesTest)
{
	{
		using UP = hamon::unique_ptr<int>;
		static_assert(hamon::is_same<UP::pointer, int*>::value, "");
		static_assert(hamon::is_same<UP::element_type, int>::value, "");
		static_assert(hamon::is_same<UP::deleter_type, hamon::default_delete<int>>::value, "");
	}
	{
		using UP = hamon::unique_ptr<char, D>;
		static_assert(hamon::is_same<UP::pointer, void*>::value, "");
		static_assert(hamon::is_same<UP::element_type, char>::value, "");
		static_assert(hamon::is_same<UP::deleter_type, D>::value, "");
	}
	{
		using UP = hamon::unique_ptr<char, D&>;
		static_assert(hamon::is_same<UP::pointer, void*>::value, "");
		static_assert(hamon::is_same<UP::element_type, char>::value, "");
		static_assert(hamon::is_same<UP::deleter_type, D&>::value, "");
	}
	{
		using UP = hamon::unique_ptr<char, D*>;
		static_assert(hamon::is_same<UP::pointer, char*>::value, "");
		static_assert(hamon::is_same<UP::element_type, char>::value, "");
		static_assert(hamon::is_same<UP::deleter_type, D*>::value, "");
	}
	{
		using UP = hamon::unique_ptr<int, void(&)(void*)>;
		static_assert(hamon::is_same<UP::pointer, int*>::value, "");
		static_assert(hamon::is_same<UP::element_type, int>::value, "");
		static_assert(hamon::is_same<UP::deleter_type, void(&)(void*)>::value, "");
	}
	{
		using UP = hamon::unique_ptr<int, void(*)(void*)>;
		static_assert(hamon::is_same<UP::pointer, int*>::value, "");
		static_assert(hamon::is_same<UP::element_type, int>::value, "");
		static_assert(hamon::is_same<UP::deleter_type, void(*)(void*)>::value, "");
	}
	{
		using UP = hamon::unique_ptr<int[]>;
		static_assert(hamon::is_same<UP::pointer, int*>::value, "");
		static_assert(hamon::is_same<UP::element_type, int>::value, "");
		static_assert(hamon::is_same<UP::deleter_type, hamon::default_delete<int[]>>::value, "");
	}
	{
		using UP = hamon::unique_ptr<float[], D>;
		static_assert(hamon::is_same<UP::pointer, void*>::value, "");
		static_assert(hamon::is_same<UP::element_type, float>::value, "");
		static_assert(hamon::is_same<UP::deleter_type, D>::value, "");
	}
	{
		using UP = hamon::unique_ptr<float[], D&>;
		static_assert(hamon::is_same<UP::pointer, void*>::value, "");
		static_assert(hamon::is_same<UP::element_type, float>::value, "");
		static_assert(hamon::is_same<UP::deleter_type, D&>::value, "");
	}
	{
		using UP = hamon::unique_ptr<char[], D*>;
		static_assert(hamon::is_same<UP::pointer, char*>::value, "");
		static_assert(hamon::is_same<UP::element_type, char>::value, "");
		static_assert(hamon::is_same<UP::deleter_type, D*>::value, "");
	}
	{
		using UP = hamon::unique_ptr<int[], void(&)(void*)>;
		static_assert(hamon::is_same<UP::pointer, int*>::value, "");
		static_assert(hamon::is_same<UP::element_type, int>::value, "");
		static_assert(hamon::is_same<UP::deleter_type, void(&)(void*)>::value, "");
	}
	{
		using UP = hamon::unique_ptr<int[], void(*)(void*)>;
		static_assert(hamon::is_same<UP::pointer, int*>::value, "");
		static_assert(hamon::is_same<UP::element_type, int>::value, "");
		static_assert(hamon::is_same<UP::deleter_type, void(*)(void*)>::value, "");
	}
}

}	// namespace types_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
