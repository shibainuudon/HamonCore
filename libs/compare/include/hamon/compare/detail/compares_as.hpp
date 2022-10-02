/**
 *	@file	compares_as.hpp
 *
 *	@brief	compares_as の定義
 */

#ifndef HAMON_COMPARE_DETAIL_COMPARES_AS_HPP
#define HAMON_COMPARE_DETAIL_COMPARES_AS_HPP

#include <hamon/compare/common_comparison_category.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename Cat>
concept compares_as =
	hamon::same_as<hamon::common_comparison_category_t<T, Cat>, Cat>;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_COMPARE_DETAIL_COMPARES_AS_HPP
