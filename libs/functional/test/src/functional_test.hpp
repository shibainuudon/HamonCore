/**
 *	@file	functional_test.hpp
 *
 *	@brief
 */

#ifndef UNIT_TEST_FUNCTIONAL_FUNCTIONAL_TEST_HPP
#define UNIT_TEST_FUNCTIONAL_FUNCTIONAL_TEST_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>

namespace hamon_functional_test
{

template <typename T, typename = void>
struct has_is_transparent
	: public hamon::false_type {};

template <typename T>
struct has_is_transparent<T, hamon::void_t<typename T::is_transparent>>
	: public hamon::true_type {};

}	// namespace hamon_functional_test

#endif // UNIT_TEST_FUNCTIONAL_FUNCTIONAL_TEST_HPP
