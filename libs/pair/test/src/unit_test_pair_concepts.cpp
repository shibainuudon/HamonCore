/**
 *	@file	unit_test_pair_concepts.cpp
 *
 *	@brief
 */

#include <hamon/pair/pair.hpp>
#include <hamon/concepts/detail/is_specialization_of_pair.hpp>

static_assert(hamon::detail::is_specialization_of_pair<hamon::pair<int, float>>::value, "");
static_assert(hamon::detail::is_specialization_of_pair<hamon::pair<double, long>>::value, "");
