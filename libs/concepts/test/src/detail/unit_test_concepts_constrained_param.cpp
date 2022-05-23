/**
 *	@file	unit_test_concepts_constrained_param.cpp
 *
 *	@brief	HAMON_CONSTRAINED_PARAM のテスト
 */

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/integral.hpp>

namespace hamon_concepts_test
{

namespace constrained_param_test
{

template <HAMON_CONSTRAINED_PARAM(hamon::integral, T)>
constexpr int f(T)
{
	return 1;
}

constexpr int f(...)
{
	return 2;
}

static_assert(f(0) == 1, "");
static_assert(f(0.0f) == 2, "");

}	// namespace constrained_param_test

}	// namespace hamon_concepts_test
