/**
 *	@file	unit_test_ranges_from_range_t .cpp
 *
 *	@brief	from_range_t  のテスト
 */

#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/remove_cv.hpp>

static_assert(hamon::is_default_constructible<hamon::from_range_t>::value, "");
static_assert(hamon::is_same<hamon::from_range_t, hamon::remove_cv_t<decltype(hamon::from_range)>>::value, "");
