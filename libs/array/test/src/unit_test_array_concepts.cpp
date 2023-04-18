/**
 *	@file	unit_test_array_concepts.cpp
 *
 *	@brief
 */

#include <hamon/array/array.hpp>
#include <hamon/concepts/detail/is_specialization_of_array.hpp>

static_assert(hamon::detail::is_specialization_of_array<hamon::array<int, 3>>::value, "");
static_assert(hamon::detail::is_specialization_of_array<hamon::array<float, 10>>::value, "");
