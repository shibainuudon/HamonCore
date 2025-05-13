/**
 *	@file	queue_test_helper.hpp
 *
 *	@brief
 */

#ifndef HAMON_QUEUE_TEST_HELPER_HPP
#define HAMON_QUEUE_TEST_HELPER_HPP

#include <hamon/memory/allocator.hpp>

namespace hamon_queue_test
{

template <typename T>
struct TestAllocator : hamon::allocator<T>
{
	TestAllocator() = default;
	TestAllocator(TestAllocator const&) = default;

	template <typename U>
	constexpr TestAllocator(TestAllocator<U> const&) noexcept {}
};

}	// namespace hamon_queue_test

#endif // HAMON_QUEUE_TEST_HELPER_HPP
