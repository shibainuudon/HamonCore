/**
 *	@file	stop_token.hpp
 *
 *	@brief	stop_token の定義
 */

#ifndef HAMON_STOP_TOKEN_STOP_TOKEN_HPP
#define HAMON_STOP_TOKEN_STOP_TOKEN_HPP

#include <hamon/stop_token/stop_callback_fwd.hpp>
#include <hamon/stop_token/detail/stop_state.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 32.3.4 Class stop_token[stoptoken]

class stop_token
{
public:
	template <typename CallbackFn>
	using callback_type = hamon::stop_callback<CallbackFn>;

	stop_token() noexcept = default;

	// [stoptoken.mem], member functions
	void swap(stop_token& rhs) noexcept
	{
		// [stoptoken.mem]/1
		m_stop_state.swap(rhs.m_stop_state);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	bool stop_requested() const noexcept
	{
		// [stoptoken.mem]/2
		return m_stop_state != nullptr && m_stop_state->stop_requested();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	bool stop_possible() const noexcept
	{
		// [stoptoken.mem]/3
		return m_stop_state != nullptr && m_stop_state->stop_possible();
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD	// nodiscard as an extension
	bool operator==(stop_token const& rhs) const noexcept = default;
#else
	HAMON_NODISCARD	// nodiscard as an extension
	bool operator==(stop_token const& rhs) const noexcept
	{
		return m_stop_state == rhs.m_stop_state;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	bool operator!=(stop_token const& rhs) const noexcept
	{
		return !(*this == rhs);
	}
#endif

private:
	explicit
	stop_token(hamon::shared_ptr<hamon::detail::stop_state> const& state)
		: m_stop_state(state)
	{}

	hamon::shared_ptr<hamon::detail::stop_state> m_stop_state;

	friend class stop_source;
	template <typename>
	friend class stop_callback;
};

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_STOP_TOKEN_HPP
