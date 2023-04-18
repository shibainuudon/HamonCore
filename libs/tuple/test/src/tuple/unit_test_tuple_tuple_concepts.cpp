/**
 *	@file	unit_test_tuple_tuple_concepts.cpp
 *
 *	@brief
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/concepts/detail/is_specialization_of_tuple.hpp>

static_assert(hamon::detail::is_specialization_of_tuple<hamon::tuple<int>>::value, "");
static_assert(hamon::detail::is_specialization_of_tuple<hamon::tuple<char, float, int>>::value, "");
