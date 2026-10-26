/**
 *	@file	unit_test_stop_token_stop_source_concepts.cpp
 *
 *	@brief	コンセプトのテスト
 */

#include <hamon/stop_token/stop_source.hpp>
#include <hamon/stop_token/detail/stoppable_source.hpp>
#include <hamon/concepts/copyable.hpp>
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/concepts/swappable.hpp>

// [stopsource.general]/2
static_assert(hamon::detail::stoppable_source<hamon::stop_source>, "");
static_assert(hamon::copyable<hamon::stop_source>, "");
static_assert(hamon::equality_comparable<hamon::stop_source>, "");
static_assert(hamon::swappable<hamon::stop_source>, "");
