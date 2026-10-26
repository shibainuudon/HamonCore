/**
 *	@file	stoppable_source.hpp
 *
 *	@brief	stoppable_source の定義
 */

#ifndef HAMON_STOP_TOKEN_DETAIL_STOPPABLE_SOURCE_HPP
#define HAMON_STOP_TOKEN_DETAIL_STOPPABLE_SOURCE_HPP

#include <hamon/stop_token/stoppable_token.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

// 32.3.3 Stop token concepts[stoptoken.concepts]

// [stoptoken.concepts]/8

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Source>
HAMON_CONCEPT_OR_BOOL stoppable_source =
	requires (Source & src, Source const csrc)
	{
		// see implicit expression variations ([concepts.equality])
		{ csrc.get_token() } -> hamon::stoppable_token;
		{ csrc.stop_possible() } noexcept -> hamon::same_as<bool>;
		{ csrc.stop_requested() } noexcept -> hamon::same_as<bool>;
		{ src.request_stop() } -> hamon::same_as<bool>;
	};

#else

template <typename Source>
struct stoppable_source_impl
{
private:
	template <typename Source2,
		typename R1 = decltype(hamon::declval<Source2 const&>().get_token()),
		typename = hamon::enable_if_t<hamon::stoppable_token<R1>>,
		typename R2 = decltype(hamon::declval<Source2 const&>().stop_possible()),
		typename = hamon::enable_if_t<hamon::same_as<R2, bool>>,
		typename = hamon::enable_if_t<noexcept(hamon::declval<Source2 const&>().stop_possible())>,
		typename R3 = decltype(hamon::declval<Source2 const&>().stop_requested()),
		typename = hamon::enable_if_t<hamon::same_as<R3, bool>>,
		typename = hamon::enable_if_t<noexcept(hamon::declval<Source2 const&>().stop_requested())>,
		typename R4 = decltype(hamon::declval<Source2&>().request_stop()),
		typename = hamon::enable_if_t<hamon::same_as<R4, bool>>
	>
	static auto test(int) -> hamon::true_type;

	template <typename S>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Source>(0));
};

template <typename Source>
HAMON_CONCEPT_OR_BOOL stoppable_source =
	stoppable_source_impl<Source>::type::value;

#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_STOP_TOKEN_DETAIL_STOPPABLE_SOURCE_HPP
