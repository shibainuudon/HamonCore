/**
 *	@file	stop_source.hpp
 *
 *	@brief	stop_source の定義
 */

#ifndef HAMON_STOP_TOKEN_STOP_SOURCE_HPP
#define HAMON_STOP_TOKEN_STOP_SOURCE_HPP

#include <hamon/stop_token/nostopstate_t.hpp>
#include <hamon/stop_token/stop_token.hpp>
#include <hamon/stop_token/detail/stop_state.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 32.3.5 Class stop_source[stopsource]

class stop_source
{
public:
	// [stopsource.cons], constructors, copy, and assignment
	stop_source()
		// [stopsource.cons]/1
		: m_stop_state(new hamon::detail::stop_state())
	{
		m_stop_state->increment_stop_source_counter();
	}

	explicit
	stop_source(hamon::nostopstate_t) noexcept
	{
	}

	stop_source(stop_source const& other) noexcept : m_stop_state(other.m_stop_state)
	{
		if (m_stop_state)
		{
			m_stop_state->increment_stop_source_counter();
		}
	}

	stop_source(stop_source&& other) noexcept = default;

	stop_source& operator=(stop_source const& other) noexcept
	{
		// increment `other` first so that we don't hit 0 in case of self-assignment
		if (other.m_stop_state)
		{
			other.m_stop_state->increment_stop_source_counter();
		}
		if (m_stop_state)
		{
			m_stop_state->decrement_stop_source_counter();
		}
		m_stop_state = other.m_stop_state;
		return *this;
	}

	stop_source& operator=(stop_source&&) noexcept = default;

	~stop_source()
	{
		if (m_stop_state)
		{
			m_stop_state->decrement_stop_source_counter();
		}
	}

	// [stopsource.mem], member functions
	void swap(stop_source& rhs) noexcept
	{
		// [stopsource.mem]/1
		m_stop_state.swap(rhs.m_stop_state);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	hamon::stop_token get_token() const noexcept
	{
		// [stopsource.mem]/2
		if (!stop_possible())
		{
			return stop_token();
		}
		return hamon::stop_token(m_stop_state);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	bool stop_possible() const noexcept
	{
		// [stopsource.mem]/3
		return m_stop_state != nullptr;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	bool stop_requested() const noexcept
	{
		// [stopsource.mem]/4
		return m_stop_state != nullptr && m_stop_state->stop_requested();
	}

	bool request_stop() noexcept
	{
		// [stopsource.mem]/5
		return m_stop_state != nullptr && m_stop_state->request_stop();
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD	// nodiscard as an extension
	bool operator==(stop_source const& rhs) const noexcept = default;
#else
	HAMON_NODISCARD	// nodiscard as an extension
	bool operator==(stop_source const& rhs) const noexcept
	{
		return m_stop_state == rhs.m_stop_state;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	bool operator!=(stop_source const& rhs) const noexcept
	{
		return !(*this == rhs);
	}
#endif

private:
	hamon::shared_ptr<hamon::detail::stop_state> m_stop_state;
};

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_STOP_SOURCE_HPP
