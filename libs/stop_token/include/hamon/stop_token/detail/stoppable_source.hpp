/**
 *	@file	stoppable_source.hpp
 *
 *	@brief	stoppable_source の定義
 */

#ifndef HAMON_STOP_TOKEN_DETAIL_STOPPABLE_SOURCE_HPP
#define HAMON_STOP_TOKEN_DETAIL_STOPPABLE_SOURCE_HPP

#include <hamon/stop_token/stoppable_token.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

// 32.3.3 Stop token concepts[stoptoken.concepts]

// [stoptoken.concepts]/8

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Source>
concept stoppable_source =
	requires (Source & src, Source const csrc)
	{
		// see implicit expression variations ([concepts.equality])
		{ csrc.get_token() } -> hamon::stoppable_token;
		{ csrc.stop_possible() } noexcept -> hamon::same_as<bool>;
		{ csrc.stop_requested() } noexcept -> hamon::same_as<bool>;
		{ src.request_stop() } -> hamon::same_as<bool>;
	};

#else

// TODO

#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_STOP_TOKEN_DETAIL_STOPPABLE_SOURCE_HPP
