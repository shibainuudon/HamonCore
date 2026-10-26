/**
 *	@file	inplace_stop_source.hpp
 *
 *	@brief	inplace_stop_source の定義
 */

#ifndef HAMON_STOP_TOKEN_INPLACE_STOP_SOURCE_HPP
#define HAMON_STOP_TOKEN_INPLACE_STOP_SOURCE_HPP

#include <hamon/stop_token/inplace_stop_token.hpp>
#include <hamon/stop_token/detail/stop_state.hpp>

namespace hamon
{

// 32.3.9 Class inplace_stop_source[stopsource.inplace]

#if 0
class inplace_stop_source
{
public:
	// [stopsource.inplace.cons], constructors
	constexpr inplace_stop_source() noexcept
	{
		// [stopsource.inplace.cons]/1
		m_stop_state.increment_stop_source_counter();
	}

	inplace_stop_source(inplace_stop_source&&) = delete;
	inplace_stop_source(inplace_stop_source const&) = delete;
	inplace_stop_source& operator=(inplace_stop_source&&) = delete;
	inplace_stop_source& operator=(inplace_stop_source const&) = delete;

	~inplace_stop_source()
	{
		m_stop_state.decrement_stop_source_counter();
	}

	// [stopsource.inplace.mem], stop handling
	constexpr hamon::inplace_stop_token get_token() const noexcept
	{
		// [stopsource.inplace.mem]/1
		return hamon::inplace_stop_token(const_cast<hamon::detail::stop_state*>(&m_stop_state));
	}

	static constexpr bool stop_possible() noexcept
	{
		return true;
	}

	bool stop_requested() const noexcept
	{
		// [stopsource.inplace.mem]/2
		return m_stop_state.stop_requested();
	}

	bool request_stop() noexcept
	{
		// [stopsource.inplace.mem]/3
		return m_stop_state.request_stop();
	}

private:
	hamon::detail::stop_state m_stop_state;
};
#endif

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_INPLACE_STOP_SOURCE_HPP
