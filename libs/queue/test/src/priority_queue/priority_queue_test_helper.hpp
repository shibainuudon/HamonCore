/**
 *	@file	priority_queue_test_helper.hpp
 *
 *	@brief
 */

#ifndef HAMON_PRIORITY_QUEUE_TEST_HELPER_HPP
#define HAMON_PRIORITY_QUEUE_TEST_HELPER_HPP

#include <hamon/memory/allocator.hpp>

namespace hamon_priority_queue_test
{

template <typename T>
struct TestAllocator : hamon::allocator<T>
{
	TestAllocator() = default;
	TestAllocator(TestAllocator const&) = default;

	template <typename U>
	constexpr TestAllocator(TestAllocator<U> const&) noexcept {}
};

}	// namespace hamon_priority_queue_test

#endif // HAMON_PRIORITY_QUEUE_TEST_HELPER_HPP
