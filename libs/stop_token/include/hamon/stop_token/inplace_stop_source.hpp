/**
 *	@file	inplace_stop_source.hpp
 *
 *	@brief	inplace_stop_source の定義
 */

#ifndef HAMON_STOP_TOKEN_INPLACE_STOP_SOURCE_HPP
#define HAMON_STOP_TOKEN_INPLACE_STOP_SOURCE_HPP

#include <hamon/stop_token/inplace_stop_token_fwd.hpp>

namespace hamon
{

// 32.3.9 Class inplace_stop_source[stopsource.inplace]

class inplace_stop_source
{
public:
	// [stopsource.inplace.cons], constructors
	constexpr inplace_stop_source() noexcept;

	inplace_stop_source(inplace_stop_source&&) = delete;
	inplace_stop_source(inplace_stop_source const&) = delete;
	inplace_stop_source& operator=(inplace_stop_source&&) = delete;
	inplace_stop_source& operator=(inplace_stop_source const&) = delete;
	~inplace_stop_source();

	// [stopsource.inplace.mem], stop handling
	constexpr hamon::inplace_stop_token get_token() const noexcept;

	static constexpr bool stop_possible() noexcept { return true; }

	bool stop_requested() const noexcept;

	bool request_stop() noexcept;
};

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_INPLACE_STOP_SOURCE_HPP
