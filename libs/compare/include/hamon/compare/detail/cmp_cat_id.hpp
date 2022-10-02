/**
 *	@file	cmp_cat_id.hpp
 *
 *	@brief	cmp_cat_id の定義
 */

#ifndef HAMON_COMPARE_DETAIL_CMP_CAT_ID_HPP
#define HAMON_COMPARE_DETAIL_CMP_CAT_ID_HPP

#include <hamon/compare/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
struct cmp_cat_id
{
	static constexpr unsigned value = 1;
};

template <> struct cmp_cat_id<hamon::partial_ordering> { static constexpr unsigned value = 2; };
template <> struct cmp_cat_id<hamon::weak_ordering>    { static constexpr unsigned value = 4; };
template <> struct cmp_cat_id<hamon::strong_ordering>  { static constexpr unsigned value = 8; };

#if defined(HAMON_HAS_STD_COMPARE) && defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
// * extension *
template <> struct cmp_cat_id<std::partial_ordering> { static constexpr unsigned value = 2; };
template <> struct cmp_cat_id<std::weak_ordering>    { static constexpr unsigned value = 4; };
template <> struct cmp_cat_id<std::strong_ordering>  { static constexpr unsigned value = 8; };
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_COMPARE_DETAIL_CMP_CAT_ID_HPP
