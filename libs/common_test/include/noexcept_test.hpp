/**
 *	@file	noexcept_test.hpp
 *
 *	@brief	
 */

#ifndef UNIT_TEST_COMMON_NOEXCEPT_TEST_HPP
#define UNIT_TEST_COMMON_NOEXCEPT_TEST_HPP

#define HAMON_ASSERT_NOEXCEPT_TRUE(...) \
    static_assert(noexcept(__VA_ARGS__), "Operation must be noexcept")

#define HAMON_ASSERT_NOEXCEPT_FALSE(...) \
    static_assert(!noexcept(__VA_ARGS__), "Operation must not be noexcept")

#endif // UNIT_TEST_COMMON_NOEXCEPT_TEST_HPP
